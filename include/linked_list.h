#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stdlib.h>

typedef struct __st_linked_list_element {
    void* value;
    struct __st_linked_list_element* next;
} LinkedListElement;

typedef struct __st_linked_list {
    LinkedListElement* head;
    LinkedListElement* last;
    int size;
} LinkedList;

/*
Cria um novo elemento vazio para o LinkedList

@return novo elemento vazio para o LinkedList
*/
LinkedListElement* new_element ();

/*
Cria uma nova lista vazia

@return nova lista vazia
*/
LinkedList* new_linked_list();

/*
Adiciona valor no inicio do LinkedList

@param linked_list instância do LinkedList
@param value valor a ser adicionado no início do LinkedList
*/
void linked_list_add_top(LinkedList* linked_list, void* value);

/*
Retorna o valor do início do LinkedList

@param linked_list instância do LinkedList
*/
void* linked_list_top(LinkedList* linked_list);

/*
Remove o elemento do início do LinkedList

@param linked_list instância do LinkedList
@return valor removido do início do LinkedList
*/
void* linked_list_remove_top(LinkedList* linked_list);

// Remove e apaga da memória elemento do linked_list_top da lista
/*
Remove da lista e apaga da memória o elemento do início do LinkedList

@param linked_list instância do LinkedList
*/
void linked_list_eraser_top(LinkedList* linked_list);

// busca um elemento antes do elemento da lista que possui a mesma referencia fornecida
/*
Busca e retorna o elemento anterior ao elemento da lista que possui a mesma referência de "value"

@param linked_list instância do LinkedList
@param value referência do valor posterior ao valor que será retornado
@return elemento anterior ao elemento que possui a referência recebida
*/
LinkedListElement* linked_list_find_previous_by_reference(LinkedList* linked_list, void* value);

// apaga da memoria o elemento que vem depois do elemento recebido
/*
Remove do LinkedList e apaga da memória o elemento posterior ao elemento recebido

@param linked_list instância do LinkedList
@param element elemento anterior ao elemento que será apagado
*/
void linked_list_eraser_next(LinkedList* linked_list, LinkedListElement* element);

// remove da lista sem remover da memoria o elemento que vem depois do elemento recebido
/*
Remove do LinkedList sem apagar da memória o elemento posterior ao elemento recebido

@param linked_list instância do LinkedList
@param element elemento anterior ao elemento que será removido
@return valor removido do LinkedList
*/
void* linked_list_remove_next(LinkedList* linked_list, LinkedListElement* element);

// remove a lista da memoria sem remover os contatos da lista da memoria, a partir de head
void linked_list_free_by_head(LinkedList* linked_list, LinkedListElement* head);

// apaga a lista e os elementos da lista da memoria a partir do head
void linked_list_free_eraser_by_head(LinkedList* linked_list, LinkedListElement* head);

// apaga a lista e os elementos são apagados por meio de função destrutora, a partir de head
void linked_list_free_eraser_destructor_by_head(LinkedList* linked_list, LinkedListElement* head, void (*destructor)(void*));

// busca um LinkedListElement da lista que possui a posição fornecida
LinkedListElement* linked_list_find_element_by_index(LinkedList* linked_list, int index);

// busca um LinkedListElement da lista que possui a mesma referencia fornecida
LinkedListElement* linked_list_find_element_by_reference(LinkedList* linked_list, void* value);

// ### implements interface_list.h ###

/*
Busca a referencia do elemento do LinkedList que possui a posição fornecida
*/
void* linked_list_find_by_index(LinkedList* array, int index);

/*
Busca a referencia do elemento do LinkedList que possui a referência fornecida
*/
void* linked_list_find_by_reference(LinkedList* array, void* value);

// adiciona um elemento no fim na lista
void linked_list_add(LinkedList* linked_list, void* value);

// adiciona um elemento na lista na posicao informada
void linked_list_add_at(LinkedList* linked_list, void* value, int index);

// remove da lista e apaga da memoria a refêrencia fornecida
void linked_list_eraser_by_reference(LinkedList* linked_list, void* value);

// remove da lista e apaga elemento da memoria que possui o identificado recebido
void linked_list_eraser_at(LinkedList* linked_list, int index);

// remove da lista sem remover da memoria a refêrencia fornecida
void linked_list_remove_by_reference(LinkedList* linked_list, void* value);

// remove da lista sem remover da memoria o elemento que possui o id recebido
void* linked_list_remove_at(LinkedList* linked_list, int index);

/*
Apaga o LinkedList sem apagar os elementos da memoria
*/
void linked_list_free(LinkedList* linked_list);

/*
Apaga o LinkedList e os elementos da lista e da memoria
*/
void linked_list_free_eraser(LinkedList* linked_list);

/*
Apaga o LinkedList e os elementos da lista e da memoria
*/
void linked_list_free_eraser_destructor(LinkedList* linked_list, void (*destructor)(void*));

/*
Percorre cada elemento do LinkedList e passa o valor e
posição para "callback"
*/
void linked_list_for_each(LinkedList* linked_list, void (*callback)(void*, int));

#endif // LINKED_LIST_H_INCLUDED