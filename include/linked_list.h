#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stdlib.h>

typedef struct __st_linked_list_element {
    void* value;
    struct __st_linked_list_element* next;
} LinkedListElement;

typedef struct __st_linked_list {
    // public
    int size;

    // private
    LinkedListElement* __head;
    LinkedListElement* __last;
} LinkedList;

/**
 * Obtém o head do LinkedList que aponta para o primeiro elemento da lista
 *
 * @param linked_list instância do LinkedList
 * @return o head do LinkedList que aponta para o primeiro elemento da lista
 */
LinkedListElement* linked_list_head(LinkedList* linked_list);

/**
 * Obtém o último elemento do LinkedList. Se a lista estiver vazia, retorna-se
 * o head
 *
 * @param linked_list instância do LinkedList
 * @return o último elemento do LinkedList. Se a lista estiver vazia, retorna-se
 *  o head
 */
LinkedListElement* linked_list_last(LinkedList* linked_list);

/**
 * Inicializa uma LinkedList vazia
 *
 * @param linked_list instância do LinkedList a ser inicializada
 */
void linked_list_init(LinkedList* linked_list);

/**
 * Cria um novo elemento vazio para o LinkedList
 *
 * @return novo elemento vazio para o LinkedList
 */
LinkedListElement* new_element ();

/**
 * Cria uma nova LinkedList vazia
 *
 * @return nova lista vazia
 */
LinkedList* new_linked_list();

/**
 * Adiciona valor no inicio do LinkedList
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser adicionado no início do LinkedList
 */
void linked_list_add_top(LinkedList* linked_list, void* value);

/**
 * Retorna o valor do início do LinkedList
 *
 * @param linked_list instância do LinkedList
 */
void* linked_list_top(LinkedList* linked_list);

/**
 * Remove o elemento do início do LinkedList
 *
 * @param linked_list instância do LinkedList
 * @return valor removido do início do LinkedList
 */
void* linked_list_remove_top(LinkedList* linked_list);

/**
 * Remove da lista e apaga da memória o elemento do início do LinkedList
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_eraser_top(LinkedList* linked_list);

/**
 * Busca e retorna o elemento anterior ao elemento da lista que possui a mesma referência de "value"
 *
 * @param linked_list instância do LinkedList
 * @param value referência do valor posterior ao valor que será retornado
 * @return elemento anterior ao elemento que possui a referência recebida
 */
LinkedListElement* linked_list_find_previous_by_reference(LinkedList* linked_list, void* value);

/**
 * Remove do LinkedList e apaga da memória o elemento posterior ao elemento recebido
 *
 * @param linked_list instância do LinkedList
 * @param element elemento anterior ao elemento que será apagado
 */
void linked_list_eraser_next(LinkedList* linked_list, LinkedListElement* element);

/**
 * Remove do LinkedList sem apagar da memória o elemento posterior ao elemento recebido
 *
 * @param linked_list instância do LinkedList
 * @param element elemento anterior ao elemento que será removido
 * @return valor removido do LinkedList
 */
void* linked_list_remove_next(LinkedList* linked_list, LinkedListElement* element);

/**
 * Remove os elementos da lista, sem apagar os elementos do LinkedList da memória, a partir de head.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 * @param head elemento que aponta para o primeiro elemento do LinkedList a ser removido
 */
void linked_list_clear_by_head(LinkedList* linked_list, LinkedListElement* head);

/**
 * Remove os elementos da lista e apaga os elementos do LinkedList da memória, a partir de head.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 * @param head elemento que aponta para o primeiro elemento do LinkedList a ser removido
 */
void linked_list_clear_eraser_by_head(LinkedList* linked_list, LinkedListElement* head);

/**
 * Remove os elementos da lista e apaga os elementos do LinkedList da memória, utilizando destrutor,
 * a partir de head. Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 * @param head elemento que aponta para o primeiro elemento do LinkedList a ser removido
 * @param destructor destrutora para cada elemento do LinkedList
 */
void linked_list_clear_eraser_destructor_by_head(LinkedList* linked_list, LinkedListElement* head, void (*destructor)(void*));

/**
 * Busca um LinkedListElement di LinkedList que possui a posição fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição do elemento a ser buscado
 * @return LinkedListElement* que possui a posição fornecida
 */
LinkedListElement* linked_list_find_element_by_index(LinkedList* linked_list, int index);

/**
 * Busca um LinkedListElement* da lista que possui um valor com a mesma referencia fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value referência que aponta para o valor do LinkedListElement a ser buscado
 */
LinkedListElement* linked_list_find_element_by_reference(LinkedList* linked_list, void* value);

// ### implements interface_list.h ###

/**
 * Busca a referência do elemento do LinkedList que possui a posição fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição do alemento a ser buscado
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* linked_list_find_by_index(LinkedList* array, int index);

/**
 * Busca a referência do elemento do LinkedList que possui a referência fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value referência do valor a ser buscado
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* linked_list_find_by_reference(LinkedList* array, void* value);

/**
 * Adiciona no final do LinkedList um valor
 *
 * @param linked_list instância do LinkedList que receberá o valor
 * @param value valor a ser adicionado no final do LinkedList
 */
void linked_list_add(LinkedList* linked_list, void* value);

/**
 * Adiciona um elemento no LinkedList na posicao informada
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 */
void linked_list_add_at(LinkedList* linked_list, void* value, int index);

/**
 * Remove do LinkedList e apaga da memoria a refêrencia fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser removido do LinkedList e apagado da memória
 */
void linked_list_eraser_by_reference(LinkedList* linked_list, void* value);

/**
 * Remove do LinkedList e apaga elemento da memoria que possui a posição
 * fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição a ter o elemento removido do LinkedList e apagado
 *        da memória
 */
void linked_list_eraser_at(LinkedList* linked_list, int index);

/**
 * Remove do LinkedList sem apagar da memoria a refêrencia fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser removido do LinkedList sem ser apagado da
 *        memória
 */
void linked_list_remove_by_reference(LinkedList* linked_list, void* value);

/**
 * Remove do LinkedList sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição a ter o elemento removido do LinkedList sem ser
 *        apagado da memória
 */
void* linked_list_remove_at(LinkedList* linked_list, int index);

/**
 * Remove os elementos do LinkedList sem apagar os elementos da memoria.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_clear(LinkedList* linked_list);

/**
 * Remove os elementos do LinkedList e apaga os elementos da memoria.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_clear_eraser(LinkedList* linked_list);

/**
 * Remove os elementos do LinkedList e apaga os elementos da memoria, usando destrutor.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_clear_eraser_destructor(LinkedList* linked_list, void (*destructor)(void*));

/**
 * Percorre cada elemento do LinkedList e passa o valor e
 * posição para "callback"

 * @param linked_list instância do LinkedList
 * @param callback função que receberá cada valor e posição
 *        presente no LinkedList. "callback" deve retornar
 *        1 para continuar a iteração. 0 para que o comando
 *        break seja executado
 */
void linked_list_for_each(LinkedList* linked_list, short (*callback)(void*, int));

#endif // LINKED_LIST_H_INCLUDED