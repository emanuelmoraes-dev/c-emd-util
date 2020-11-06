#ifndef ARRAY_LIST_H_INCLUDED
#define ARRAY_LIST_H_INCLUDED

#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ARRAY_LIST_DEFAULT_MIN_EXTRA 20 // Quantidade mínima de espaço extra em realocações de memória
#define ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED ARRAY_LIST_HALF_STRATEGY_REALLOCATED // Estratégia padrão de realocação de memória

#define ARRAY_LIST_TYPEDEF(varname, type) \
    void* __##varname##_array_list_pointer_get(void* pointer, int index) {\
        type##* p = (type##*) pointer;\
        return p[i];\
    }\
    void __##varname##_array_list_pointer_set(void* pointer, int index, void* value) {\
        type##* p = (type##*) pointer;\
        type##* v = (type##*) value;\
        p[i] = *v;\
    }\
    ArrayListType varname;\
    varname.sizeof_unit = sizeof(type);\
    varname.get = __##varname##_array_list_pointer_get;\
    varname.set = __##varname##_array_list_pointer_set;


typedef void* ArrayListPointerGet(void* pointer, int index);
typedef void ArrayListPointerSet(void* pointer, int index, void* value);

typedef struct __st_array_list_type {
    size_t sizeof_unit;
    ArrayListPointerGet get;
    ArrayListPointerSet set;
} ArrayListType;

/**
 * Define o tipo de realocação que o ArrayList terá
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do ArrayList
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
typedef int ArrayListReallocateStrategy(int length_allocated, int lenght);

/**
 * Cria uma estratégia de realocar apenas o espaço necessário pelo
 * tamanho do array
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do ArrayList
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
*/
int ARRAY_LIST_STRICT_STRATEGY_REALLOCATED(int length_allocated, int size);

/**
 * É a estratégia de realocar adicionando a metade do tamanho do array
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do array
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
*/
int ARRAY_LIST_HALF_STRATEGY_REALLOCATED(int length_allocated, int size);

/**
 * É a estratégia de realocar o dobro do que foi alocado anteriormente
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do array
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
int ARRAY_LIST_DOUBLE_STRATEGY_REALLOCATED(int length_allocated, int size);

/**
 * Struct que representa uma instância do ArrayList
 */
typedef struct __st_array_list {
    // public
    void* pointer; // Ponteiro que armazena os alementos do array
    ArrayListType type; // Tipo de dados armazenado pelo array
    size_t size; // tamanho so array
    size_t min_extra; // Quantidade mínima de espaço extra na realocação do Array
    ArrayListReallocateStrategy* reallocate_strategy; // Estratégia de realocação de espaço

    // private
    size_t __length_allocated; // Espaço alocado na memória
} ArrayList;

/**
 * Construtor do ArrayList
 *
 * ArrayList->min_extra = min_extra
 * ArrayList->reallocate_strategy = reallocate_strategy
 *
 * @param type tipo de dados armazenado pelo array
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @param min_extra valor extra mínimo na realocação do ArrayList
 * @param reallocate_strategy estratégia para realocação
 * @return nova instância de ArrayList
 */
ArrayList* new_array_list_reallocate_strategy(ArrayListType type, int min_length_allocated, int min_extra, ArrayListReallocateStrategy* reallocate_strategy);

/**
 * Construtor do ArrayList
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param type tipo de dados armazenado pelo array
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @return nova instância de ArrayList
 */
ArrayList* new_array_list_allocated(ArrayListType type, int min_length_allocated);

/**
 * Construtor do ArrayList
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param type tipo de dados armazenado pelo array
 * @return nova instância do ArrayList
 */
ArrayList* new_array_list(ArrayListType type);

/**
 * @param array_list instância do ArrayList
 * @return quantidade de espaço alocado para o ArrayList
 */
int array_list_get_length_allocated(ArrayList* array_list);

/**
 * Informa a quantidade mínima de espaço que deve estar alocado
 * para um determinado ArrayList (esse método não irá interferir
 * em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade mínima que deve estar alocada
 * @return 1 se uma realocação foi necessária, 0 caso contrário
 */
short array_list_set_min_length_allocated(ArrayList* array_list, int length_allocated);

/**
 * Informa a quantidade máxima de espaço que deve estar alocado
 * para um determinado ArrayList (esse método não irá interferir
 * em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade máxima que deve estar alocada
 * @return 1 se uma realocação foi necessária, 0 caso contrário
 */
short array_list_set_max_length_allocated(ArrayList* array_list, int length_allocated);

/**
 * Informa a quantidade exata que deve estar alocado para um determinado
 * ArrayList. Se o tamanho do array for maior que o tamanho da
 * alocação, a realocação não ocorrerá (esse método não irá
 * interferir em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade exata que deve estar alocada
 * @return 1 se uma realocação ocorreu, 0 caso contrário
 */
short array_list_set_length_allocated(ArrayList* array_list, int length_allocated);

/**
 * Adiciona no final do ArrayList os valores presentes em "values"
 *
 * @param array_list instância do ArrayList que receberá os valores
 * @param values array contendo os valores a serem atribuídos
 * @param size quantidade de valores a serem adicionados
 */
void array_list_add_all(ArrayList* array_list, void* values, int size);

/**
 * Substitui os valores do ArrayList pelos valores presentes em "values"
 *
 * @param array_list instância do ArrayList que receberá os valores
 * @param values array contendo os valores a serem atribuídos
 * @param size quantidade de valores a serem atribuídos
 */
void array_list_set(ArrayList* array_list, void* values, int size);

// ### implements interface_list.h ###

/**
 * Busca a referência do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do alemento a ser buscado
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* array_list_find_by_index(ArrayList* array_list, int index);

/**
 * Busca a referência do elemento do ArrayList que possui a referência fornecida
 *
 * @param array_list instância do ArrayList
 * @param value referência do valor a ser buscado
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* array_list_find_by_reference(ArrayList* array_list, void* value);

/**
 * Adiciona no final do ArrayList um valor
 *
 * @param array_list instância do ArrayList que receberá o valor
 * @param value valor a ser adicionado no final do ArrayList
 */
void array_list_add(ArrayList* array_list, void* value);

/**
 * Adiciona um elemento no ArrayList na posicao informada
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 */
void array_list_add_at(ArrayList* array_list, void* value, int index);

/**
 * Remove do ArrayList e apaga da memoria a refêrencia fornecida
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser removido do ArrayList e apagado da memória
 */
void array_list_eraser_by_reference(ArrayList* array_list, void* value);

/**
 * Remove do ArrayList e apaga elemento da memoria que possui a posição
 * fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição a ter o elemento removido do ArrayList e apagado
 *        da memória
 */
void array_list_eraser_at(ArrayList* array_list, int index);

/**
 * Remove do ArrayList sem apagar da memoria a refêrencia fornecida
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser removido do ArrayList sem ser apagado da
 *        memória
 */
void array_list_remove_by_reference(ArrayList* array_list, void* value);

/**
 * Remove do ArrayList sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição a ter o elemento removido do ArrayList sem ser
 *        apagado da memória
 */
void array_list_remove_at(ArrayList* array_list, int index);

/**
 * Apaga o ArrayList sem apagar os elementos da memoria
 *
 * @param array_list instância do ArrayList
 */
void array_list_free(ArrayList* array_list);

/**
 * Apaga o ArrayList e os elementos da lista e da memoria
 *
 * @param array_list instância do ArrayList
 */
void array_list_free_eraser(ArrayList* array_list);

/**
 * Apaga o ArrayList e os elementos da lista e da memoria
 *
 * @param array_list instância do ArrayList
 */
void array_list_free_eraser_destructor(ArrayList* array_list, void (*destructor)(void*));

/**
 * Percorre cada elemento do ArrayList e passa o valor e
 * posição para "callback"

 * @param array_list instância do ArrayList
 * @param callback função que receberá cada valor e posição
 *        presente no ArrayList
 */
void array_list_for_each(ArrayList* array_list, void (*callback)(void*, int));

#endif // ARRAY_LIST_H_INCLUDED