#ifndef INTERFACE_LIST_H_INCLUDED
#define INTERFACE_LIST_H_INCLUDED

#define LIST_PARAM(varname) LinkedList* __##varname##_linked_list, ArrayList* __##varname##_array_list

#define LIST_ARG_LINKED_LIST(linked_list) linked_list, NULL
#define LIST_ARG_ARRAY_LIST(array_list) NULL, arrayList

#define LIST_LET_LINKED_LIST(varname, value) \
    LinkedList* __##varname##_linked_list = value;\
    ArrayList* __##varname##_array_list = NULL
#define LIST_LET_ARRAY_LIST(varname, value) \
    LinkedList* __##varname##_linked_list = NULL;\
    ArrayList* __##varname##_array_list = value

#define LIST_SET(varname, valuename) \
    __##varname##_linked_list = __##valuename##_linked_list;\
    __##varname##_array_list = __##valuename##_array_list

// ### MÉTODOS ###

#define LIST_FIND_BY_INDEX(varname, index) \
    __##varname##_linked_list != NULL ? linked_list_find_by_index(__##varname##_linked_list, index) : \
    array_list_find_by_index(__##varname##_array_list, index)

#define LIST_FIND_BY_REFERENCE(varname, value) \
    __##varname##_linked_list != NULL ? linked_list_find_by_reference(__##varname##_linked_list, value) : \
    array_list_find_by_reference(__##varname##_array_list, value)

#define LIST_ADD(varname, value) \
    __##varname##_linked_list != NULL ? linked_list_add(__##varname##_linked_list, value) : \
    array_list_add(__##varname##_array_list, value)

#define LIST_ADD_AT(varname, value, index) \
    __##varname##_linked_list != NULL ? linked_list_add_at(__##varname##_linked_list, value, index) : \
    array_list_add_at(__##varname##_array_list, value, index)

#define LIST_ERASER_BY_REFERENCE(varname, value) \
    __##varname##_linked_list != NULL ? linked_list_eraser_by_reference(__##varname##_linked_list, value) : \
    array_list_eraser_by_reference(__##varname##_array_list, value)

#define LIST_ERASER_AT(varname, index) \
    __##varname##_linked_list != NULL ? linked_list_eraser_at(__##varname##_linked_list, index) : \
    array_list_eraser_at(__##varname##_array_list, index)

#define LIST_REMOVE_BY_REFERENCE(varname, value) \
    __##varname##_linked_list != NULL ? linked_list_remove_by_reference(__##varname##_linked_list, value) : \
    array_list_remove_by_reference( __##varname##_array_list, value)

#define LIST_REMOVE_AT(varname, index) \
    __##varname##_linked_list != NULL ? linked_list_remove_at(__##varname##_linked_list, index) : \
    array_list_remove_at(__##varname##_array_list, index)

#define LIST_FREE(varname) \
    __##varname##_linked_list != NULL ? linked_list_free(__##varname##_linked_list) : \
    array_list_free(__##varname##_array_list)

#define LIST_FREE_ERASER(varname) \
    __##varname##_linked_list != NULL ? linked_list_free_eraser(__##varname##_linked_list) : \
    array_list_free_eraser(__##varname##_array_list)

#define LIST_FREE_ERASER_DESTRUCTOR(varname, destructor) \
    __##varname##_linked_list != NULL ? linked_list_free_eraser_destructor(__##varname##_linked_list, destructor) : \
    array_list_free_eraser_destructor(__##varname##_array_list, destructor)

#define LIST_FOR_EACH(varname, callback) \
    __##varname##_linked_list != NULL ? linked_list_for_each(__##varname##_linked_list, callback) : \
    array_list_for_each(__##varname##_array_list, callback)

#endif // INTERFACE_LIST_H_INCLUDED