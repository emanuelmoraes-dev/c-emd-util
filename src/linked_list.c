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

// busca um elemento antes do elemento da lista que possui a mesma referencia fornecida
LinkedListElement* linked_list_find_previous_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (it->next != NULL && it->next->value == value)
            return it;
    return NULL;
}

// remove da lista e apaga da memoria a refêrencia fornecida
void linked_list_eraser_next(LinkedList* linked_list, LinkedListElement* element) {
    if (linked_list->size == 0)
        return;
    LinkedListElement* alvo = element->next; // LinkedListElement que eu quero remover
    element->next = alvo->next; // Alvo é excluido da lista
    free(alvo->value); // Valor do alvo é excluido da memória
    free(alvo); // Alvo é excluido da memária RAM
    linked_list->size--;
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

// remove a lista da memoria sem remover os contatos da lista da memoria, a partir de head
void linked_list_free_by_head(LinkedList* linked_list, LinkedListElement* head) {
    if (head == NULL) return;
    if (head->next == NULL) return;
    linked_list_free_by_head(linked_list, head->next);
    linked_list_remove_next(linked_list, head);
}

// apaga a lista e os elementos da lista da memoria a partir do head
void linked_list_free_eraser_by_head(LinkedList* linked_list, LinkedListElement* head) {
    if (head == NULL) return;
    if (head->next == NULL) return;
    linked_list_free_eraser_by_head(linked_list, head->next);
    linked_list_eraser_next(linked_list, head);
}

// apaga a lista e os elementos são apagados por meio de função destrutora, a partir de head
void linked_list_free_eraser_destructor_by_head(LinkedList* linked_list, LinkedListElement* head, void (*destructor)(void*)) {
    if (head == NULL) return;
    if (head->next == NULL) return;
    linked_list_free_eraser_destructor_by_head(linked_list, head->next, destructor);
    void* value = linked_list_remove_next(linked_list, head);
    destructor(value);
}

// busca um LinkedListElement da lista que possui a posição fornecida
LinkedListElement* linked_list_find_element_by_index(LinkedList* linked_list, int index) {
    int id = -1;
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (id++ == index)
            return it;
    return NULL;
}

// busca um LinkedListElement da lista que possui a mesma referencia fornecida
LinkedListElement* linked_list_find_element_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (it->value == value)
            return it;
    return NULL;
}

// ################## MÉTODOS DO COLLECTION ##################

// busca a referencia do elemento do LinkedList que possui a posição fornecida
void* linked_list_find_by_index(LinkedList* linked_list, int index) {
    int id = -1;
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (id++ == index)
            return it->value;
    return NULL;
}

// busca a referencia do elemento do LinkedList que possui a referência fornecida
void* linked_list_find_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (it->value == value)
            return it->value;
    return NULL;
}

// adiciona um elemento no fim da lista
void linked_list_add(LinkedList* linked_list, void* value) {
    linked_list->last->next = new_element();
    linked_list->last->next->value = value;
    linked_list->last = linked_list->last->next;
    linked_list->size++;
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

// remove da lista e apaga da memoria a referência fornecida
void linked_list_eraser_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it->next != NULL; it = it->next) {
        if (it->next->value == value) {
            linked_list_eraser_next(linked_list, it);
            break;
        }
    }
}

// remove da lista e apaga elemento da memoria que possui o identificado recebido
void linked_list_eraser_at(LinkedList* linked_list, int index) {
    LinkedListElement* c = linked_list_find_by_index(linked_list, index-1);
    linked_list_eraser_next(linked_list, c);
}

// remove  da lista sem remover da memoria a referencia fornecida
void linked_list_remove_by_reference(LinkedList* linked_list, void* value) {
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

/*
Apaga o LinkedList sem apagar os elementos da memoria
*/
void linked_list_free(LinkedList* linked_list) {
    linked_list_free_by_head(linked_list, linked_list->head);
}

/*
Apaga o LinkedList e os elementos da lista e da memoria
*/
void linked_list_free_eraser(LinkedList* linked_list) {
    linked_list_free_eraser_by_head(linked_list, linked_list->head);
}

/*
Apaga o LinkedList e os elementos da lista e da memoria
*/
void linked_list_free_eraser_destructor(LinkedList* linked_list, void (*destructor)(void*)) {
    linked_list_free_eraser_destructor_by_head(linked_list, linked_list->head, destructor);
}

/*
Percorre cada elemento do LinkedList e passa o valor e
posição para "callback"
*/
void linked_list_for_each(LinkedList* linked_list, void (*callback)(void*, int)) {
    if (linked_list == NULL || linked_list->head == NULL || linked_list->head->next == NULL)
        return;

    int index = 0;

    for (LinkedListElement* it = linked_list->head->next; it != NULL; it = it->next)
        callback(it->value, index++);
}