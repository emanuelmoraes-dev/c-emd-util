#include <math.h>
#include <string.h>
#include "cemdutil/array_list.h"

/**
 * Cria uma estratégia de realocar apenas o espaço necessário pelo
 * tamanho do array
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do ArrayList
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
size_t ARRAY_LIST_STRICT_STRATEGY_REALLOCATED(size_t length_allocated, size_t size) {
    return size + 1;
}

/**
 * É a estratégia de realocar adicionando a metade do tamanho do array
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do array
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
size_t ARRAY_LIST_HALF_STRATEGY_REALLOCATED(size_t length_allocated, size_t size) {
    size++;
    size_t half = ceil(size / 2.0);
    return size + half;
}

/**
 * É a estratégia de realocar o dobro do que foi alocado anteriormente
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do array
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
size_t ARRAY_LIST_DOUBLE_STRATEGY_REALLOCATED(size_t length_allocated, size_t size) {
    length_allocated = MAX(1, length_allocated);
    return length_allocated*2;
}

/**
 * Obtém o ponteiro que armazena os alementos do array
 *
 * @param array_list instância do ArrayList
 * @return ponteiro que armazena os alementos do array
 */
void* array_list_pointer(ArrayList* array_list) {
    if (array_list->__pointer == NULL) {
        array_list->__pointer = malloc(array_list->type.sizeof_unit);
        array_list->size = 0;
        array_list->__length_allocated = 1;
    }
    return array_list->__pointer;
}

void __array_list_set_pointer(ArrayList* array_list, void* pointer) {
    array_list->__pointer = pointer;
}

/**
 * Inicializa um ArrayList vazio
 *
 * ArrayList->min_extra = min_extra
 * ArrayList->reallocate_strategy = reallocate_strategy
 *
 * @param array_list instância do ArrayList a ser inicializado
 * @param type tipo de dados armazenado pelo array
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @param min_extra valor extra mínimo na realocação do ArrayList
 * @param reallocate_strategy estratégia para realocação
 * @return nova instância de ArrayList
 */
void array_list_init_reallocate_strategy(ArrayList* array_list, ArrayListType type, size_t min_length_allocated, size_t min_extra, ArrayListReallocateStrategy* reallocate_strategy) {
    array_list->type = type;
    array_list->min_extra = min_extra;
    array_list->reallocate_strategy = reallocate_strategy;
    array_list->size = 0;
    array_list->__length_allocated = 1;
    array_list->__length_allocated = MAX(array_list->__length_allocated, min_length_allocated);
    array_list->__length_allocated = MAX(array_list->__length_allocated, min_extra);
    __array_list_set_pointer(array_list, malloc(array_list->type.sizeof_unit * array_list->__length_allocated));
}

/**
 * Inicializa um ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param array_list instância do ArrayList a ser inicializado
 * @param type tipo de dados armazenado pelo array
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @return nova instância de ArrayList
 */
void array_list_init_allocated(ArrayList* array_list, ArrayListType type, size_t min_length_allocated) {
    array_list->type = type;
    array_list->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA;
    array_list->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED;
    array_list->size = 0;
    array_list->__length_allocated = 1;
    array_list->__length_allocated = MAX(array_list->__length_allocated, min_length_allocated);
    array_list->__length_allocated = MAX(array_list->__length_allocated, ARRAY_LIST_DEFAULT_MIN_EXTRA);
    __array_list_set_pointer(array_list, malloc(array_list->type.sizeof_unit * array_list->__length_allocated));
}

/**
 * Inicializa um ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param array_list instância do ArrayList a ser inicializado
 * @param type tipo de dados armazenado pelo array
 * @return nova instância do ArrayList
 */
void array_list_init(ArrayList* array_list, ArrayListType type) {
    array_list_init_reallocate_strategy(array_list, type, 0, ARRAY_LIST_DEFAULT_MIN_EXTRA, ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED);
}

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
ArrayList* new_array_list_reallocate_strategy(ArrayListType type, size_t min_length_allocated, size_t min_extra, ArrayListReallocateStrategy* reallocate_strategy) {
    ArrayList* array_list = (ArrayList*) malloc(sizeof(ArrayList));
    array_list_init_reallocate_strategy(array_list, type, min_length_allocated, min_extra, reallocate_strategy);
    return array_list;
}

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
ArrayList* new_array_list_allocated(ArrayListType type, size_t min_length_allocated) {
    ArrayList* array_list = (ArrayList*) malloc(sizeof(ArrayList));
    array_list_init_allocated(array_list, type, min_length_allocated);
    return array_list;
}

/**
 * Cria um novo ArrayList vazio
 *
 * ArrayList->min_extra = ARRAY_LIST_DEFAULT_MIN_EXTRA # 20
 * ArrayList->reallocate_strategy = ARRAY_LIST_DEFAULT_STRATEGY_REALLOCATED # ARRAY_LIST_HALF_STRATEGY_REALLOCATED
 *
 * @param type tipo de dados armazenado pelo array
 * @return nova instância do ArrayList
 */
ArrayList* new_array_list(ArrayListType type) {
    ArrayList* array_list = (ArrayList*) malloc(sizeof(ArrayList));
    array_list_init(array_list, type);
    return array_list;
}

/**
 * @param array_list instância do ArrayList
 * @return quantidade de espaço alocado para o ArrayList
 */
size_t array_list_get_length_allocated(ArrayList* array_list) {
    return array_list->__length_allocated;
}

/**
 * Implementa a função realloc usando malloc e free
 *
 * @param _ptr ponteiro a ser realocado
 * @param _new_size novo tamanho para o ponteiro
 * @param _old_size atual tamanho para o ponteiro
 * @return novo ponteiro realocado
 */
void* __mfrealloc(void* _ptr, size_t _new_size, size_t _old_size) {
    void* ptr = malloc(_new_size);
    memcpy(ptr, _ptr, MIN(_old_size, _new_size));
    free(_ptr);
    return ptr;
}

/**
 * Informa a quantidade mínima de espaço que deve estar alocado
 * para um determinado ArrayList (esse método não irá interferir
 * em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade mínima que deve estar alocada
 * @return 0 se uma realocação foi necessária
 */
short array_list_set_min_length_allocated(ArrayList* array_list, size_t length_allocated) {
    if (array_list->__length_allocated >= length_allocated)
        return 1;

    size_t new_length = array_list->type.sizeof_unit * length_allocated;
    size_t old_length = array_list->type.sizeof_unit * array_list->__length_allocated;
    __array_list_set_pointer(array_list, __mfrealloc(array_list_pointer(array_list), new_length, old_length));
    array_list->__length_allocated = length_allocated;
    return 0;
}

/**
 * Informa a quantidade máxima de espaço que deve estar alocado
 * para um determinado ArrayList (esse método não irá interferir
 * em realocações futuras)
 *
 * @param array_list instância do ArrayList
 * @param length_allocated quantidade máxima que deve estar alocada
 * @return 0 se uma realocação foi necessária
 */
short array_list_set_max_length_allocated(ArrayList* array_list, size_t length_allocated) {
    if (array_list->__length_allocated <= length_allocated || array_list->size >= length_allocated)
        return 1;

    size_t new_length = array_list->type.sizeof_unit * length_allocated;
    size_t old_length = array_list->type.sizeof_unit * array_list->__length_allocated;
    __array_list_set_pointer(array_list, __mfrealloc(array_list_pointer(array_list), new_length, old_length));
    array_list->__length_allocated = length_allocated;
    return 0;
}

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
short array_list_set_length_allocated(ArrayList* array_list, size_t length_allocated) {
    if (array_list->size >= length_allocated)
        return 1;

    size_t new_length = array_list->type.sizeof_unit * length_allocated;
    size_t old_length = array_list->type.sizeof_unit * array_list->__length_allocated;
    __array_list_set_pointer(array_list, __mfrealloc(array_list_pointer(array_list), new_length, old_length));
    array_list->__length_allocated = length_allocated;
    return 0;
}

/**
 * Adiciona no final do ArrayList os valores presentes em "values"
 *
 * @param array_list instância do ArrayList que receberá os valores
 * @param values array contendo os valores a serem atribuídos
 * @param size quantidade de valores a serem adicionados
 */
void array_list_add_all(ArrayList* array_list, void* values, size_t size) {
    array_list_set_min_length_allocated(array_list, array_list->size + size);
    size_t i;
    for (i = 0; i < size; i++)
        array_list_add(array_list, array_list->type.get(values, i));
}

/**
 * Adiciona em uma posição específica do ArrayList os valores presentes em "values"
 *
 * @param array_list instância do ArrayList que receberá os valores
 * @param values array contendo os valores a serem atribuídos
 * @param size quantidade de valores a serem adicionados
 * @param index posição a ser adicionado os valores
 */
void array_list_add_all_at(ArrayList* array_list, void* values, size_t size, size_t index) {
    array_list_set_min_length_allocated(array_list, array_list->size + size);
    size_t i;
    for (i = size - 1; i >= 0; i--)
        array_list_add_at(array_list, array_list->type.get(values, i), index);
}

/**
 * Ordena o ArrayList
 *
 * @param array_list instância do ArrayList
 * @param cmp função comparadora
 * @param begin primeira posição a ser ordenada (inclusive)
 * @param end última posição a ser ordenada (exclusive)
 */
void array_list_sort(ArrayList* array_list, size_t (*cmp)(void*, void*), size_t begin, size_t end) {
    end--;

    if (begin > end)
        return;

    size_t n = end - begin + 1;
    size_t pv = rand() % n + begin;
    array_list->type.swap(array_list_pointer(array_list), pv, end);

    size_t i, j;
    for (i = begin, j = begin; i < end; i++) {
        void* a = array_list->type.get(array_list_pointer(array_list), i);
        void* b = array_list->type.get(array_list_pointer(array_list), end);

        if (cmp(a, b) > 0)
            continue;

        array_list->type.swap(array_list_pointer(array_list), i, j);
        j++;
    }

    array_list->type.swap(array_list_pointer(array_list), j, end);

    array_list_sort(array_list, cmp, begin, j);
    array_list_sort(array_list, cmp, j + 1, end + 1);

    return;
}

// ### implements interface_list.h ###

/**
 * Obtém a referência do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do alemento
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* array_list_get_at(ArrayList* array_list, size_t index) {
    size_t i;
    for (i = 0; i < array_list->size; i++)
        if (i == index)
            return array_list->type.get(array_list_pointer(array_list), i);
    return NULL;
}

/**
 * Atualiza o valor do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do elemento a ser atualizado
 * @param value valor a ser atribuído
 */
void array_list_set_at(ArrayList* array_list, size_t index, void* value) {
    array_list->type.set(array_list_pointer(array_list), index, value);
}

/**
 * Busca a posição no ArrayList da referência fornecida
 *
 * @param array_list instância do ArrayList
 * @param value referência a ser buscada
 * @return posição na lista da referência. -1 se não for encontrada
 */
size_t array_list_find_index_by_reference(ArrayList* array_list, void* value) {
    size_t i;
    for (i = 0; i < array_list->size; i++)
        if (array_list->type.get(array_list_pointer(array_list), i) == value)
            return i;
    return -1;
}

/**
 * Adiciona no final do ArrayList um valor
 *
 * @param array_list instância do ArrayList que receberá o valor
 * @param value valor a ser adicionado no final do ArrayList
 */
void array_list_add(ArrayList* array_list, void* value) {
    size_t size = array_list->size++;

    if (array_list->__length_allocated <= array_list->size) {
        size_t length_allocated = array_list->reallocate_strategy(array_list->__length_allocated, array_list->size);
        length_allocated = MAX(length_allocated, array_list->size + array_list->min_extra);
        size_t new_length = array_list->type.sizeof_unit * length_allocated;
        size_t old_length = array_list->type.sizeof_unit * array_list->__length_allocated;
        array_list->__length_allocated = length_allocated;
        __array_list_set_pointer(array_list, __mfrealloc(array_list_pointer(array_list), new_length, old_length));
    }

    array_list->type.set(array_list_pointer(array_list), size, value);
}

/**
 * Adiciona um elemento no ArrayList na posicao informada
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 */
void array_list_add_at(ArrayList* array_list, void* value, size_t index) {
    array_list_add(array_list, value);

    size_t i;
    for (i = array_list->size - 1; i > 0 && i > index; i--) {
        void* const to_back = array_list->type.get(array_list_pointer(array_list), i);
        void* const to_front = array_list->type.get(array_list_pointer(array_list), i - 1);
        array_list->type.set(array_list_pointer(array_list), i, to_front);
        array_list->type.set(array_list_pointer(array_list), i - 1, to_back);
    }
}

/**
 * Remove do ArrayList e apaga da memoria a refêrencia fornecida
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser removido do ArrayList e apagado da memória
 * @return 0 se a referência foi encontrada, removida do ArrayList e apagada da memória
 */
short array_list_eraser_by_reference(ArrayList* array_list, void* value) {
    size_t index = array_list_find_index_by_reference(array_list, value);
    if (index < 0) return 1;
    if (value != NULL) free(value);

    size_t i;
    for (i = index; i < array_list->size - 1; i++) {
        void* to_front = array_list->type.get(array_list_pointer(array_list), i + 1);
        array_list->type.set(array_list_pointer(array_list), i, to_front);
    }

    array_list->size--;
    return 0;
}

/**
 * Remove do ArrayList e apaga elemento da memoria que possui a posição
 * fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição a ter o elemento removido do ArrayList e apagado
 *        da memória
 */
void array_list_eraser_at(ArrayList* array_list, size_t index) {
    if (index < 0) return;
    if (index >= array_list->size) return;
    void* value = array_list_get_at(array_list, index);
    if (value != NULL) free(value);

    size_t i;
    for (i = index; i < array_list->size - 1; i++) {
        void* to_front = array_list->type.get(array_list_pointer(array_list), i + 1);
        array_list->type.set(array_list_pointer(array_list), i, to_front);
    }

    array_list->size--;
}

/**
 * Remove do ArrayList sem apagar da memoria a refêrencia fornecida
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser removido do ArrayList sem ser apagado da memória
 * @return 0 se a referência foi encontrada e removida do ArrayList
 */
short array_list_remove_by_reference(ArrayList* array_list, void* value) {
    size_t index = array_list_find_index_by_reference(array_list, value);
    if (index < 0) return 1;

    size_t i;
    for (i = index; i < array_list->size - 1; i++) {
        void* to_back = array_list->type.get(array_list_pointer(array_list), i + 1);
        array_list->type.set(array_list_pointer(array_list), i, to_back);
    }

    array_list->size--;
    return 0;
}

/**
 * Remove do ArrayList sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição a ter o elemento removido do ArrayList sem ser
 *        apagado da memória
 * @return referência removida do ArrayList
 */
void* array_list_remove_at(ArrayList* array_list, size_t index) {
    if (index < 0) return NULL;
    if (index >= array_list->size) return NULL;
    void* value = array_list_get_at(array_list, index);

    size_t i;
    for (i = index; i < array_list->size - 1; i++) {
        void* to_front = array_list->type.get(array_list_pointer(array_list), i + 1);
        array_list->type.set(array_list_pointer(array_list), i, to_front);
    }

    array_list->size--;
    return value;
}

/**
 * Remove os elementos do ArrayList sem apagar os elementos da memoria.
 * Não apaga ArrayList da memória
 *
 * @param _array_list instância do ArrayList
 */
void array_list_clear(void* _array_list) {
    ArrayList* array_list = (ArrayList*)_array_list;
    array_list->size = 0;
    array_list->__length_allocated = 0;
    __array_list_set_pointer(array_list, NULL);
}

/**
 * Remove os elementos do ArrayList e apaga os elementos da memoria.
 * Não apaga ArrayList da memória
 *
 * @param _array_list instância do ArrayList
 */
void array_list_clear_eraser(void* _array_list) {
    ArrayList* array_list = (ArrayList*)_array_list;
    size_t i;
    for (i = array_list->size - 1; i >= 0; i--)
        array_list_eraser_at(array_list, i);
    array_list_clear(_array_list);
}

/**
 * Remove os elementos do ArrayList e apaga os elementos da memoria, usando destrutor.
 * Não apaga ArrayList da memória
 *
 * @param array_list instância do ArrayList
 */
void array_list_clear_eraser_destructor(ArrayList* array_list, void (*destructor)(void*)) {
    size_t i;
    for (i = array_list->size - 1; i >= 0; i--) {
        void* value = array_list_remove_at(array_list, i);
        destructor(value);
    }
    array_list_clear(array_list);
}

/**
 * Remove os elementos do ArrayList sem apagar os elementos da memoria.
 * Apaga ArrayList da memória
 *
 * @param _array_list instância do ArrayList
 */
void array_list_free(void* _array_list) {
    array_list_clear(_array_list);
    free(_array_list);
}

/**
 * Remove os elementos do ArrayList e apaga os elementos da memoria.
 * Apaga ArrayList da memória
 *
 * @param _array_list instância do ArrayList
 */
void array_list_free_eraser(void* _array_list) {
    array_list_clear_eraser(_array_list);
    free(_array_list);
}

/**
 * Remove os elementos do ArrayList e apaga os elementos da memoria, usando destrutor.
 * Apaga ArrayList da memória
 *
 * @param array_list instância do ArrayList
 */
void array_list_free_eraser_destructor(ArrayList* array_list, void (*destructor)(void*)) {
    array_list_clear_eraser_destructor(array_list, destructor);
    free(array_list);
}

/**
 * Percorre cada elemento do ArrayList e passa o valor e
 * posição para "callback"

 * @param array_list instância do ArrayList
 * @param callback função que receberá cada valor e posição
 *        presente no LinkedList. "callback" deve retornar
 *        1 para continuar a iteração. 0 para que o comando
 *        break seja executado
 */
void array_list_for_each(ArrayList* array_list, short (*callback)(void*, size_t)) {
    size_t i;
    for (i = 0; i < array_list->size; i++)
        if (callback(array_list->type.get(array_list_pointer(array_list), i), i) != 0)
            break;
}