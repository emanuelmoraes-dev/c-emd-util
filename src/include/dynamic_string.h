#ifndef DYNAMIC_STRING_H_INCLUDED
#define DYNAMIC_STRING_H_INCLUDED

#include <string.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define INIT_LENGTH_ALLOCATED 10 // Espaço alocado na memória pelo construtor

/*
Struct que representa uma instância de uma String dinâmica
*/
typedef struct st_string {
    char* c_str; // String e formato C
    int lenght; // Quantidade de caracteres da string
    int __length_allocated; // Espaço alocado na memória
} String;

/*
Construtor da string dinâmica

@param s - Valor a ser copiado para String dinâmica
@return Nova instância de String dinâmica
*/
String* new_string(const char* s);

/*
Atribui novo valor para a String dinâmica

@param str - Instância da String dinâmica
@param s - Valor a ser atribuído a 'str'
*/
void set_string(String* str, const char* s);

/*
Concatena a String dinâmica com um valor

@param str - Instância da String dinâmica
@param s - Valor a ser concatenado
*/
void cat_string(String* str, const char* s);

/*
Remove a String dinâmica da memória

@param str - Instância da String dinâmica a ser removida
*/
void eraser_string(String* str);

#endif // DYNAMIC_STRING_H_INCLUDED