#include "linked_list.h"

/**
 * Inicializa uma LinkedList vazia
 *
 * @param linked_list instância do LinkedList a ser inicializada
 */
void linked_list_init(LinkedList* linked_list) {
    linked_list->head = new_element();
    linked_list->last = linked_list->head;
    linked_list->size = 0;
}

/**
 * Cria um novo elemento vazio para o LinkedList
 *
 * @return novo elemento vazio para o LinkedList
 */
LinkedListElement* new_element () {
    LinkedListElement* elemento = (LinkedListElement*) malloc(sizeof(LinkedListElement));

    elemento->value = NULL;
    elemento->next = NULL;

    return elemento;
}

/**
 * Cria uma nova LinkedList vazia
 *
 * @return nova lista vazia
 */
LinkedList* new_linked_list() {
    LinkedList* lista = (LinkedList*) malloc(sizeof(LinkedList));
    linked_list_init(lista);
    return lista;
}

/**
 * Adiciona valor no inicio do LinkedList
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser adicionado no início do LinkedList
 */
void linked_list_add_top(LinkedList* linked_list, void* value) {
    linked_list_add_at(linked_list, value, 0);
}

/**
 * Retorna o valor do início do LinkedList
 *
 * @param linked_list instância do LinkedList
 */
void* linked_list_top(LinkedList* linked_list) {
    if (linked_list->size == 0)
        return NULL;
    return linked_list->head->next->value;
}

/**
 * Remove o elemento do início do LinkedList
 *
 * @param linked_list instância do LinkedList
 * @return valor removido do início do LinkedList
 */
void* linked_list_remove_top(LinkedList* linked_list) {
    return linked_list_remove_next(linked_list, linked_list->head);
}

/**
 * Remove da lista e apaga da memória o elemento do início do LinkedList
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_eraser_top(LinkedList* linked_list) {
    linked_list_eraser_next(linked_list, linked_list->head);
}

/**
 * Busca e retorna o elemento anterior ao elemento da lista que possui a mesma referência de "value"
 *
 * @param linked_list instância do LinkedList
 * @param value referência do valor posterior ao valor que será retornado
 * @return elemento anterior ao elemento que possui a referência recebida
 */
LinkedListElement* linked_list_find_previous_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (it->next != NULL && it->next->value == value)
            return it;
    return NULL;
}

/**
 * Remove do LinkedList e apaga da memória o elemento posterior ao elemento recebido
 *
 * @param linked_list instância do LinkedList
 * @param element elemento anterior ao elemento que será apagado
 */
void linked_list_eraser_next(LinkedList* linked_list, LinkedListElement* element) {
    if (linked_list->size == 0)
        return;
    LinkedListElement* alvo = element->next; // LinkedListElement que eu quero remover
    element->next = alvo->next; // Alvo é excluido da lista
    free(alvo->value); // Valor do alvo é excluido da memória
    free(alvo); // Alvo é excluido da memária RAM
    linked_list->size--;
}

/**
 * Remove do LinkedList sem apagar da memória o elemento posterior ao elemento recebido
 *
 * @param linked_list instância do LinkedList
 * @param element elemento anterior ao elemento que será removido
 * @return valor removido do LinkedList
 */
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

/**
 * Remove os elementos da lista, sem apagar os elementos do LinkedList da memória, a partir de head.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 * @param head elemento que aponta para o primeiro elemento do LinkedList a ser removido
 */
void linked_list_clear_by_head(LinkedList* linked_list, LinkedListElement* head) {
    if (head == NULL) return;
    if (head->next == NULL) return;
    linked_list_clear_by_head(linked_list, head->next);
    linked_list_remove_next(linked_list, head);
}

/**
 * Remove os elementos da lista e apaga os elementos do LinkedList da memória, a partir de head.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 * @param head elemento que aponta para o primeiro elemento do LinkedList a ser removido
 */
void linked_list_clear_eraser_by_head(LinkedList* linked_list, LinkedListElement* head) {
    if (head == NULL) return;
    if (head->next == NULL) return;
    linked_list_clear_eraser_by_head(linked_list, head->next);
    linked_list_eraser_next(linked_list, head);
}

/**
 * Remove os elementos da lista e apaga os elementos do LinkedList da memória, utilizando destrutor,
 * a partir de head. Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 * @param head elemento que aponta para o primeiro elemento do LinkedList a ser removido
 * @param destructor destrutora para cada elemento do LinkedList
 */
void linked_list_clear_eraser_destructor_by_head(LinkedList* linked_list, LinkedListElement* head, void (*destructor)(void*)) {
    if (head == NULL) return;
    if (head->next == NULL) return;
    linked_list_clear_eraser_destructor_by_head(linked_list, head->next, destructor);
    void* value = linked_list_remove_next(linked_list, head);
    destructor(value);
}

/**
 * Busca um LinkedListElement di LinkedList que possui a posição fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição do elemento a ser buscado
 * @return LinkedListElement* que possui a posição fornecida
 */
LinkedListElement* linked_list_find_element_by_index(LinkedList* linked_list, int index) {
    int id = -1;
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (id++ == index)
            return it;
    return NULL;
}

/**
 * Busca um LinkedListElement* da lista que possui um valor com a mesma referencia fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value referência que aponta para o valor do LinkedListElement a ser buscado
 */
LinkedListElement* linked_list_find_element_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (it->value == value)
            return it;
    return NULL;
}

// ### implements interface_list.h ###

/**
 * Busca a referência do elemento do LinkedList que possui a posição fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição do alemento a ser buscado
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* linked_list_find_by_index(LinkedList* linked_list, int index) {
    int id = -1;
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (id++ == index)
            return it->value;
    return NULL;
}

/**
 * Busca a referência do elemento do LinkedList que possui a referência fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value referência do valor a ser buscado
 * @return a referência do valor buscado. NULL caso não seja encontrado
 */
void* linked_list_find_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it != NULL; it = it->next)
        if (it->value == value)
            return it->value;
    return NULL;
}

/**
 * Adiciona no final do LinkedList um valor
 *
 * @param linked_list instância do LinkedList que receberá o valor
 * @param value valor a ser adicionado no final do LinkedList
 */
void linked_list_add(LinkedList* linked_list, void* value) {
    linked_list->last->next = new_element();
    linked_list->last->next->value = value;
    linked_list->last = linked_list->last->next;
    linked_list->size++;
}

/**
 * Adiciona um elemento no LinkedList na posicao informada
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser adicionado
 * @param index posição a ser adicionada o valor
 */
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

/**
 * Remove do LinkedList e apaga da memoria a refêrencia fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser removido do LinkedList e apagado da memória
 */
void linked_list_eraser_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it->next != NULL; it = it->next) {
        if (it->next->value == value) {
            linked_list_eraser_next(linked_list, it);
            break;
        }
    }
}

/**
 * Remove do LinkedList e apaga elemento da memoria que possui a posição
 * fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição a ter o elemento removido do LinkedList e apagado
 *        da memória
 */
void linked_list_eraser_at(LinkedList* linked_list, int index) {
    LinkedListElement* c = linked_list_find_by_index(linked_list, index-1);
    linked_list_eraser_next(linked_list, c);
}

/**
 * Remove do LinkedList sem apagar da memoria a refêrencia fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser removido do LinkedList sem ser apagado da
 *        memória
 */
void linked_list_remove_by_reference(LinkedList* linked_list, void* value) {
    for (LinkedListElement* it = linked_list->head; it->next != NULL; it = it->next) {
        if (it->next->value == value) {
            linked_list_remove_next(linked_list, it);
        }
    }
}

/**
 * Remove do LinkedList sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição a ter o elemento removido do LinkedList sem ser
 *        apagado da memória
 */
void* linked_list_remove_at(LinkedList* linked_list, int index) {
    LinkedListElement* c = linked_list_find_by_index(linked_list, index-1);
    return linked_list_remove_next(linked_list, c);
}

/**
 * Remove os elementos do LinkedList sem apagar os elementos da memoria.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_clear(LinkedList* linked_list) {
    linked_list_clear_by_head(linked_list, linked_list->head);
}

/**
 * Remove os elementos do LinkedList e apaga os elementos da memoria.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_clear_eraser(LinkedList* linked_list) {
    linked_list_clear_eraser_by_head(linked_list, linked_list->head);
}

/**
 * Remove os elementos do LinkedList e apaga os elementos da memoria, usando destrutor.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_clear_eraser_destructor(LinkedList* linked_list, void (*destructor)(void*)) {
    linked_list_clear_eraser_destructor_by_head(linked_list, linked_list->head, destructor);
}

/**
 * Percorre cada elemento do LinkedList e passa o valor e
 * posição para "callback"

 * @param linked_list instância do LinkedList
 * @param callback função que receberá cada valor e posição
 *        presente no LinkedList
 */
void linked_list_for_each(LinkedList* linked_list, void (*callback)(void*, int)) {
    if (linked_list == NULL || linked_list->head == NULL || linked_list->head->next == NULL)
        return;

    int index = 0;

    for (LinkedListElement* it = linked_list->head->next; it != NULL; it = it->next)
        callback(it->value, index++);
}