#ifndef C_EMD_UTIL_ARRAY_LIST_H_INCLUDED
#define C_EMD_UTIL_ARRAY_LIST_H_INCLUDED

#include <stdlib.h>
#include "cemdutil/types.h"

#define ARRAY_LIST_DEFAULT_MIN_EXTRA 20 // Quantidade mínima de espaço extra em realocações de memória
#define ARRAY_LIST_DEFAULT_REALLOCATE_STRATEGY ARRAY_LIST_HALF_REALLOCATE_STRATEGY // Estratégia padrão de realocação de memória

#define ARRAY_LIST_TYPEDEF(varname, type) \
    void* __##varname##_array_list_pointer_get(void* pointer, size_t index) {\
        type* p = (type*) pointer;\
        return &p[index];\
    }\
    void __##varname##_array_list_pointer_set(void* pointer, size_t index, void* value) {\
        type* p = (type*) pointer;\
        type* v = (type*) value;\
        p[index] = *v;\
    }\
    void __##varname##_array_list_pointer_swap(void* pointer, size_t i, size_t j) {\
        type* p = (type*) pointer;\
        type to_j = p[i];\
        type to_i = p[j];\
        p[j] = to_j;\
        p[i] = to_i;\
    }\
    ArrayListType varname() {\
        ArrayListType t;\
        t.sizeof_unit = sizeof(type);\
        t.get = __##varname##_array_list_pointer_get;\
        t.set = __##varname##_array_list_pointer_set;\
        t.swap = __##varname##_array_list_pointer_swap;\
        return t;\
    }

typedef struct __st_array_list_type {
    size_t sizeof_unit;
    void* (*get)(void* pointer, size_t index);
    void (*set)(void* pointer, size_t index, void* value);
    void (*swap)(void* pointer, size_t i, size_t j);
} ArrayListType;

/**
 * Define o tipo de realocação que o ArrayList terá
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do ArrayList
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            atribuído, o valor é automaticamente definido como 0 (sem erros).
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
typedef size_t ArrayListReallocateStrategy(size_t length_allocated, size_t lenght, EMD_ERR* err);

/**
 * Cria uma estratégia de realocar apenas o espaço necessário pelo
 * tamanho do array
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do ArrayList
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            atribuído, o valor é automaticamente definido como 0 (sem erros).
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
size_t ARRAY_LIST_STRICT_REALLOCATE_STRATEGY(size_t length_allocated, size_t size, EMD_ERR* err);

/**
 * É a estratégia de realocar adicionando a metade do tamanho do array
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do array
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            atribuído, o valor é automaticamente definido como 0 (sem erros).
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
size_t ARRAY_LIST_HALF_REALLOCATE_STRATEGY(size_t length_allocated, size_t size, EMD_ERR* err);

/**
 * É a estratégia de realocar o dobro do que foi alocado anteriormente
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do array
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            atribuído, o valor é automaticamente definido como 0 (sem erros).
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
size_t ARRAY_LIST_DOUBLE_REALLOCATE_STRATEGY(size_t length_allocated, size_t size, EMD_ERR* err);

/**
 * Struct que representa uma instância do ArrayList
 */
typedef struct __st_array_list {
    // public
    ArrayListType type; // Tipo de dados armazenado pelo array
    size_t size; // tamanho so array
    size_t min_extra; // Quantidade mínima de espaço extra na realocação do Array
    ArrayListReallocateStrategy* reallocate_strategy; // Estratégia de realocação de espaço

    // private
    void* __pointer; // Ponteiro que armazena os alementos do array
    size_t __length_allocated; // Espaço alocado na memória
} ArrayList;

/**
 * Obtém o ponteiro que armazena os alementos do array
 *
 * @param array_list instância do ArrayList
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            atribuído, o valor é automaticamente definido como 0 (sem erros).
 * @return ponteiro que armazena os alementos do array
 */
void* array_list_pointer(const ArrayList* array_list, EMD_ERR* err);

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
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_init_reallocate_strategy(ArrayList* array_list, ArrayListType type, size_t min_length_allocated, size_t min_extra, ArrayListReallocateStrategy* reallocate_strategy, EMD_ERR* err);

/**
 * Inicializa um ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_REALLOCATE_STRATEGY # ARRAY_LIST_HALF_REALLOCATE_STRATEGY
 *
 * @param array_list instância do ArrayList a ser inicializado
 * @param type tipo de dados armazenado pelo ArrayList
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_init_allocated(ArrayList* array_list, ArrayListType type, size_t min_length_allocated, EMD_ERR* err);

/**
 * Inicializa um ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_REALLOCATE_STRATEGY # ARRAY_LIST_HALF_REALLOCATE_STRATEGY
 *
 * @param array_list instância do ArrayList a ser inicializado
 * @param type tipo de dados armazenado pelo ArrayList
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_init(ArrayList* array_list, ArrayListType type, EMD_ERR* err);

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
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 * @return nova instância de ArrayList
 */
ArrayList* new_array_list_reallocate_strategy(ArrayListType type, size_t min_length_allocated, size_t min_extra, ArrayListReallocateStrategy* reallocate_strategy, EMD_ERR* err);

/**
 * Cria um novo ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_REALLOCATE_STRATEGY # ARRAY_LIST_HALF_REALLOCATE_STRATEGY
 *
 * @param type tipo de dados armazenado pelo array
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 * @return nova instância de ArrayList
 */
ArrayList* new_array_list_allocated(ArrayListType type, size_t min_length_allocated, EMD_ERR* err);

/**
 * Cria um novo ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_REALLOCATE_STRATEGY # ARRAY_LIST_HALF_REALLOCATE_STRATEGY
 *
 * @param type tipo de dados armazenado pelo array
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 * @return nova instância do ArrayList
 */
ArrayList* new_array_list(ArrayListType type, EMD_ERR* err);

/**
 * @param array_list instância do ArrayList
 * @return quantidade de espaço alocado para o ArrayList
 */
size_t array_list_get_length_allocated(const ArrayList* array_list);

/**
 * Informa a quantidade mínima de espaço que deve estar alocado
 * para um determinado ArrayList (esse método não irá interferir
 * em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade mínima que deve estar alocada
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 * @return 1 se uma realocação foi necessária. 0 caso contrário
 */
EMD_BIT array_list_set_min_length_allocated(ArrayList* array_list, size_t length_allocated, EMD_ERR* err);

/**
 * Informa a quantidade máxima de espaço que deve estar alocado
 * para um determinado ArrayList (esse método não irá interferir
 * em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade máxima que deve estar alocada
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 * @return 1 se uma realocação foi necessária. 0 caso contrário
 */
EMD_BIT array_list_set_max_length_allocated(ArrayList* array_list, size_t length_allocated, EMD_ERR* err);

/**
 * Informa a quantidade exata que deve estar alocado para um determinado
 * ArrayList. Se o tamanho do array for maior que o tamanho da
 * alocação, a realocação não ocorrerá (esse método não irá
 * interferir em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade exata que deve estar alocada
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 * @return 1 se uma realocação foi necessária. 0 caso contrário
 */
EMD_BIT array_list_set_length_allocated(ArrayList* array_list, size_t length_allocated, EMD_ERR* err);

/**
 * Adiciona no final do ArrayList os valores presentes em "values"
 *
 * @param array_list instância do ArrayList que receberá os valores
 * @param values array contendo os valores a serem atribuídos
 * @param size quantidade de valores a serem adicionados
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_add_all(ArrayList* array_list, void* values, size_t size, EMD_ERR* err);

/**
 * Adiciona em uma posição específica do ArrayList os valores presentes em "values"
 *
 * @param array_list instância do ArrayList que receberá os valores
 * @param values array contendo os valores a serem atribuídos
 * @param size quantidade de valores a serem adicionados
 * @param index posição a ser adicionado os valores
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_add_all_at(ArrayList* array_list, void* values, size_t size, size_t index, EMD_ERR* err);

/**
 * Ordena o ArrayList
 *
 * @param array_list instância do ArrayList
 * @param cmp função comparadora
 * @param begin primeira posição a ser ordenada (inclusive)
 * @param end última posição a ser ordenada (exclusive)
 */
void array_list_sort(ArrayList* array_list, size_t (*cmp)(void*, void*), size_t begin, size_t end);

/**
 * Troca os valores de duas posições de uma instância do ArrayList
 *
 * @param array_list instância do ArrayList
 * @param i posição do primeiro valor a ser trocado
 * @param j posição do segundo valor a ser trocado
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_swap(ArrayList* array_list, size_t i, size_t j, EMD_ERR* err);

// ### implements interface_list.h ###

/**
 * Obtém a referência do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do alemento
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* array_list_get_at(const ArrayList* array_list, size_t index);

/**
 * Atualiza o valor do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do elemento a ser atualizado
 * @param value valor a ser atribuído
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_set_at(ArrayList* array_list, size_t index, void* value, EMD_ERR* err);

/**
 * Busca a posição no ArrayList da referência fornecida
 *
 * @param array_list instância do ArrayList
 * @param value referência a ser buscada
 * @return posição no ArrayList da referência fornecida. -1 se não encontrado
 */
size_t array_list_find_index_by_reference(const ArrayList* array_list, void* value);

/**
 * Adiciona no final do ArrayList um valor
 *
 * @param array_list instância do ArrayList que receberá o valor
 * @param value valor a ser adicionado no final do ArrayList
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_add(ArrayList* array_list, void* value, EMD_ERR* err);

/**
 * Adiciona um elemento no ArrayList na posicao informada
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_add_at(ArrayList* array_list, void* value, size_t index, EMD_ERR* err);

/**
 * Remove do ArrayList e apaga da memoria a refêrencia fornecida
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser removido do ArrayList e apagado da memória
 * @return 1 se a referência foi encontrada, removida do ArrayList e apagada da memória. 0 caso contrário
 */
EMD_BIT array_list_eraser_by_reference(ArrayList* array_list, void* value);

/**
 * Remove do ArrayList e apaga elemento da memoria que possui a posição
 * fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição a ter o elemento removido do ArrayList e apagado
 *        da memória
 */
void array_list_eraser_at(ArrayList* array_list, size_t index);

/**
 * Remove do ArrayList sem apagar da memoria a refêrencia fornecida
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser removido do ArrayList sem ser apagado da memória
 * @return 1 se a referência foi encontrada e removida do ArrayList. 0 caso contrário
 */
EMD_BIT array_list_remove_by_reference(ArrayList* array_list, void* value);

/**
 * Remove do ArrayList sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição a ter o elemento removido do ArrayList sem ser
 *        apagado da memória
 * @return referência removida do ArrayList
 */
void* array_list_remove_at(ArrayList* array_list, size_t index);

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
void array_list_for_each(const ArrayList* array_list, EMD_BIT (*callback)(void*, size_t));

#endif // C_EMD_UTIL_ARRAY_LIST_H_INCLUDED
