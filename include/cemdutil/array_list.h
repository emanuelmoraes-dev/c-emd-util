#ifndef C_EMD_UTIL_ARRAY_LIST_H_INCLUDED
#define C_EMD_UTIL_ARRAY_LIST_H_INCLUDED

#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ARRAY_LIST_DEFAULT_MIN_EXTRA 20 // Quantidade mínima de espaço extra em realocações de memória
#define ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED ARRAY_LIST_HALF_STRATEGY_REALLOCATED // Estratégia padrão de realocação de memória

#define ARRAY_LIST_TYPEDEF(varname, type) \
    void* __##varname##_array_list_pointer_get(void* pointer, int index) {\
        type##* p = (type*) pointer;\
        return &p[index];\
    }\
    void __##varname##_array_list_pointer_set(void* pointer, int index, void* value) {\
        type##* p = (type*) pointer;\
        type##* v = (type*) value;\
        p[index] = *v;\
    }\
    ArrayListType* varname() {\
        ArrayListType* t = (ArrayListType*) malloc(sizeof(ArrayListType));\
        t->sizeof_unit = sizeof(type);\
        t->get = __##varname##_array_list_pointer_get;\
        t->set = __##varname##_array_list_pointer_set;\
        return t;\
    }

typedef struct __st_array_list_type {
    size_t sizeof_unit;
    void* (*get)(void* pointer, int index);
    void (*set)(void* pointer, int index, void* value);
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
    ArrayListType type; // Tipo de dados armazenado pelo array
    int size; // tamanho so array
    int min_extra; // Quantidade mínima de espaço extra na realocação do Array
    ArrayListReallocateStrategy* reallocate_strategy; // Estratégia de realocação de espaço

    // private
    void* __pointer; // Ponteiro que armazena os alementos do array
    int __length_allocated; // Espaço alocado na memória
} ArrayList;

/**
 * Obtém o ponteiro que armazena os alementos do array
 *
 * @param array_list instância do ArrayList
 * @return ponteiro que armazena os alementos do array
 */
void* array_list_pointer(ArrayList* array_list);

/**
 * Inicializa um ArrayList vazio
 *
 * ArrayList->min_extra = min_extra
 * ArrayList->reallocate_strategy = reallocate_strategy
 *
 * @param array_list instância do ArrayList a ser inicializado
 * @param type tipo de dados armazenado pelo ArrayList
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @param min_extra valor extra mínimo na realocação do ArrayList
 * @param reallocate_strategy estratégia para realocação
 */
void array_list_init_reallocate_strategy(ArrayList* array_list, ArrayListType* type, int min_length_allocated, int min_extra, ArrayListReallocateStrategy* reallocate_strategy);

/**
 * Inicializa um ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param array_list instância do ArrayList a ser inicializado
 * @param type tipo de dados armazenado pelo ArrayList
 * @param min_length_allocated quantidade mínima que deve estar alocado
 */
void array_list_init_allocated(ArrayList* array_list, ArrayListType* type, int min_length_allocated);

/**
 * Inicializa um ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param array_list instância do ArrayList a ser inicializado
 * @param type tipo de dados armazenado pelo ArrayList
 */
void array_list_init(ArrayList* array_list, ArrayListType* type);

/**
 * Cria um novo ArrayList vazio
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
ArrayList* new_array_list_reallocate_strategy(ArrayListType* type, int min_length_allocated, int min_extra, ArrayListReallocateStrategy* reallocate_strategy);

/**
 * Cria um novo ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param type tipo de dados armazenado pelo array
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @return nova instância de ArrayList
 */
ArrayList* new_array_list_allocated(ArrayListType* type, int min_length_allocated);

/**
 * Cria um novo ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param type tipo de dados armazenado pelo array
 * @return nova instância do ArrayList
 */
ArrayList* new_array_list(ArrayListType* type);

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
 * @return 0 se uma realocação foi necessária
 */
short array_list_set_min_length_allocated(ArrayList* array_list, int length_allocated);

/**
 * Informa a quantidade máxima de espaço que deve estar alocado
 * para um determinado ArrayList (esse método não irá interferir
 * em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade máxima que deve estar alocada
 * @return 0 se uma realocação foi necessária
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
 * @return 0 se uma realocação ocorreu
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
 * Adiciona em uma posição específica do ArrayList os valores presentes em "values"
 *
 * @param array_list instância do ArrayList que receberá os valores
 * @param values array contendo os valores a serem atribuídos
 * @param size quantidade de valores a serem adicionados
 * @param index posição a ser adicionado os valores
 */
void array_list_add_all_at(ArrayList* array_list, void* values, int size, int index);

/**
 * Ordena o ArrayList
 *
 * @param array_list instância do ArrayList
 * @param cmp função comparadora
 * @param begin primeira posição a ser ordenada (inclusive)
 * @param end última posição a ser ordenada (exclusive)
 */
void array_list_sort(ArrayList* array_list, int (*cmp)(void*, void*), int begin, int end);

// ### implements interface_list.h ###

/**
 * Obtém a referência do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do alemento
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* array_list_get_by_index(ArrayList* array_list, int index);

/**
 * Atualiza o valor do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do elemento a ser atualizado
 * @param value valor a ser atribuído
 */
void array_list_set_by_index(ArrayList* array_list, int index, void* value);

/**
 * Busca a posição no ArrayList da referência fornecida
 *
 * @param array_list instância do ArrayList
 * @param value referência a ser buscada
 * @return posição na lista da referência. -1 se não for encontrada
 */
int array_list_find_index_by_reference(ArrayList* array_list, void* value);

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
 * @return 0 se a referência foi encontrada, removida do ArrayList e apagada da memória.
 */
short array_list_eraser_by_reference(ArrayList* array_list, void* value);

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
 * @param value valor a ser removido do ArrayList sem ser apagado da memória
 * @return 0 se a referência foi encontrada e removida do ArrayList.
 */
short array_list_remove_by_reference(ArrayList* array_list, void* value);

/**
 * Remove do ArrayList sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição a ter o elemento removido do ArrayList sem ser
 *        apagado da memória
 * @return referência removida do ArrayList
 */
void* array_list_remove_at(ArrayList* array_list, int index);

/**
 * Remove os elementos do ArrayList sem apagar os elementos da memoria.
 * Não apaga ArrayList da memória
 *
 * @param _array_list instância do ArrayList
 */
void array_list_clear(void* _array_list);

/**
 * Remove os elementos do ArrayList e apaga os elementos da memoria.
 * Não apaga ArrayList da memória
 *
 * @param _array_list instância do ArrayList
 */
void array_list_clear_eraser(void* _array_list);

/**
 * Remove os elementos do ArrayList e apaga os elementos da memoria, usando destrutor.
 * Não apaga ArrayList da memória
 *
 * @param array_list instância do ArrayList
 */
void array_list_clear_eraser_destructor(ArrayList* array_list, void (*destructor)(void*));

/**
 * Remove os elementos do ArrayList sem apagar os elementos da memoria.
 * Apaga ArrayList da memória
 *
 * @param _array_list instância do ArrayList
 */
void array_list_free(void* _array_list);

/**
 * Remove os elementos do ArrayList e apaga os elementos da memoria.
 * Apaga ArrayList da memória
 *
 * @param _array_list instância do ArrayList
 */
void array_list_free_eraser(void* _array_list);

/**
 * Remove os elementos do ArrayList e apaga os elementos da memoria, usando destrutor.
 * Apaga ArrayList da memória
 *
 * @param array_list instância do ArrayList
 */
void array_list_free_eraser_destructor(ArrayList* array_list, void (*destructor)(void*));

/**
 * Percorre cada elemento do ArrayList e passa o valor e
 * posição para "callback"

 * @param array_list instância do ArrayList
 * @param callback função que receberá cada valor e posição
 *        presente no LinkedList. "callback" deve retornar
 *        1 para continuar a iteração. 0 para que o comando
 *        break seja executado
 */
void array_list_for_each(ArrayList* array_list, short (*callback)(void*, int));

#endif // C_EMD_UTIL_ARRAY_LIST_H_INCLUDED