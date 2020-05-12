#include "dynamic_string.h"

/*
Construtor da string dinâmica

@param s - Valor a ser copiado para String dinâmica
@return Nova instância de String dinâmica
*/
String* new_string(const char* s) {
    String* str = (String*) malloc(sizeof(String));
    str->lenght = strlen(s);
    str->__length_allocated = MAX(str->lenght * 2, 10);
    str->c_str = (char*) malloc(sizeof(char) * str->__length_allocated);
    strcpy(str->c_str, s);
    return str;
}

/*
Atribui novo valor para a String dinâmica

@param str - Instância da String dinâmica
@param s - Valor a ser atribuído a 'str'
*/
void set_string(String* str, const char* s) {
    int len_s = strlen(s);
    int flag = 0;

    while (str->__length_allocated <= len_s) {
        str->__length_allocated *= 2;
        flag = 1;
    }

    if (flag)
        str->c_str = (char*) realloc(str->c_str, sizeof(char) * str->__length_allocated);

    strcpy(str->c_str, s);
}

/*
Concatena a String dinâmica com um valor

@param str - Instância da String dinâmica
@param s - Valor a ser concatenado
*/
void cat_string(String* str, const char* s) {
    int len_s = strlen(s);
    char ns[len_s + str->lenght + 1];
    strcpy(ns, "");
    strcpy(ns, str->c_str);
    strcat(ns, s);
    set_string(str, ns);
}

/*
Remove a String dinâmica da memória

@param str - Instância da String dinâmica a ser removida
*/
void eraser_string(String* str) {
    str->__length_allocated = 0;
    str->lenght = 0;
    free(str->c_str);
    free(str);
}
