#ifndef INTERFACE_LIST_H_INCLUDED
#define INTERFACE_LIST_H_INCLUDED

// ### CRIAÇÃO E ATRIBUIÇÃO DE VARIÁVEL DA INTERFACE LIST ###]

#define LIST_NO_PREFIX

/**
 * Declara LIST em parâmetro de função
 *
 * @param varname nome do parâmetro
 */
#define LIST_PARAM(varname) LinkedList* __##varname##_linked_list, ArrayList* __##varname##_array_list

/**
 * Passa LIST para LIST em parâmetro de função
 *
 * @param valuename nome da variável que possui LIST
 */
#define LIST_ARG(valuename) __##valuename##_linked_list, __##valuename##_array_list
/**
 * Passa LIST para LIST em parâmetro de função, fornecendo "prefix". Prefix pode ser, por exemplo, uma estrutura seguido por "." ou "->".
 * Se não houver prefixo, basta passar LIST_NO_PREFIX
 *
 * @param valuename nome da variável que possui LIST
 */
#define LIST_ARG_PREFIX(prefix, valuename) prefix##__##valuename##_linked_list, prefix##__##valuename##_array_list
/**
 * Passa LinkedList para LIST em parâmetro de função
 *
 * @param linked_list instância de LinkedList
 */
#define LIST_ARG_LINKED_LIST(linked_list) linked_list, NULL
/**
 * Passa ArrayList para LIST em parâmetro de função
 *
 * @param array_list instância de ArrayList
 */
#define LIST_ARG_ARRAY_LIST(array_list) NULL, arrayList

/**
 * Declara LIST de um LIST
 *
 * @param varname nome da variável a ser criada
 * @param valuename nome da variável que será atribuída na variável criada
 */
#define LIST_LET(varname, valuename) \
    LinkedList* __##varname##_linked_list = __##valuename##_linked_list;\
    ArrayList* __##varname##_array_list = __##valuename##_array_list
/**
 * Declara LIST de um LinkedList*
 *
 * @param varname nome da variável a ser criada
 * @param value valor do tipo LinkedList* a ser atribuído na variável a ser criada
 */
#define LIST_LET_LINKED_LIST(varname, value) \
    LinkedList* __##varname##_linked_list = value;\
    ArrayList* __##varname##_array_list = NULL
/**
 * Declara LIST de um ArrayList*
 *
 * @param varname nome da variável a ser criada
 * @param value valor do tipo ArrayList* a ser atribuído na variável a ser criada
 */
#define LIST_LET_ARRAY_LIST(varname, value) \
    LinkedList* __##varname##_linked_list = NULL;\
    ArrayList* __##varname##_array_list = value

/**
 * Atribui em LIST um LIST
 *
 * @param varname nome da variável que terá seu valor alterado
 * @param valuename nome da variável que será atribuída em "varname"
 */
#define LIST_SET(varname, valuename) \
    __##varname##_linked_list = __##valuename##_linked_list;\
    __##varname##_array_list = __##valuename##_array_list
/**
 * Atribui em LIST um LinkedList*
 *
 * @param varname nome da variável que terá seu valor alterado
 * @param value valor do tipo LinkedList* a ser atribuido na variável "varname"
 */
#define LIST_SET_LINKED_LIST(varname, value) \
    __##varname##_linked_list = value;\
    __##varname##_array_list =NULL
/**
 * Atribui em LIST um ArrayList*
 *
 * @param varname nome da variável que terá seu valor alterado
 * @param value valor do tipo ArrayList* a ser atribuido na variável "varname"
 */
#define LIST_SET_ARRAY_LIST(varname, value) \
    __##varname##_linked_list = NULL;\
    __##varname##_array_list = value

/**
 * Declara LIST
 *
 * @param varname nome da variável a ser criada
 * @param valuename nome da variável que será atribuída na variável criada
 */
#define LIST_DECLARE(varname) \
    LinkedList* __##varname##_linked_list;\
    ArrayList* __##varname##_array_list

/**
 * Atribui em LIST um LIST, fornecendo "prefix". Prefix pode ser, por exemplo, uma estrutura seguido por "." ou "->".
 * Se não houver prefixo, basta passar LIST_NO_PREFIX
 *
 * @param prefix_varname prefixo de "varname"
 * @param varname nome da variável que terá seu valor alterado
 * @param prefix_valuename prefixo de "valuename"
 * @param valuename nome da variável que será atribuída em "varname"
 */
#define LIST_SET_PREFIX(prefix_varname, varname, prefix_valuename, valuename) \
    prefix_varname##__##varname##_linked_list = prefix_valuename##__##valuename##_linked_list;\
    prefix_varname##__##varname##_array_list = prefix_valuename##__##valuename##_array_list
/**
 * Atribui em LIST um LinkedList*, fornecendo um "prefix". Prefix pode ser, por exemplo, uma estrutura seguido por "." ou "->".
 * Se não houver prefixo, basta passar LIST_NO_PREFIX
 *
 * @param prefix prefixo de "varname"
 * @param varname nome da variável que terá seu valor alterado
 * @param value valor do tipo LinkedList* a ser atribuido na variável "varname"
 */
#define LIST_SET_PREFIX_LINKED_LIST(prefix, varname, value) \
    prefix##__##varname##_linked_list = value;\
    prefix##__##varname##_array_list = NULL
/**
 * Atribui em LIST um ArrayList*, fornecendo um "prefix". Prefix pode ser, por exemplo, uma estrutura seguido por "." ou "->".
 * Se não houver prefixo, basta passar LIST_NO_PREFIX
 *
 * @param prefix prefixo de "varname"
 * @param varname nome da variável que terá seu valor alterado
 * @param value valor do tipo ArrayList* a ser atribuido na variável "varname"
 */
#define LIST_SET_PREFIX_ARRAY_LIST(prefix, varname, value) \
    prefix##__##varname##_linked_list = NULL;\
    prefix##__##varname##_array_list = value

// ### MÉTODOS ###

/**
 * Busca a referência do elemento do LIST que possui a posição fornecida
 *
 * @param varname instância de LIST
 * @param index posição do alemento a ser buscado
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
#define LIST_FIND_BY_INDEX(varname, index) \
    __##varname##_linked_list != NULL ? linked_list_find_by_index(__##varname##_linked_list, index) : \
    array_list_find_by_index(__##varname##_array_list, index)

/**
 * Busca a posição no LIST da referência fornecida
 *
 * @param varname instância de LIST
 * @param value referência a ser buscada
 * @return posição na LIST da referência. -1 se não for encontrada
 */
#define LIST_FIND_INDEX_BY_REFERENCE(varname, value) \
    __##varname##_linked_list != NULL ? linked_list_find_index_by_reference(__##varname##_linked_list, value) : \
    array_list_find_index_by_reference(__##varname##_array_list, value)

/**
 * Adiciona no final do LIST um valor
 *
 * @param varname instância de LIST que receberá o valor
 * @param value valor a ser adicionado no final do LIST
 */
#define LIST_ADD(varname, value) \
    __##varname##_linked_list != NULL ? linked_list_add(__##varname##_linked_list, value) : \
    array_list_add(__##varname##_array_list, value)

/**
 * Adiciona um elemento no LIST na posicao informada
 *
 * @param varname instância de LIST
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 */
#define LIST_ADD_AT(varname, value, index) \
    __##varname##_linked_list != NULL ? linked_list_add_at(__##varname##_linked_list, value, index) : \
    array_list_add_at(__##varname##_array_list, value, index)

/**
 * Remove do LIST e apaga da memoria a refêrencia fornecida
 *
 * @param varname instância de LIST
 * @param value valor a ser removido do LIST e apagado da memória
 * @return 0 se a referência foi encontrada, removida de LIST e apagada da memória
 */
#define LIST_ERASER_BY_REFERENCE(varname, value) \
    __##varname##_linked_list != NULL ? linked_list_eraser_by_reference(__##varname##_linked_list, value) : \
    array_list_eraser_by_reference(__##varname##_array_list, value)

/**
 * Remove do LIST e apaga elemento da memoria que possui a posição
 * fornecida
 *
 * @param varname instância de LIST
 * @param index posição a ter o elemento removido do LIST e apagado
 *        da memória
 */
#define LIST_ERASER_AT(varname, index) \
    __##varname##_linked_list != NULL ? linked_list_eraser_at(__##varname##_linked_list, index) : \
    array_list_eraser_at(__##varname##_array_list, index)

/**
 * Remove do LIST sem apagar da memoria a refêrencia fornecida
 *
 * @param varname instância de LIST
 * @param value valor a ser removido do LIST sem ser apagado da
 *        memória
 * @return 0 se a referência foi encontrada e removida de LIST
 */
#define LIST_REMOVE_BY_REFERENCE(varname, value) \
    __##varname##_linked_list != NULL ? linked_list_remove_by_reference(__##varname##_linked_list, value) : \
    array_list_remove_by_reference( __##varname##_array_list, value)

/**
 * Remove do LIST sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param varname instância de LIST
 * @param index posição a ter o elemento removido do LIST sem ser
 *        apagado da memória
 * @return referência removida de LIST
 */
#define LIST_REMOVE_AT(varname, index) \
    __##varname##_linked_list != NULL ? linked_list_remove_at(__##varname##_linked_list, index) : \
    array_list_remove_at(__##varname##_array_list, index)

/**
 * Remove os elementos de LIST sem apagar os elementos da memoria.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_CLEAR(varname) \
    __##varname##_linked_list != NULL ? linked_list_clear(__##varname##_linked_list) : \
    array_list_clear(__##varname##_array_list)

/**
 * Remove os elementos de LIST e apaga os elementos da memoria.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_CLEAR_ERASER(varname) \
    __##varname##_linked_list != NULL ? linked_list_clear_eraser(__##varname##_linked_list) : \
    array_list_clear_eraser(__##varname##_array_list)

/**
 * Remove os elementos de LIST e apaga os elementos da memoria, usando destrutor.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_CLEAR_ERASER_DESTRUCTOR(varname, destructor) \
    __##varname##_linked_list != NULL ? linked_list_clear_eraser_destructor(__##varname##_linked_list, destructor) : \
    array_list_clear_eraser_destructor(__##varname##_array_list, destructor)

/**
 * Percorre cada elemento do LIST e passa o valor e
 * posição para "callback"

 * @param varname instância de LIST
 * @param callback função que receberá cada valor e posição
 *        presente no LinkedList. "callback" deve retornar
 *        1 para continuar a iteração. 0 para que o comando
 *        break seja executado
 */
#define LIST_FOR_EACH(varname, callback) \
    __##varname##_linked_list != NULL ? linked_list_for_each(__##varname##_linked_list, callback) : \
    array_list_for_each(__##varname##_array_list, callback)

#endif // INTERFACE_LIST_H_INCLUDED