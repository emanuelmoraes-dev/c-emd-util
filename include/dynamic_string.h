#ifndef DYNAMIC_STRING_H_INCLUDED
#define DYNAMIC_STRING_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define STRING_DEFAULT_MIN_EXTRA 20 // Quantidade mínima de espaço extra em realocações de memória
#define STRING_DEFAULT_STRATEGY_REALLOCATED STRING_HALF_STRATEGY_REALLOCATED // Estratégia padrão de realocação de memória

/**
 * Define o tipo de realocação que a String terá
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param size tamanho atual do ArrayList
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
typedef int StringReallocateStrategy(int length_allocated, int lenght);

/**
 * Cria uma estratégia de realocar apenas o espaço necessário pelo
 * tamanho da string
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param lenght quantidade de caracteres atualmente armazenados na String,
 *        desconsiderando o \0
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
int STRING_STRICT_STRATEGY_REALLOCATED(int length_allocated, int lenght);

/**
 * É a estratégia de realocar adicionando a metade do tamanho da string
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param lenght quantidade de caracteres atualmente armazenados na String,
 *        desconsiderando o \0
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
int STRING_HALF_STRATEGY_REALLOCATED(int length_allocated, int lenght);

/**
 * É a estratégia de realocar o dobro do que foi alocado anteriormente
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param lenght quantidade de caracteres atualmente armazenados na String,
 *        desconsiderando o \0
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
int STRING_DOUBLE_STRATEGY_REALLOCATED(int length_allocated, int lenght);

/**
 * Struct que representa uma instância de uma String dinâmica
 */
typedef struct __st_string {
    // public
    int lenght; // Quantidade de caracteres da string
    int min_extra; // Quantidade mínima de espaço extra na realocação da String
    StringReallocateStrategy* reallocate_strategy; // Estratégia de realocação de espaço

    // private
    char* __c_str; // String e formato C
    int __length_allocated; // Espaço alocado na memória
} String;

/**
 * Obtém a String dinâmica no formato C
 *
 * @param str instância da string dinâmica
 * @return string no formato c
 */
char* string_c(String* str);

/**
 * Inicializador de string dinâmica
 *
 * String->min_extra = min_extra
 * String->reallocate_strategy = reallocate_strategy
 *
 * @param str instância de String dinâmica
 * @param s valor a ser copiado para String dinâmica
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @param min_extra valor extra mínimo na realocação da String
 * @param reallocate_strategy estratégia para realocação
 */
void string_init_reallocate_strategy(String* str, const char* s, int min_length_allocated, int min_extra, StringReallocateStrategy* reallocate_strategy);

/**
 * Inicializador de string dinâmica
 *
 * String->min_extra = STRING_DEFAULT_MIN_EXTRA # 20
 * String->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED # STRING_HALF_STRATEGY_REALLOCATED
 *
 * @param str instância de String dinâmica
 * @param s valor a ser copiado para String dinâmica
 * @param min_length_allocated quantidade mínima que deve estar alocado
 */
void string_init_allocated(String* str, const char* s, int min_length_allocated);

/**
 * Inicializador de string dinâmica
 *
 * String->min_extra = STRING_DEFAULT_MIN_EXTRA # 20
 * String->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED # STRING_HALF_STRATEGY_REALLOCATED
 *
 * @param str instância de String dinâmica
 * @param s valor a ser copiado para String dinâmica
 */
void string_init(String* str, const char* s);

/**
 * Cria uma string dinâmica
 *
 * String->min_extra = min_extra
 * String->reallocate_strategy = reallocate_strategy
 *
 * @param s valor a ser copiado para String dinâmica
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @param min_extra valor extra mínimo na realocação da String
 * @param reallocate_strategy estratégia para realocação
 * @return nova instância de String dinâmica
 */
String* new_string_reallocate_strategy(const char* s, int min_length_allocated, int min_extra, StringReallocateStrategy* reallocate_strategy);

/**
 * Cria uma string dinâmica
 *
 * String->min_extra = STRING_DEFAULT_MIN_EXTRA # 20
 * String->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED # STRING_HALF_STRATEGY_REALLOCATED
 *
 * @param s valor a ser copiado para String dinâmica
 * @param min_length_allocated quantidade mínima que deve estar alocado
 * @return nova instância de String dinâmica
 */
String* new_string_allocated(const char* s, int min_length_allocated);

/**
 * Cria uma string dinâmica
 *
 * String->min_extra = STRING_DEFAULT_MIN_EXTRA # 20
 * String->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED # STRING_HALF_STRATEGY_REALLOCATED
 *
 * @param s valor a ser copiado para String dinâmica
 * @return nova instância de String dinâmica
 */
String* new_string(const char* s);

/**
 * @param str instância da String dinâmicas
 * @return quantidade de espaço alocado para a String dinâmica
 */
int string_get_length_allocated(String* str);

/**
 * Informa a quantidade mínima de espaço que deve estar alocado
 * para uma determinada String dinâmica (esse método não irá
 * interferir em realocações futuras)
 *
 * @param str String dinâmica
 * @param length_allocated quantidade mínima que deve estar alocada
 * @return 0 se uma realocação foi necessária
 */
short string_set_min_length_allocated(String* str, int length_allocated);

/**
 * Informa a quantidade máxima de espaço que deve estar alocado
 * para uma determinada String dinâmica (esse método não irá
 * interferir em uma realocações futuras)
 *
 * @param str String dinâmica
 * @param length_allocated quantidade máxima que deve estar alocada
 * @return 0 se uma realocação foi necessária
 */
short string_set_max_length_allocated(String* str, int length_allocated);

/**
 * Informa a quantidade exata que deve estar alocado para uma determinada
 * String dinâmica. Se o tamanho da String for maior que o tamanho da
 * alocação, a realocação não ocorrerá (esse método não irá
 * interferir em uma realocações futuras)
 *
 * @param str String dinâmica
 * @param length_allocated quantidade exata que deve estar alocada
 * @return 0 se uma realocação ocorreu
 */
short string_set_length_allocated(String* str, int length_allocated);

/**
 * Atribui novo valor para a String dinâmica
 *
 * @param str instância da String dinâmica
 * @param s valor a ser atribuído a 'str'
 */
void string_set(String* str, const char* s);

/**
 * Concatena a String dinâmica com um valor
 *
 * @param str instância da String dinâmica
 * @param s valor a ser concatenado
 */
void string_cat(String* str, const char* s);

/**
 * Apaga da memória os caracteres da String dinâmica.
 * Não apaga String dinâmica da memória
 *
 * @param _str instância da String dinâmica a ser removida
 */
void string_clear(void* _str);

/**
 * Apaga da memória os caracteres da String dinâmica.
 * Apaga String dinâmica da memória
 *
 * @param _str instância da String dinâmica a ser removida
 */
void string_free(void* _str);

/**
 * Altera uma String dinâmica para receber uma substring de outra
 * String dinâmica
 *
 * @param str instânciada String dinâmica
 * @param target instância que irá receber a substring. Precisa
 *        já estar alocada. Não pode ser a mesma instância de str
 * @param start posição inicial da substring
 * @param end posição final da substring (não incluso)
 */
void string_sub(String* str, String* target, int start, int end);

/**
 * Retorna o tamanho do array necessário para armazenar
 * o resultado do método "string_split"
 *
 * @param str instância da String dinâmica que será separada
 * @param sep separador que divide a String em várias partes
 * @return tamanho do array que armazenará o resultado
 *         do split
 */
int string_size_split(String* str, const char* sep);

/**
 * Modifica o array dos elementos separados da String
 * dinâmica, tendo como delimitador um separador. As Strings do
 * array devem estar desalocadas da memória
 *
 * @param str instância da String dinâmica que será separada
 * @param target array que armazenará o resultado do split. O
 *        array deve estar completamente desalocado da
 *        memória
 * @param sep separador que divide a String em várias partes
 */
void string_split(String* str, String* target[], const char* sep);

/**
 * Busca a primeira posição da substring na String dinâmica
 *
 * @param target substring que será buscada
 * @return primeira posição da substring na String dinâmica. -1 se não for encontrado
 */
int string_find_sub(String* src, String* target);

/**
 * Atribui em "target" uma string dinâmica na qual a primeira substring
 * de "src" igual a "replace" foi substituída pelo conteúdo
 * por "value". "target" precisa já estar alocada
 *
 * @param src string dinâmica na qual terá a primeira substring
 *        substituída
 * @param target string que irá receber a nova string dinâmica. Precisa
 *        já estar alocada
 * @param replace substring que será buscada
 * @param value valor que irá substituir "replace"
 */
void string_replace(String* src, String* target, String* replace, String* value);

/**
 * Atribui em "target" uma string dinâmica na qual TODAS as substrings
 * de "src" iguais a "replace" foram substituídas pelo conteúdo
 * por "value". "target" precisa já estar alocada
 *
 * @param src string dinâmica na qual terá TODAS as substrings
 *        substituídas
 * @param target string que irá receber nova string dinâmica. Precisa
 *        já estar alocada
 * @param replace substring que será buscada
 * @param value valor que irá substituir "replace"
 */
void string_replace_all(String* src, String* target, String* replace, String* value);

/**
 * Atribui em "target" o conteúdo de uma linha inteira de um arquivo,
 * independente da quantidade de caracteres. "target" precisa já estar
 * alocada
 *
 * @param file arquivo na qual a linha será lida
 * @param target string dinâmica que irá receber o conteúdo da linha.
 *        Precisa já estar alocada
 * @param ignore_endl se 1, ignora quebras de linha
 * @return 0 se a operação for executada com sucesso
 */
short string_read_full_line(FILE* file, String* target, short ignore_endl);

#endif // DYNAMIC_STRING_H_INCLUDED