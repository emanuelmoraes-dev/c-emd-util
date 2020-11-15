#include "cemdutil/linked_list.h"

/**
 * Obtém o head do LinkedList que aponta para o primeiro elemento da lista
 *
 * @param linked_list instância do LinkedList
 * @return o head do LinkedList que aponta para o primeiro elemento da lista
 */
LinkedListElement* linked_list_head(LinkedList* linked_list) {
    if (linked_list->__head == NULL) {
        linked_list->__head = new_element();
        linked_list->size = 0;
    }
    return linked_list->__head;
}

void __linked_list_set_head(LinkedList* linked_list, LinkedListElement* head) {
    linked_list->__head = head;
}

/**
 * Obtém o último elemento do LinkedList. Se a lista estiver vazia, retorna-se
 * o head
 *
 * @param linked_list instância do LinkedList
 * @return o último elemento do LinkedList. Se a lista estiver vazia, retorna-se
 *  o head
 */
LinkedListElement* linked_list_last(LinkedList* linked_list) {
    LinkedListElement* head = linked_list_head(linked_list);

    if (linked_list->__last == NULL)
        linked_list->__last = head;

    return linked_list->__last;
}

void __linked_list_set_last(LinkedList* linked_list, LinkedListElement* last) {
    linked_list->__last = last;
}

/**
 * Inicializa uma LinkedList vazia
 *
 * @param linked_list instância do LinkedList a ser inicializada
 */
void linked_list_init(LinkedList* linked_list) {
    __linked_list_set_head(linked_list, new_element());
    __linked_list_set_last(linked_list, linked_list_head(linked_list));
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
    return linked_list_head(linked_list)->next->value;
}

/**
 * Remove o elemento do início do LinkedList
 *
 * @param linked_list instância do LinkedList
 * @return valor removido do início do LinkedList
 */
void* linked_list_remove_top(LinkedList* linked_list) {
    return linked_list_remove_next(linked_list, linked_list_head(linked_list));
}

/**
 * Remove da lista e apaga da memória o elemento do início do LinkedList
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_eraser_top(LinkedList* linked_list) {
    linked_list_eraser_next(linked_list, linked_list_head(linked_list));
}

/**
 * Adiciona um valor no LinkedList após o elemento informado
 *
 * @param linked_list instância do LinkedList
 * @param before elemento anterior ao elemento a ser adicionado
 * @param value valor a ser adicionado
 */
void linked_list_add_next(LinkedList* linked_list, LinkedListElement* before, void* value) {
    LinkedListElement* const ant = before;
    LinkedListElement* const prx = ant->next;
    ant->next = new_element();
    ant->next->value = value;
    ant->next->next = prx;
    if (prx == NULL)
        __linked_list_set_last(linked_list, ant->next);
    linked_list->size++;
}

/**
 * Busca e retorna o elemento anterior ao elemento da lista que possui a mesma referência de "value"
 *
 * @param linked_list instância do LinkedList
 * @param value referência do valor posterior ao valor que será retornado
 * @return elemento anterior ao elemento que possui a referência recebida
 */
LinkedListElement* linked_list_find_previous_by_reference(LinkedList* linked_list, void* value) {
    LinkedListElement* it;
    LINKED_LIST_FOR_EACH_PREVIOUS(it, linked_list)
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
    LinkedListElement* const alvo = element->next; // LinkedListElement que eu quero remover
    void* const value = alvo->value;
    alvo->value = NULL;
    if (alvo != NULL) {
        element->next = alvo->next; // Alvo é excluido da lista
        if (value != NULL)
            free(value); // Valor do alvo é excluido da memória
        free(alvo); // Alvo é excluido da memária RAM
        linked_list->size--;
    }
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
    if (alvo != NULL) {
        element->next = alvo->next; // Alvo é excluido da lista
        void* value = alvo->value;
        free(alvo); // Alvo é excluido da memária RAM
        linked_list->size--;
        return value;
    }
    return NULL;
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
    if (head == linked_list_head(linked_list)) {
        free(head);
        __linked_list_set_head(linked_list, NULL);
        __linked_list_set_last(linked_list, NULL);
    }
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
    if (head == linked_list_head(linked_list)) {
        free(head);
        __linked_list_set_head(linked_list, NULL);
        __linked_list_set_last(linked_list, NULL);
    }
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
    if (head == linked_list_head(linked_list)) {
        free(head);
        __linked_list_set_head(linked_list, NULL);
        __linked_list_set_last(linked_list, NULL);
    }
}

/**
 * Busca um LinkedListElement di LinkedList que possui a posição fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição do elemento a ser buscado
 * @return LinkedListElement* que possui a posição fornecida
 */
LinkedListElement* linked_list_find_element_by_index(LinkedList* linked_list, int index) {
    int i = 0;
    LinkedListElement* it;
    LINKED_LIST_FOR_EACH(it, linked_list)
        if (i++ == index)
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
    LinkedListElement* it;
    LINKED_LIST_FOR_EACH(it, linked_list)
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
void* linked_list_get_by_index(LinkedList* linked_list, int index) {
    int i = 0;
    LinkedListElement* it;
    LINKED_LIST_FOR_EACH(it, linked_list)
        if (i++ == index)
            return it->value;
    return NULL;
}

/**
 * Atualiza o valor do elemento do LinkedList que possui a posição fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição do alemento a ser atualizado
 * @param value valor a ser atribuído
 */
void linked_list_set_by_index(LinkedList* linked_list, int index, void* value) {
    LinkedListElement* element = linked_list_find_element_by_index(linked_list, index);
    element->value = value;
}

/**
 * Busca a posição no LinkedList da referência fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value referência a ser buscada
 * @return posição na lista da referência. -1 se não for encontrada
 */
int linked_list_find_index_by_reference(LinkedList* linked_list, void* value) {
    int i = 0;
    LinkedListElement* it;
    LINKED_LIST_FOR_EACH(it, linked_list)
        if (it->value == value)
            return i;
        else
            i++;
    return -1;
}

/**
 * Adiciona no final do LinkedList um valor
 *
 * @param linked_list instância do LinkedList que receberá o valor
 * @param value valor a ser adicionado no final do LinkedList
 */
void linked_list_add(LinkedList* linked_list, void* value) {
    linked_list_last(linked_list)->next = new_element();
    linked_list_last(linked_list)->next->value = value;
    __linked_list_set_last(linked_list, linked_list_last(linked_list)->next);
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
    LinkedListElement* const ant = linked_list_find_element_by_index(linked_list, index-1);
    LinkedListElement* const prx = ant->next;
    ant->next = new_element();
    ant->next->value = value;
    ant->next->next = prx;
    if (prx == NULL)
        __linked_list_set_last(linked_list, ant->next);
    linked_list->size++;
}

/**
 * Remove do LinkedList e apaga da memoria a refêrencia fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser removido do LinkedList e apagado da memória
 * @return 0 se a referência foi encontrada, removida do ArayList e apagada da memória
 */
short linked_list_eraser_by_reference(LinkedList* linked_list, void* value) {
    LinkedListElement* it;
    LINKED_LIST_FOR_EACH(it, linked_list) {
        if (it->next->value == value) {
            linked_list_eraser_next(linked_list, it);
            return 0;
        }
    }
    return 1;
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
    LinkedListElement* c = linked_list_find_element_by_index(linked_list, index-1);
    linked_list_eraser_next(linked_list, c);
}

/**
 * Remove do LinkedList sem apagar da memoria a refêrencia fornecida
 *
 * @param linked_list instância do LinkedList
 * @param value valor a ser removido do LinkedList sem ser apagado da
 *        memória
 * @return 0 se a referência foi encontrada e removida do LinkedList
 */
short linked_list_remove_by_reference(LinkedList* linked_list, void* value) {
    LinkedListElement* it;
    LINKED_LIST_FOR_EACH(it, linked_list) {
        if (it->next->value == value) {
            linked_list_remove_next(linked_list, it);
            return 0;
        }
    }
    return 1;
}

/**
 * Remove do LinkedList sem apagar elemento da memoria que possui a posição
 * fornecida
 *
 * @param linked_list instância do LinkedList
 * @param index posição a ter o elemento removido do LinkedList sem ser
 *        apagado da memória
 * @return referência removida do LinkedList
 */
void* linked_list_remove_at(LinkedList* linked_list, int index) {
    LinkedListElement* c = linked_list_find_element_by_index(linked_list, index-1);
    return linked_list_remove_next(linked_list, c);
}

/**
 * Remove os elementos do LinkedList sem apagar os elementos da memoria.
 * Não apaga LinkedList da memória
 *
 * @param _linked_list instância do LinkedList
 */
void linked_list_clear(void* _linked_list) {
    LinkedList* linked_list = (LinkedList*) _linked_list;
    linked_list_clear_by_head(linked_list, linked_list_head(linked_list));
}

/**
 * Remove os elementos do LinkedList e apaga os elementos da memoria.
 * Não apaga LinkedList da memória
 *
 * @param _linked_list instância do LinkedList
 */
void linked_list_clear_eraser(void* _linked_list) {
    LinkedList* linked_list = (LinkedList*) _linked_list;
    linked_list_clear_eraser_by_head(linked_list, linked_list_head(linked_list));
}

/**
 * Remove os elementos do LinkedList e apaga os elementos da memoria, usando destrutor.
 * Não apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_clear_eraser_destructor(LinkedList* linked_list, void (*destructor)(void*)) {
    linked_list_clear_eraser_destructor_by_head(linked_list, linked_list_head(linked_list), destructor);
}

/**
 * Remove os elementos do LinkedList sem apagar os elementos da memoria.
 * Apaga LinkedList da memória
 *
 * @param _linked_list instância do LinkedList
 */
void linked_list_free(void* _linked_list) {
    linked_list_clear(_linked_list);
    free(_linked_list);
}

/**
 * Remove os elementos do LinkedList e apaga os elementos da memoria.
 * Apaga LinkedList da memória
 *
 * @param _linked_list instância do LinkedList
 */
void linked_list_free_eraser(void* _linked_list) {
    linked_list_clear_eraser(_linked_list);
    free(_linked_list);
}

/**
 * Remove os elementos do LinkedList e apaga os elementos da memoria, usando destrutor.
 * Apaga LinkedList da memória
 *
 * @param linked_list instância do LinkedList
 */
void linked_list_free_eraser_destructor(LinkedList* linked_list, void (*destructor)(void*)) {
    linked_list_clear_eraser_destructor(linked_list, destructor);
    free(linked_list);
}

/**
 * Percorre cada elemento do LinkedList e passa o valor e
 * posição para "callback"

 * @param linked_list instância do LinkedList
 * @param callback função que receberá cada valor e posição
 *        presente no LinkedList. "callback" deve retornar
 *        1 para continuar a iteração. 0 para que o comando
 *        break seja executado
 */
void linked_list_for_each(LinkedList* linked_list, short (*callback)(void*, int)) {
    if (linked_list == NULL || linked_list_head(linked_list) == NULL || linked_list_head(linked_list)->next == NULL)
        return;

    int index = 0;
    LinkedListElement* it;
    LINKED_LIST_FOR_EACH(it, linked_list)
        if (callback(it->value, index++) != 0)
            break;
}
