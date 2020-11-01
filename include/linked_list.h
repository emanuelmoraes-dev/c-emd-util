#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stdlib.h>

typedef struct st_linked_list_element {
    void* value;
    struct st_linked_list_element* next;
} LinkedListElement;

typedef struct st_linked_list {
    LinkedListElement* head;
    LinkedListElement* last;
    int size;
} LinkedList;

// retorna um novo elemento vazio para lista
LinkedListElement* new_element ();

// cria e retorna uma nova lista vazia
LinkedList* new_linked_list();

// adiciona um elemento na lista
void linked_list_add(LinkedList* linked_list, void* value);

// busca um elemento da lista que possui a posição fornecida pelo usuario
LinkedListElement* linked_list_find_by_index(LinkedList* linked_list, int index);

// adiciona um elemento na lista na posicao informada
void linked_list_add_at(LinkedList* linked_list, void* value, int index);

// apaga da memoria o elemento que vem depois do elemento recebido
void linked_list_eraser_next(LinkedList* linked_list, LinkedListElement* element);

// apaga da memoria o elemento recebido, o elemento mesmo
void linked_list_eraser_by_value(LinkedList* linked_list, void* value);

// apaga elemento da memoria que possui o id recebido , o elemento mesmo
void linked_list_eraser_at(LinkedList* linked_list, int index);

// remove da lista sem remover da memoria o elemento que vem depois do elemento recebido
void* linked_list_remove_next(LinkedList* linked_list, LinkedListElement* element);

// remove  da lista sem remover da memoria o elemento recebido, o elemento mesmo
void linked_list_remove_by_value(LinkedList* linked_list, void* value);

// remove da lista sem remover da memoria o elemento que possui o id recebido
void* linked_list_remove_at(LinkedList* linked_list, int index);

// apaga a lista e os elementos da lista da memoria
void linked_list_free_eraser(LinkedList* linked_list, LinkedListElement* element);

// apaga a lista e os elementos são apagados por meio de função destrutora
void linked_list_free_eraser_destrutor(LinkedList* linked_list, LinkedListElement* element, void (*destrutor)(void*));

// remove a lista da memoria sem remover os contatdos da lista da memoria
void linked_list_free(LinkedList* linked_list, LinkedListElement* element);

// Adiciona no linked_list_top da lista
void linked_list_add_top(LinkedList* linked_list, void* value);

// Retorna o value do linked_list_top da lista
void* linked_list_top(LinkedList* linked_list);

// Remove elemento do linked_list_top da lista
void* linked_list_remove_top(LinkedList* linked_list);

// Remove e apaga da memória elemento do linked_list_top da lista
void linked_list_eraser_top(LinkedList* linked_list);

#endif // LINKED_LIST_H_INCLUDED