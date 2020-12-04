#ifndef C_EMD_UTIL_INTERFACE_LIST_H_INCLUDED
#define C_EMD_UTIL_INTERFACE_LIST_H_INCLUDED

// ### CRIAÇÃO DE DESTRUTORES ###

#define LIST_CREATE_DESTRUCTOR(fn_name, destructor1, destructor2) \
    void fn_name (void* value) {\
        destructor1(value, destructor2);\
    }

// ### CRIAÇÃO E ATRIBUIÇÃO DE VARIÁVEL DA INTERFACE LIST ###

/**
 * Declara LIST em parâmetro de função
 *
 * @param varname nome do parâmetro
 */
#define LIST_PARAM(varname) List* varname##_linked_list__, ArrayList* varname##_array_list__

/**
 * Passa LIST para LIST em parâmetro de função
 *
 * @param valuename nome da variável que possui LIST
 */
#define LIST_ARG(valuename) valuename##_linked_list__, valuename##_array_list__
/**
 * Passa List para LIST em parâmetro de função
 *
 * @param linked_list instância de List
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
    List* varname##_linked_list__ = valuename##_linked_list__;\
    ArrayList* varname##_array_list__ = valuename##_array_list__
/**
 * Declara LIST
 *
 * @param varname nome da variável a ser criada
 * @param valuename nome da variável que será atribuída na variável criada
 */
#define LIST_DECLARE(varname) \
    List* varname##_linked_list__;\
    ArrayList* varname##_array_list__
/**
 * Declara LIST de um List*
 *
 * @param varname nome da variável a ser criada
 * @param value valor do tipo List* a ser atribuído na variável a ser criada
 */
#define LIST_LET_LINKED_LIST(varname, value) \
    List* varname##_linked_list__ = value;\
    ArrayList* varname##_array_list__ = NULL
/**
 * Declara LIST de um ArrayList*
 *
 * @param varname nome da variável a ser criada
 * @param value valor do tipo ArrayList* a ser atribuído na variável a ser criada
 */
#define LIST_LET_ARRAY_LIST(varname, value) \
    List* varname##_linked_list__ = NULL;\
    ArrayList* varname##_array_list__ = value

/**
 * Atribui em LIST um LIST
 *
 * @param varname nome da variável que terá seu valor alterado
 * @param valuename nome da variável que será atribuída em "varname"
 */
#define LIST_SET(varname, valuename) \
    varname##_linked_list__ = valuename##_linked_list__;\
    varname##_array_list__ = valuename##_array_list__
/**
 * Atribui em LIST um List*
 *
 * @param varname nome da variável que terá seu valor alterado
 * @param value valor do tipo List* a ser atribuido na variável "varname"
 */
#define LIST_SET_LINKED_LIST(varname, value) \
    varname##_linked_list__ = value;\
    varname##_array_list__ =NULL
/**
 * Atribui em LIST um ArrayList*
 *
 * @param varname nome da variável que terá seu valor alterado
 * @param value valor do tipo ArrayList* a ser atribuido na variável "varname"
 */
#define LIST_SET_ARRAY_LIST(varname, value) \
    varname##_linked_list__ = NULL;\
    varname##_array_list__ = value

/**
 * Obtém a LIST com o tipo List*. Se o tipo for incompatível, retorna-se NULL
 *
 * @param varname instância de LIST
 */
#define LIST_GET_LINKED_LIST(varname) varname##_linked_list__
/**
 * Obtém a LIST com o tipo ArrayList*. Se o tipo for incompatível, retorna-se NULL
 *
 * @param varname instância de LIST
 */
#define LIST_GET_ARRAY_LIST(varname) varname##_array_list__

// ### MÉTODOS ###

/**
 * Busca a referência do elemento do LIST que possui a posição fornecida
 *
 * @param varname instância de LIST
 * @param index posição do alemento a ser buscado
 * @param err referência para armazenar o valor do erro, caso ocorra
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
#define LIST_GET_AT(varname, index, err) \
    varname##_linked_list__ != NULL ? linked_list_get_at(varname##_linked_list__, index, err) : \
    array_list_get_at(varname##_array_list__, index, err)

/**
 * Atualiza o valor do elemento do LIST que possui a posição fornecida
 *
 * @param varname instância de LIST
 * @param index posição do alemento a ser atualizado
 * @param value valor a ser atribuído
 * @param err referência para armazenar o valor do erro, caso ocorra
 */
#define LIST_SET_AT(varname, index, value, err) \
    varname##_linked_list__ != NULL ? linked_list_set_at(varname##_linked_list__, index, value, err) : \
    array_list_set_at(varname##_array_list__, index, value, err)

/**
 * Busca a posição no LIST da referência fornecida
 *
 * @param varname instância de LIST
 * @param value referência a ser buscada
 * @return posição na LIST da referência. -1 se não for encontrada
 */
#define LIST_FIND_INDEX_BY_REFERENCE(varname, value) \
    varname##_linked_list__ != NULL ? linked_list_find_index_by_reference(varname##_linked_list__, value) : \
    array_list_find_index_by_reference(varname##_array_list__, value)

/**
 * Adiciona no final do LIST um valor
 *
 * @param varname instância de LIST que receberá o valor
 * @param value valor a ser adicionado no final do LIST
 * @param err referência para armazenar o valor do erro, caso ocorra
 */
#define LIST_ADD(varname, valuem, err) \
    varname##_linked_list__ != NULL ? linked_list_add(varname##_linked_list__, value, err) : \
    array_list_add(varname##_array_list__, value, err)

/**
 * Adiciona um elemento no LIST na posicao informada
 *
 * @param varname instância de LIST
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 * @param err referência para armazenar o valor do erro, caso ocorra
 */
#define LIST_ADD_AT(varname, value, index, err) \
    varname##_linked_list__ != NULL ? linked_list_add_at(varname##_linked_list__, value, index, err) : \
    array_list_add_at(varname##_array_list__, value, index, err)

/**
 * Remove do LIST e apaga da memoria a refêrencia fornecida
 *
 * @param varname instância de LIST
 * @param value valor a ser removido do LIST e apagado da memória
 * @return 1 se a referência foi encontrada, removida do List e apagada da memória. 0 caso contrário
 */
#define LIST_ERASER_BY_REFERENCE(varname, value) \
    varname##_linked_list__ != NULL ? linked_list_eraser_by_reference(varname##_linked_list__, value) : \
    array_list_eraser_by_reference(varname##_array_list__, value)

/**
 * Remove do LIST e apaga elemento da memoria que possui a posição
 * fornecida
 *
 * @param varname instância de LIST
 * @param index posição a ter o elemento removido do LIST e apagado
 *        da memória
 * @param err referência para armazenar o valor do erro, caso ocorra
 */
#define LIST_ERASER_AT(varname, index, err) \
    varname##_linked_list__ != NULL ? linked_list_eraser_at(varname##_linked_list__, index, err) : \
    array_list_eraser_at(varname##_array_list__, index, err)

/**
 * Remove do LIST sem apagar da memoria a refêrencia fornecida
 *
 * @param varname instância de LIST
 * @param value valor a ser removido do LIST sem ser apagado da
 *        memória
 * @return 1 se a referência foi encontrada e removida do List. 0 caso contrário
 */
#define LIST_REMOVE_BY_REFERENCE(varname, value) \
    varname##_linked_list__ != NULL ? linked_list_remove_by_reference(varname##_linked_list__, value) : \
    array_list_remove_by_reference(varname##_array_list__, value)

/**
 * Remove do LIST sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param varname instância de LIST
 * @param index posição a ter o elemento removido do LIST sem ser
 *        apagado da memória
 * @param err referência para armazenar o valor do erro, caso ocorra
 * @return referência removida do List
 */
#define LIST_REMOVE_AT(varname, index, err) \
    varname##_linked_list__ != NULL ? linked_list_remove_at(varname##_linked_list__, index, err) : \
    array_list_remove_at(varname##_array_list__, index, err)

/**
 * Remove os elementos de LIST sem apagar os elementos da memoria.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_CLEAR(varname) \
    varname##_linked_list__ != NULL ? linked_list_clear(varname##_linked_list__) : \
    array_list_clear(varname##_array_list__)

/**
 * Remove os elementos de LIST e apaga os elementos da memoria.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_CLEAR_ERASER(varname) \
    varname##_linked_list__ != NULL ? linked_list_clear_eraser(varname##_linked_list__) : \
    array_list_clear_eraser(varname##_array_list__)

/**
 * Remove os elementos de LIST e apaga os elementos da memoria, usando destrutor.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_CLEAR_ERASER_DESTRUCTOR(varname, destructor) \
    varname##_linked_list__ != NULL ? linked_list_clear_eraser_destructor(varname##_linked_list__, destructor) : \
    array_list_clear_eraser_destructor(varname##_array_list__, destructor)

/**
 * Remove os elementos de LIST sem apagar os elementos da memoria.
 * Apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_FREE(varname) \
    varname##_linked_list__ != NULL ? linked_list_free(varname##_linked_list__) : \
    array_list_free(varname##_array_list__)

/**
 * Remove os elementos de LIST e apaga os elementos da memoria.
 * Apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_FREE_ERASER(varname) \
    varname##_linked_list__ != NULL ? linked_list_free_eraser(varname##_linked_list__) : \
    array_list_free_eraser(varname##_array_list__)

/**
 * Remove os elementos de LIST e apaga os elementos da memoria, usando destrutor.
 * Apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_FREE_ERASER_DESTRUCTOR(varname, destructor) \
    varname##_linked_list__ != NULL ? linked_list_free_eraser_destructor(varname##_linked_list__, destructor) : \
    array_list_free_eraser_destructor(varname##_array_list__, destructor)

/**
 * Percorre cada elemento do LIST e passa o valor e
 * posição para "callback"

 * @param varname instância de LIST
 * @param callback função que receberá cada valor e posição
 *        presente no List. "callback" deve retornar
 *        1 para continuar a iteração. 0 para que o comando
 *        break seja executado
 */
#define LIST_FOR_EACH(varname, callback) \
    varname##_linked_list__ != NULL ? linked_list_for_each(varname##_linked_list__, callback) : \
    array_list_for_each(varname##_array_list__, callback)

// ### REFERÊNCIAS DOS MÉTODOS ###

/**
 * Busca a referência do elemento do LIST que possui a posição fornecida
 *
 * @param varname instância de LIST
 * @param index posição do alemento a ser buscado
 * @param err referência para armazenar o valor do erro, caso ocorra
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
#define LIST_REF_GET_AT \
    varname##_linked_list__ != NULL ? linked_list_get_at : array_list_get_at

/**
 * Atualiza o valor do elemento do LIST que possui a posição fornecida
 *
 * @param varname instância de LIST
 * @param index posição do alemento a ser atualizado
 * @param value valor a ser atribuído
 * @param err referência para armazenar o valor do erro, caso ocorra
 */
#define LIST_REF_SET_AT \
    varname##_linked_list__ != NULL ? linked_list_set_at : array_list_set_at

/**
 * Busca a posição no LIST da referência fornecida
 *
 * @param varname instância de LIST
 * @param value referência a ser buscada
 * @return posição na LIST da referência. -1 se não for encontrada
 */
#define LIST_REF_FIND_INDEX_BY_REFERENCE \
    varname##_linked_list__ != NULL ? linked_list_find_index_by_reference : array_list_find_index_by_reference

/**
 * Adiciona no final do LIST um valor
 *
 * @param varname instância de LIST que receberá o valor
 * @param value valor a ser adicionado no final do LIST
 * @param err referência para armazenar o valor do erro, caso ocorra
 */
#define LIST_REF_ADD \
    varname##_linked_list__ != NULL ? linked_list_add : array_list_add

/**
 * Adiciona um elemento no LIST na posicao informada
 *
 * @param varname instância de LIST
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 * @param err referência para armazenar o valor do erro, caso ocorra
 */
#define LIST_REF_ADD_AT \
    varname##_linked_list__ != NULL ? linked_list_add_at : array_list_add_at

/**
 * Remove do LIST e apaga da memoria a refêrencia fornecida
 *
 * @param varname instância de LIST
 * @param value valor a ser removido do LIST e apagado da memória
 * @return 1 se a referência foi encontrada, removida do List e apagada da memória. 0 caso contrário
 */
#define LIST_REF_ERASER_BY_REFERENCE \
    varname##_linked_list__ != NULL ? linked_list_eraser_by_reference : array_list_eraser_by_reference

/**
 * Remove do LIST e apaga elemento da memoria que possui a posição
 * fornecida
 *
 * @param varname instância de LIST
 * @param index posição a ter o elemento removido do LIST e apagado
 *        da memória
 * @param err referência para armazenar o valor do erro, caso ocorra
 */
#define LIST_REF_ERASER_AT \
    varname##_linked_list__ != NULL ? linked_list_eraser_at : array_list_eraser_at

/**
 * Remove do LIST sem apagar da memoria a refêrencia fornecida
 *
 * @param varname instância de LIST
 * @param value valor a ser removido do LIST sem ser apagado da
 *        memória
 * @return 1 se a referência foi encontrada e removida do List. 0 caso contrário
 */
#define LIST_REF_REMOVE_BY_REFERENCE \
    varname##_linked_list__ != NULL ? linked_list_remove_by_reference : array_list_remove_by_reference

/**
 * Remove do LIST sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param varname instância de LIST
 * @param index posição a ter o elemento removido do LIST sem ser
 *        apagado da memória
 * @param err referência para armazenar o valor do erro, caso ocorra
 * @return referência removida do List
 */
#define LIST_REF_REMOVE_AT \
    varname##_linked_list__ != NULL ? linked_list_remove_at : array_list_remove_at

/**
 * Remove os elementos de LIST sem apagar os elementos da memoria.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_REF_CLEAR \
    varname##_linked_list__ != NULL ? linked_list_clear : array_list_clear

/**
 * Remove os elementos de LIST e apaga os elementos da memoria.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_REF_CLEAR_ERASER \
    varname##_linked_list__ != NULL ? linked_list_clear_eraser : array_list_clear_eraser

/**
 * Remove os elementos de LIST e apaga os elementos da memoria, usando destrutor.
 * Não apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_REF_CLEAR_ERASER_DESTRUCTOR \
    varname##_linked_list__ != NULL ? linked_list_clear_eraser_destructor : array_list_clear_eraser_destructor

/**
 * Remove os elementos de LIST sem apagar os elementos da memoria.
 * Apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_REF_FREE \
    varname##_linked_list__ != NULL ? linked_list_free : array_list_free

/**
 * Remove os elementos de LIST e apaga os elementos da memoria.
 * Apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_REF_FREE_ERASER \
    varname##_linked_list__ != NULL ? linked_list_free_eraser : array_list_free_eraser

/**
 * Remove os elementos de LIST e apaga os elementos da memoria, usando destrutor.
 * Apaga LIST da memória
 *
 * @param varname instância de LIST
 */
#define LIST_REF_FREE_ERASER_DESTRUCTOR \
    varname##_linked_list__ != NULL ? linked_list_free_eraser_destructor : array_list_free_eraser_destructor

/**
 * Percorre cada elemento do LIST e passa o valor e
 * posição para "callback"

 * @param varname instância de LIST
 * @param callback função que receberá cada valor e posição
 *        presente no List. "callback" deve retornar
 *        1 para continuar a iteração. 0 para que o comando
 *        break seja executado
 */
#define LIST_REF_FOR_EACH \
    varname##_linked_list__ != NULL ? linked_list_for_each : array_list_for_each

#endif // C_EMD_UTIL_INTERFACE_LIST_H_INCLUDED