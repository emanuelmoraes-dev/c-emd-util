#include "linked_list.h"

// retorna um novo elemento vazio para lista
LinkedListElement* new_element () {
    LinkedListElement* elemento = (LinkedListElement*) malloc(sizeof(LinkedListElement));

    elemento->value = NULL;
    elemento->next = NULL;

    return elemento;
}

// cria e retorna uma nova lista vazia
LinkedList* new_linked_list() {
    LinkedList* lista = (LinkedList*) malloc(sizeof(LinkedList));
    lista->head = new_element();
    lista->last = lista->head;
    lista->size = 0;
    return lista;
}

// adiciona um elemento na lista
void linked_list_add(LinkedList* linked_list, void* value) {
    linked_list->last->next = new_element();
    linked_list->last->next->value = value;
    linked_list->last = linked_list->last->next;
    linked_list->size++;
}

// busca um elemento da lista que possui a posição fornecida pelo usuario
LinkedListElement* linked_list_find_by_index(LinkedList* linked_list, int index) {
    int id = -1;
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (id++ == index)
            return it;
    return NULL;
}

// adiciona um elemento na lista na posicao informada
void linked_list_add_at(LinkedList* linked_list, void* value, int index) {
    LinkedListElement* ant = linked_list_find_by_index(linked_list, index-1);
    LinkedListElement* prx = ant->next;
    ant->next = new_element();
    ant->next->value = value;
    ant->next->next = prx;
    if (prx == NULL)
        linked_list->last = ant->next;
    linked_list->size++;
}

// apaga da memoria o elemento que vem depois do elemento recebido
void linked_list_eraser_next(LinkedList* linked_list, LinkedListElement* element) {
    if (linked_list->size == 0)
        return;
    LinkedListElement* alvo = element->next; // LinkedListElement que eu quero remover
    element->next = alvo->next; // Alvo é excluido da lista
    free(alvo->value); // Valor do alvo é excluido da memória
    free(alvo); // Alvo é excluido da memária RAM
    linked_list->size--;
}

// apaga da memoria o elemento recebido, o elemento mesmo
void linked_list_eraser_by_value(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it->next != NULL; it = it->next) {
        if (it->next->value == value) {
            linked_list_eraser_next(linked_list, it);
            break;
        }
    }
}

// apaga elemento da memoria que possui o id recebido , o elemento mesmo
void linked_list_eraser_at(LinkedList* linked_list, int index) {
    LinkedListElement* c = linked_list_find_by_index(linked_list, index-1);
    linked_list_eraser_next(linked_list, c);
}

// remove da lista sem remover da memoria o elemento que vem depois do elemento recebido
void* linked_list_remove_next(LinkedList* linked_list, LinkedListElement* element) {
    if (linked_list->size == 0)
        return NULL;
    LinkedListElement* alvo = element->next; // LinkedListElement que eu quero remover
    element->next = alvo->next; // Alvo é excluido da lista
    void* value = alvo->value;
    free(alvo); // Alvo é excluido da memária RAM
    linked_list->size--;
    return value;
}

// remove  da lista sem remover da memoria o elemento recebido, o elemento mesmo
void linked_list_remove_by_value(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it->next != NULL; it = it->next) {
        if (it->next->value == value) {
            linked_list_remove_next(linked_list, it);
        }
    }
}

// remove da lista sem remover da memoria o elemento que possui o id recebido
void* linked_list_remove_at(LinkedList* linked_list, int index) {
    LinkedListElement* c = linked_list_find_by_index(linked_list, index-1);
    return linked_list_remove_next(linked_list, c);
}

// apaga a lista e os elementos da lista da memoria
void linked_list_free_eraser(LinkedList* linked_list, LinkedListElement* element) {
    if (element == NULL) return;
    if (element->next == NULL) return;
    linked_list_free_eraser(linked_list, element->next);
    linked_list_eraser_next(linked_list, element);
}

// apaga a lista e os elementos são apagados por meio de função destrutora
void linked_list_free_eraser_destrutor(LinkedList* linked_list, LinkedListElement* element, void (*destrutor)(void*)) {
    if (element == NULL) return;
    if (element->next == NULL) return;
    linked_list_free_eraser_destrutor(linked_list, element->next, destrutor);
    void* value = linked_list_remove_next(linked_list, element);
    destrutor(value);
}

// remove a lista da memoria sem remover os contatdos da lista da memoria
void linked_list_free(LinkedList* linked_list, LinkedListElement* element) {
    if (element == NULL) return;
    if (element->next == NULL) return;
    linked_list_free(linked_list, element->next);
    linked_list_remove_next(linked_list, element);
}

// Adiciona no linked_list_top da lista
void linked_list_add_top(LinkedList* linked_list, void* value) {
    linked_list_add_at(linked_list, value, 0);
}

// Retorna o value do linked_list_top da lista
void* linked_list_top(LinkedList* linked_list) {
    if (linked_list->size == 0)
        return NULL;
    return linked_list->head->next->value;
}

// Remove elemento do linked_list_top da lista
void* linked_list_remove_top(LinkedList* linked_list) {
    return linked_list_remove_next(linked_list, linked_list->head);
}

// Remove e apaga da memória elemento do linked_list_top da lista
void linked_list_eraser_top(LinkedList* linked_list) {
    linked_list_eraser_next(linked_list, linked_list->head);
}