#ifndef DYNAMIC_STRING_H_INCLUDED
#define DYNAMIC_STRING_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define DEFAULT_MIN_EXTRA_STRING 20 // Quantidade mínima de espaço extra em realocações de memória
#define DEFAULT_STRATEGY_REALLOCATED_STRING HALF_STRATEGY_REALLOCATED_STRING // Estratégia padrão de realocação de memória

/* Define o tipo de realocação que a String terá */
typedef int ReallocateStrategyString(int length_allocated, int lenght);

/*
Cria uma estratégia de realocar apenas o espaço necessário pelo
tamanho da string

@param length_allocated - expaço atualmente definido para realocação
@param lenght - quantidade de caracteres atualmente armazenados na String,
    desconsiderando o \0
@return - Novo espaço a ser realocado (se não for o suficiente, a função será
    chamada novamente)
*/
int STRICT_STRATEGY_REALLOCATED_STRING(int length_allocated, int lenght);

/*
É a estratégia de realocar adicionando a metade do tamanho da string

@param length_allocated - expaço atualmente definido para realocação
@param lenght - quantidade de caracteres atualmente armazenados na String,
    desconsiderando o \0
@return - Novo espaço a ser realocado (se não for o suficiente, a função será
    chamada novamente)
*/
int HALF_STRATEGY_REALLOCATED_STRING(int length_allocated, int lenght);

/*
É a estratégia de realocar o dobro do que foi alocado anteriormente

@param length_allocated - expaço atualmente definido para realocação
@param lenght - quantidade de caracteres atualmente armazenados na String,
    desconsiderando o \0
@return - Novo espaço a ser realocado (se não for o suficiente, a função será
    chamada novamente)
*/
int DOUBLE_STRATEGY_REALLOCATED_STRING(int length_allocated, int lenght);

/*
Struct que representa uma instância de uma String dinâmica
*/
typedef struct st_string {
    // public
    char* c_str; // String e formato C
    size_t lenght; // Quantidade de caracteres da string
    size_t min_extra; // Quantidade mínima de espaço extra na realocação da String
    ReallocateStrategyString* reallocate_strategy; // Estratégia de realocação de espaço

    // private
    size_t __length_allocated; // Espaço alocado na memória
} String;

/*
Construtor da string dinâmica

@param s - Valor a ser copiado para String dinâmica
@param min_extra - Valor extra mínimo na realocação da String
@param reallocate_strategy - Estratégia para realocação
@return - Nova instância de String dinâmica
*/
String* new_string_reallocate_strategy(const char* s, int min_extra, ReallocateStrategyString* reallocate_strategy);

/*
Construtor da string dinâmica

@param s - Valor a ser copiado para String dinâmica
@param min_length_allocated - Quantidade mínima que estar alocado
@return Nova instância de String dinâmica
*/
String* new_string_allocated(const char* s, int min_length_allocated);

/*
Construtor da string dinâmica

@param s - Valor a ser copiado para String dinâmica
@return - Nova instância de String dinâmica
*/
String* new_string(const char* s);

/*
@param str - Instância da String dinâmicas
@return - quantidade de espaço alocado para a String dinâmica
*/
int get_length_allocated_string(String* str);

/*
Informa a quantidade mínima de espaço que deve estar alocado
para uma determinada String dinâmica (esse método não irá
interferir em uma realocações futuras)

@param str - String dinâmica
@param length_allocated - quantidade mínima que deve estar alocada
@return - 1 se uma realocação foi necessária, 0 caso contrário
*/
short set_min__length_allocated(String* str, int length_allocated);

/*
Informa a quantidade máxima de espaço que deve estar alocado
para uma determinada String dinâmica (esse método não irá
interferir em uma realocações futuras)

@param str - String dinâmica
@param length_allocated - quantidade máxima que deve estar alocada
@return - 1 se uma realocação foi necessária, 0 caso contrário
*/
short set_max__length_allocated(String* str, int length_allocated);

/*
Informa a quantidade exata que deve estar alocado para uma determinada
String dinâmica. Se o tamanho da String for maior que o tamanho da
alocação, a realocação não ocorrerá (esse método não irá
interferir em uma realocações futuras)

@param str - String dinâmica
@param length_allocated - quantidade exata que deve estar alocada
@return - 1 se uma realocação ocorreu, 0 caso contrário
*/
short set__length_allocated(String* str, int length_allocated);

/*
Atribui novo valor para a String dinâmica

@param str - Instância da String dinâmica
@param s - Valor a ser atribuído a 'str'
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short set_string(String* str, const char* s);

/*
Concatena a String dinâmica com um valor

@param str - Instância da String dinâmica
@param s - Valor a ser concatenado
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short cat_string(String* str, const char* s);

/*
Remove a String dinâmica da memória

@param str - Instância da String dinâmica a ser removida
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short free_string(String* str);

/*
Altera uma String dinâmica para receber uma substring de outra
String dinâmica

@param str - Instânciada String dinâmica
@param target - Instância que irá receber a substring. Precisa
    já estar alocada. Não pode ser a mesma instância de str
@param start - Posição inicial da substring
@param end - Posição final da substring (não incluso)
@return - 1 se executado com sucesso, 0 caso contrário
*/
short sub_string(String* str, String* target, int start, int end);

/*
Retorna o tamanho do array necessário para armazenar
o resultado do método "split_string"

@param str - Instância da String dinâmica que será separada
@param sep - Separador que divide a String em várias partes
@return - Tamanho do array que armazenará o resultado
do split
*/
int size_split_string(String* str, const char* sep);

/*
Modifica o array dos elementos separados da String
dinâmica, tendo como delimitador um separador. As Strings do
array devem estar desalocadas da memória

@param str - Instância da String dinâmica que será separada
@param target - Array que armazenará o resultado do split. O
    array deve estar completamente desalocado da
    memória
@param sep - Separador que divide a String em várias partes
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short split_string(String* str, String* target[], const char* sep);

/*
Retorna 1 se existir uma substring igual a "target". 0 caso
contrário

@param target - substring que será buscada
*/
short find_substring(String* src, String* target);

/*
Atribui em "target" uma string dinâmica na qual a primeira substring
de "src" igual a "replace" foi substituída pelo conteúdo
por "value". "target" precisa já estar alocada

@param src - string dinâmica na qual terá a primeira substring
    substituída
@param target - string que irá receber a nova string dinâmica. Precisa
    já estar alocada
@param replace - substring que será buscada
@param value - valor que irá substituir "replace"
*/
void replace_string(String* src, String* target, String* replace, String* value);

/*
Atribui em "target" uma string dinâmica na qual TODAS as substrings
de "src" iguais a "replace" foram substituídas pelo conteúdo
por "value". "target" precisa já estar alocada

@param src - string dinâmica na qual terá TODAS as substrings
    substituídas
@param target - string que irá receber nova string dinâmica. Precisa
    já estar alocada
@param replace - substring que será buscada
@param value - valor que irá substituir "replace"
*/
void replace_all_string(String* src, String* target, String* replace, String* value);

/*
Atribui em "target" o conteúdo de uma linha inteira de um arquivo,
independente da quantidade de caracteres. "target" precisa já estar
alocada

@param file - arquivo na qual a linha será lida
@param target - string dinâmica que irá receber o conteúdo da linha.
    Precisa já estar alocada
@param ignore_endl - Se 1, ignora quebras de linha
@return 1 se a operação for executada com sucesso. 0 caso contrário
*/
short read_full_line_string(FILE* file, String* target, short ignore_endl);

#endif // DYNAMIC_STRING_H_INCLUDED