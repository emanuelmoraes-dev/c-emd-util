#include <math.h>
#include <string.h>
#include <stdint.h>
#include "cemdutil/array_list.h"
#include "cemdutil/error_utility.h"

// #define SIZE_MIN 65535
#define SIZE_MIN 0

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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
size_t ARRAY_LIST_STRICT_REALLOCATE_STRATEGY(size_t length_allocated, size_t size, EMD_ERR* err) {
    *err = ERROR_CHECK_OVERFLOW_ADD(size, 1, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return length_allocated;
    return size + 1;
}

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
size_t ARRAY_LIST_HALF_REALLOCATE_STRATEGY(size_t length_allocated, size_t size, EMD_ERR* err) {
    size++;
    size_t half = ceil(size / 2.0);
    *err = ERROR_CHECK_OVERFLOW_ADD(size, half, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return length_allocated;
    return size + half;
}

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
size_t ARRAY_LIST_DOUBLE_REALLOCATE_STRATEGY(size_t length_allocated, size_t size, EMD_ERR* err) {
    length_allocated = MAX(1, length_allocated);
    *err = ERROR_CHECK_OVERFLOW_MULT(length_allocated, 2, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return length_allocated;
    return length_allocated*2;
}

/**
 * Obtém o ponteiro que armazena os alementos do array
 *
 * @param array_list instância do ArrayList
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            atribuído, o valor é automaticamente definido como 0 (sem erros).
 * @return ponteiro que armazena os alementos do array
 */
void* array_list_pointer(const ArrayList* array_list, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list, NULL, array_list_pointer)
    return array_list->__pointer;
}

/**
 * Obtém o ponteiro que armazena os alementos do array
 *
 * @param array_list instância do ArrayList
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            atribuído, o valor é automaticamente definido como 0 (sem erros).
 * @return ponteiro que armazena os alementos do array
 */
void* __array_list_pointer_realloc(ArrayList* array_list, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list, NULL, __array_list_pointer_realloc)

    if (array_list->__pointer == NULL) {
        size_t quant_alloc = MAX(1, array_list->min_extra);

        *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, quant_alloc, SIZE_MIN, SIZE_MAX);
        if (*err != EMD_OK)
            return NULL;

        array_list->__pointer = malloc(array_list->type.sizeof_unit * quant_alloc);
        if (array_list->__pointer == NULL) {
            *err = EMD_ERRNO;
            return NULL;
        }

        array_list->size = 0;
        array_list->__length_allocated = 1;
    }

    return array_list->__pointer;
}

/**
 * Atribui novo ponteiro que armazena os alementos do array
 *
 * @param array_list instância do ArrayList
 * @param pointer novo valor a ser atribuído
 * @return ponteiro que armazena os alementos do array
 */
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
 * @param type tipo de dados armazenado pelo ArrayList
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @param min_extra valor extra mínimo na realocação do ArrayList
 * @param reallocate_strategy estratégia para realocação
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_init_reallocate_strategy(ArrayList* array_list, ArrayListType type, size_t min_length_allocated, size_t min_extra, ArrayListReallocateStrategy* reallocate_strategy, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_init_reallocate_strategy)

    array_list->type = type;
    array_list->min_extra = min_extra;
    array_list->reallocate_strategy = reallocate_strategy;
    array_list->size = 0;
    array_list->__length_allocated = 1;
    array_list->__length_allocated = MAX(array_list->__length_allocated, min_length_allocated);
    array_list->__length_allocated = MAX(array_list->__length_allocated, min_extra);

    *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, array_list->__length_allocated, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return;

    void* pointer = malloc(array_list->type.sizeof_unit * array_list->__length_allocated);
    if (pointer == NULL) {
        *err = EMD_ERRNO;
        return;
    }

    __array_list_set_pointer(array_list, pointer);
}

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
void array_list_init_allocated(ArrayList* array_list, ArrayListType type, size_t min_length_allocated, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_init_allocated)
    array_list_init_reallocate_strategy(array_list, type, min_length_allocated, ARRAY_LIST_DEFAULT_MIN_EXTRA, ARRAY_LIST_DEFAULT_REALLOCATE_STRATEGY, err);
}

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
void array_list_init(ArrayList* array_list, ArrayListType type, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_init)
    array_list_init_reallocate_strategy(array_list, type, 0, ARRAY_LIST_DEFAULT_MIN_EXTRA, ARRAY_LIST_DEFAULT_REALLOCATE_STRATEGY, err);
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
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 * @return nova instância de ArrayList
 */
ArrayList* new_array_list_reallocate_strategy(ArrayListType type, size_t min_length_allocated, size_t min_extra, ArrayListReallocateStrategy* reallocate_strategy, EMD_ERR* err) {
    ERROR_REQUIRED_ERR(err, new_array_list_reallocate_strategy)

    ArrayList* array_list = (ArrayList*) malloc(sizeof(ArrayList));
    if (array_list == NULL) {
        *err = EMD_ERRNO;
        return NULL;
    }

    array_list_init_reallocate_strategy(array_list, type, min_length_allocated, min_extra, reallocate_strategy, err);
    if (*err != EMD_OK)
        return NULL;

    return array_list;
}

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
ArrayList* new_array_list_allocated(ArrayListType type, size_t min_length_allocated, EMD_ERR* err) {
    ERROR_REQUIRED_ERR(err, new_array_list_allocated)

    ArrayList* array_list = (ArrayList*) malloc(sizeof(ArrayList));
    if (array_list == NULL) {
        *err = EMD_ERRNO;
        return NULL;
    }

    array_list_init_allocated(array_list, type, min_length_allocated, err);
    if (*err != EMD_OK)
        return NULL;

    return array_list;
}

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
ArrayList* new_array_list(ArrayListType type, EMD_ERR* err) {
    ERROR_REQUIRED_ERR(err, new_array_list)

    ArrayList* array_list = (ArrayList*) malloc(sizeof(ArrayList));
    if (array_list == NULL) {
        *err = EMD_ERRNO;
        return NULL;
    }

    array_list_init(array_list, type, err);
    if (*err != EMD_OK)
        return NULL;

    return array_list;
}

/**
 * @param array_list instância do ArrayList
 * @return quantidade de espaço alocado para o ArrayList
 */
size_t array_list_get_length_allocated(const ArrayList* array_list) {
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
    if (ptr == NULL)
        return NULL;

    void* p = memcpy(ptr, _ptr, MIN(_old_size, _new_size));
    if (p == NULL) {
        free(ptr);
        return NULL;
    }

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
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 * @return 1 se uma realocação foi necessária. 0 caso contrário
 */
EMD_BIT array_list_set_min_length_allocated(ArrayList* array_list, size_t length_allocated, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list, 0, array_list_set_min_length_allocated)

    if (array_list->__length_allocated >= length_allocated)
        return 0;

    *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, length_allocated, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return 0;

    *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, array_list->__length_allocated, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return 0;

    size_t new_length = array_list->type.sizeof_unit * length_allocated;
    size_t old_length = array_list->type.sizeof_unit * array_list->__length_allocated;

    void* pointer = __array_list_pointer_realloc(array_list, err);
    if (*err != EMD_OK)
        return 0;

    pointer = __mfrealloc(pointer, new_length, old_length);
    if (pointer == NULL) {
        *err = EMD_ERRNO;
        return 0;
    }

    __array_list_set_pointer(array_list, pointer);
    array_list->__length_allocated = length_allocated;
    return 1;
}

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
EMD_BIT array_list_set_max_length_allocated(ArrayList* array_list, size_t length_allocated, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list, 0, array_list_set_max_length_allocated)

    if (array_list->__length_allocated <= length_allocated || array_list->size >= length_allocated)
        return 0;

    *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, length_allocated, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return 0;

    *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, array_list->__length_allocated, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return 0;

    size_t new_length = array_list->type.sizeof_unit * length_allocated;
    size_t old_length = array_list->type.sizeof_unit * array_list->__length_allocated;

    void* pointer = __array_list_pointer_realloc(array_list, err);
    if (*err != EMD_OK)
        return 0;

    pointer = __mfrealloc(pointer, new_length, old_length);
    if (pointer == NULL) {
        *err = EMD_ERRNO;
        return 0;
    }

    __array_list_set_pointer(array_list, pointer);
    array_list->__length_allocated = length_allocated;
    return 1;
}

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
EMD_BIT array_list_set_length_allocated(ArrayList* array_list, size_t length_allocated, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list, 0, array_list_set_length_allocated)

    if (array_list->size >= length_allocated)
        return 0;

    *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, length_allocated, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return 0;

    *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, array_list->__length_allocated, SIZE_MIN, SIZE_MAX);
    if (*err != EMD_OK)
        return 0;

    size_t new_length = array_list->type.sizeof_unit * length_allocated;
    size_t old_length = array_list->type.sizeof_unit * array_list->__length_allocated;

    void* pointer = __array_list_pointer_realloc(array_list, err);
    if (*err != EMD_OK)
        return 0;

    pointer = __mfrealloc(pointer, new_length, old_length);
    if (pointer == NULL) {
        *err = EMD_ERRNO;
        return 0;
    }

    __array_list_set_pointer(array_list, pointer);
    array_list->__length_allocated = length_allocated;
    return 1;
}

/**
 * Adiciona no final do ArrayList os valores presentes em "values"
 *
 * @param array_list instância do ArrayList que receberá os valores
 * @param values array contendo os valores a serem atribuídos
 * @param size quantidade de valores a serem adicionados
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_add_all(ArrayList* array_list, void* values, size_t size, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_add_all)

    array_list_set_min_length_allocated(array_list, array_list->size + size, err);
    if (*err != EMD_OK)
        return;

    size_t i;
    for (i = 0; i < size; i++) {
        array_list_add(array_list, array_list->type.get(values, i), err);
        if (*err != EMD_OK)
            return;
    }
}

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
void array_list_add_all_at(ArrayList* array_list, void* values, size_t size, size_t index, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_add_all_at)

    array_list_set_min_length_allocated(array_list, array_list->size + size, err);
    if (*err != EMD_OK)
        return;

    size_t i;
    for (i = size - 1; i >= 0; i--) {
        array_list_add_at(array_list, array_list->type.get(values, i), index, err);
        if (*err != EMD_OK)
            return;
    }
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

    if (begin >= array_list->size || end >= array_list->size)
        return;

    size_t n = end - begin + 1;
    size_t pv = rand() % n + begin;

    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return;

    array_list->type.swap(pointer, pv, end);

    size_t i, j;
    for (i = begin, j = begin; i < end; i++) {
        void* a = array_list->type.get(pointer, i);
        void* b = array_list->type.get(pointer, end);

        if (cmp(a, b) > 0)
            continue;

        array_list->type.swap(pointer, i, j);
        j++;
    }

    array_list->type.swap(pointer, j, end);

    array_list_sort(array_list, cmp, begin, j);
    array_list_sort(array_list, cmp, j + 1, end + 1);

    return;
}

/**
 * Troca os valores de duas posições de uma instância do ArrayList
 *
 * @param array_list instância do ArrayList
 * @param i posição do primeiro valor a ser trocado
 * @param j posição do segundo valor a ser trocado
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_swap(ArrayList* array_list, size_t i, size_t j, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_swap)

    if (MAX(i, j) >= array_list->size || MIN(i, j) < 0) {
        *err = EMD_ERR_INDEX_OVERFLOW;
        return;
    }

    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return;

    array_list->type.swap(pointer, i, j);
}

// ### implements interface_list.h ###

/**
 * Obtém a referência do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do alemento
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* array_list_get_at(const ArrayList* array_list, size_t index) {
    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return;

    size_t i;
    for (i = 0; i < array_list->size; i++)
        if (i == index)
            return array_list->type.get(pointer, i);
    return NULL;
}

/**
 * Atualiza o valor do elemento do ArrayList que possui a posição fornecida
 *
 * @param array_list instância do ArrayList
 * @param index posição do elemento a ser atualizado
 * @param value valor a ser atribuído
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_set_at(ArrayList* array_list, size_t index, void* value, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_set_at)

    if (index >= array_list->size || index < 0) {
        *err = EMD_ERR_INDEX_OVERFLOW;
        return;
    }

    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return;

    array_list->type.set(pointer, index, value);
}

/**
 * Busca a posição no ArrayList da referência fornecida
 *
 * @param array_list instância do ArrayList
 * @param value referência a ser buscada
 * @return posição no ArrayList da referência fornecida. -1 se não encontrado
 */
size_t array_list_find_index_by_reference(const ArrayList* array_list, void* value) {
    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return -1;

    size_t i;
    for (i = 0; i < array_list->size; i++) {
        if (array_list->type.get(pointer, i) == value)
            return i;
    }
    return -1;
}

/**
 * Adiciona no final do ArrayList um valor
 *
 * @param array_list instância do ArrayList que receberá o valor
 * @param value valor a ser adicionado no final do ArrayList
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_add(ArrayList* array_list, void* value, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_add)

    size_t size = array_list->size++;

    if (array_list->__length_allocated <= array_list->size) {
        *err = EMD_OK;
        size_t length_allocated = array_list->reallocate_strategy(array_list->__length_allocated, array_list->size, err);
        if (*err != EMD_OK)
            return;

        *err = ERROR_CHECK_OVERFLOW_ADD(array_list->size, array_list->min_extra, SIZE_MIN, SIZE_MAX);
        if (*err != EMD_OK)
            return;

        *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, length_allocated, SIZE_MIN, SIZE_MAX);
        if (*err != EMD_OK)
            return;

        *err = ERROR_CHECK_OVERFLOW_MULT(array_list->type.sizeof_unit, array_list->__length_allocated, SIZE_MIN, SIZE_MAX);
        if (*err != EMD_OK)
            return;

        length_allocated = MAX(length_allocated, array_list->size + array_list->min_extra);
        size_t new_length = array_list->type.sizeof_unit * length_allocated;
        size_t old_length = array_list->type.sizeof_unit * array_list->__length_allocated;
        array_list->__length_allocated = length_allocated;

        void* pointer = __array_list_pointer_realloc(array_list, err);
        if (*err != EMD_OK)
            return;

        pointer = __mfrealloc(pointer, new_length, old_length);
        if (pointer == NULL) {
            *err = EMD_ERRNO;
            return;
        }

        __array_list_set_pointer(array_list, pointer);
    }

    void* pointer = __array_list_pointer_realloc(array_list, err);
    if (*err != EMD_OK)
        return;

    array_list->type.set(pointer, size, value);
}

/**
 * Adiciona um elemento no ArrayList na posicao informada
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 * @param err referência para armazenar o valor do erro, caso ocorra. Se não
 *            ocorrer erro, o valor é automaticamente definido como 0
 */
void array_list_add_at(ArrayList* array_list, void* value, size_t index, EMD_ERR* err) {
    ERROR_REQUIRED_ERR_METHOD(err, array_list,, array_list_add_at)

    if (index >= array_list->size || index < 0) {
        *err = EMD_ERR_INDEX_OVERFLOW;
        return;
    }

    array_list_add(array_list, value, err);
    if (*err != EMD_OK)
        return;

    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return;

    size_t i;
    for (i = array_list->size - 1; i > 0 && i > index; i--) {
        void* const to_back = array_list->type.get(pointer, i);
        void* const to_front = array_list->type.get(pointer, i - 1);
        array_list->type.set(pointer, i, to_front);
        array_list->type.set(pointer, i - 1, to_back);
    }
}

/**
 * Remove do ArrayList e apaga da memoria a refêrencia fornecida
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser removido do ArrayList e apagado da memória
 * @return 1 se a referência foi encontrada, removida do ArrayList e apagada da memória. 0 caso contrário
 */
EMD_BIT array_list_eraser_by_reference(ArrayList* array_list, void* value) {
    size_t index = array_list_find_index_by_reference(array_list, value);

    if (index < 0)
        return 0;

    if (value != NULL)
        free(value);

    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return 0;

    size_t i;
    for (i = index; i < array_list->size - 1; i++) {
        void* to_back = array_list->type.get(pointer, i + 1);
        array_list->type.set(pointer, i, to_back);
    }

    array_list->size--;
    return 1;
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

    if (value != NULL)
        free(value);

    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return;

    size_t i;
    for (i = index; i < array_list->size - 1; i++) {
        void* to_back = array_list->type.get(pointer, i + 1);
        array_list->type.set(pointer, i, to_back);
    }

    array_list->size--;
}

/**
/**
 * Remove do ArrayList sem apagar da memoria a refêrencia fornecida
 *
 * @param array_list instância do ArrayList
 * @param value valor a ser removido do ArrayList sem ser apagado da memória
 * @return 1 se a referência foi encontrada e removida do ArrayList. 0 caso contrário
 */
EMD_BIT array_list_remove_by_reference(ArrayList* array_list, void* value) {
    size_t index = array_list_find_index_by_reference(array_list, value);

    if (index < 0)
        return 0;

    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return 0;

    size_t i;
    for (i = index; i < array_list->size - 1; i++) {
        void* to_back = array_list->type.get(pointer, i + 1);
        array_list->type.set(pointer, i, to_back);
    }

    array_list->size--;
    return 1;
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
    void* pointer = array_list_pointer(array_list);
    if (pointer == NULL)
        return NULL;

    size_t i;
    for (i = index; i < array_list->size - 1; i++) {
        void* to_back = array_list->type.get(pointer, i + 1);
        array_list->type.set(pointer, i, to_back);
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
    for (i = array_list->size - 1; i >= 0; i--) {
        array_list_eraser_at(array_list, i);
    }
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
void array_list_for_each(const ArrayList* array_list, EMD_BIT (*callback)(void*, size_t)) {
    size_t i;
    for (i = 0; i < array_list->size; i++) {
        void* pointer = array_list_pointer(array_list);
        if (callback(array_list->type.get(pointer, i), i) == 0)
            break;
    }
}