#include <math.h>
#include "dynamic_string.h"

/*
Cria uma estratégia de realocar apenas o espaço necessário pelo
tamanho da string

@param length_allocated - expaço atualmente definido para realocação
@param lenght - quantidade de caracteres atualmente armazenados na String,
    desconsiderando o \0
@return - Novo espaço a ser realocado (se não for o suficiente, a função será
    chamada novamente)
*/
int STRICT_STRATEGY_REALLOCATED(int length_allocated, int lenght) {
    return lenght+1;
}

/*
É a estratégia de realocar adicionando a metade do tamanho da string

@param length_allocated - expaço atualmente definido para realocação
@param lenght - quantidade de caracteres atualmente armazenados na String,
    desconsiderando o \0
@return - Novo espaço a ser realocado (se não for o suficiente, a função será
    chamada novamente)
*/
int HALF_STRATEGY_REALLOCATED(int length_allocated, int lenght) {
    lenght++;
    int half = ceil(lenght / 2.0);
    return lenght + half;
}

/*
É a estratégia de realocar o dobro do que foi alocado anteriormente

@param length_allocated - expaço atualmente definido para realocação
@param lenght - quantidade de caracteres atualmente armazenados na String,
    desconsiderando o \0
@return - Novo espaço a ser realocado (se não for o suficiente, a função será
    chamada novamente)
*/
int DOUBLE_STRATEGY_REALLOCATED(int length_allocated, int lenght) {
    length_allocated = MAX(1, length_allocated);
    return length_allocated*2;
}

/*
Construtor da string dinâmica

String->min_extra = min_extra
String->reallocate_strategy = reallocate_strategy

@param s - Valor a ser copiado para String dinâmica
@param min_extra - Valor extra mínimo na realocação da String
@param reallocate_strategy - Estratégia para realocação
@return - Nova instância de String dinâmica
*/
String* new_string_reallocate_strategy(const char* s, int min_extra, ReallocateStrategy* reallocate_strategy) {
    String* str = (String*) malloc(sizeof(String));
    str->min_extra = min_extra;
    str->reallocate_strategy = reallocate_strategy;
    str->lenght = strlen(s);
    str->__length_allocated = 0;

    while (str->__length_allocated <= str->lenght) {
        str->__length_allocated = str->reallocate_strategy(str->__length_allocated, str->lenght);
    }

    str->__length_allocated = MAX(str->__length_allocated, (str->lenght+1) + (str->min_extra));
    str->c_str = (char*) malloc(sizeof(char) * str->__length_allocated);
    strcpy(str->c_str, s);
    return str;
}

/*
Construtor da string dinâmica. O min_extra será atribuído, mas será ignorado
para a alocação neste construtor

String->min_extra = DEFAULT_MIN_EXTRA # 20
String->reallocate_strategy = DEFAULT_STRATEGY_REALLOCATED # HALF_STRATEGY_REALLOCATED

@param s - Valor a ser copiado para String dinâmica
@param min_length_allocated - Quantidade mínima que estar alocado
@return Nova instância de String dinâmica
*/
String* new_string_allocated(const char* s, int min_length_allocated) {
    String* str = (String*) malloc(sizeof(String));
    str->min_extra = DEFAULT_MIN_EXTRA;
    str->reallocate_strategy = DEFAULT_STRATEGY_REALLOCATED;
    str->lenght = strlen(s);
    str->__length_allocated = 0;
    str->__length_allocated = STRICT_STRATEGY_REALLOCATED(str->__length_allocated, str->lenght);
    str->__length_allocated = MAX(str->__length_allocated, min_length_allocated);
    str->c_str = (char*) malloc(sizeof(char) * str->__length_allocated);
    strcpy(str->c_str, s);
    return str;
}

/*
Construtor da string dinâmica

String->min_extra = DEFAULT_MIN_EXTRA # 20
String->reallocate_strategy = DEFAULT_STRATEGY_REALLOCATED # HALF_STRATEGY_REALLOCATED

@param s - Valor a ser copiado para String dinâmica
@return Nova instância de String dinâmica
*/
String* new_string(const char* s) {
    return new_string_reallocate_strategy(s, DEFAULT_MIN_EXTRA, DEFAULT_STRATEGY_REALLOCATED);
}

/*
@param str - Instância da String dinâmicas
@return - quantidade de espaço alocado para a String dinâmica
*/
int get_length_allocated_string(String* str) {
    return str->__length_allocated;
}

/*
Informa a quantidade mínima de espaço que deve estar alocado
para uma determinada String dinâmica (esse método não irá
interferir em uma realocações futuras)

@param str - String dinâmica
@param length_allocated - quantidade mínima que deve estar alocada
@return - 1 se uma realocação foi necessária, 0 caso contrário
*/
short set_min__length_allocated(String* str, int length_allocated) {
    if (str->__length_allocated >= length_allocated)
        return 0;
    
    str->c_str = (char*) realloc(str->c_str, sizeof(char) * length_allocated);
    str->__length_allocated = length_allocated;
    return 1;
}

/*
Informa a quantidade máxima de espaço que deve estar alocado
para uma determinada String dinâmica (esse método não irá
interferir em uma realocações futuras)

@param str - String dinâmica
@param length_allocated - quantidade máxima que deve estar alocada
@return - 1 se uma realocação foi necessária, 0 caso contrário
*/
short set_max__length_allocated(String* str, int length_allocated) {
    if (str->__length_allocated <= length_allocated || str->lenght >= length_allocated)
        return 0;
    
    str->c_str = (char*) realloc(str->c_str, sizeof(char) * length_allocated);
    str->__length_allocated = length_allocated;
    return 1;
}

/*
Informa a quantidade exata que deve estar alocado para uma determinada
String dinâmica. Se o tamanho da String for maior que o tamanho da
alocação, a realocação não ocorrerá (esse método não irá
interferir em uma realocações futuras)

@param str - String dinâmica
@param length_allocated - quantidade exata que deve estar alocada
@return - 1 se uma realocação ocorreu, 0 caso contrário
*/
short set__length_allocated(String* str, int length_allocated) {
    if (str->lenght >= length_allocated)
        return 0;

    str->c_str = (char*) realloc(str->c_str, sizeof(char) * length_allocated);
    str->__length_allocated = length_allocated;
    return 1;
}

/*
Atribui novo valor para a String dinâmica

@param str - Instância da String dinâmica
@param s - Valor a ser atribuído a 'str'
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short set_string(String* str, const char* s) {
    str->lenght = strlen(s);
    int flag = 0;

    while (str->__length_allocated <= str->lenght) {
        str->__length_allocated = str->reallocate_strategy(str->__length_allocated, str->lenght);
        flag = 1;
    }

    if (flag) {
        str->__length_allocated = MAX(str->__length_allocated, (str->lenght+1) + (str->min_extra));
        str->c_str = (char*) realloc(str->c_str, sizeof(char) * str->__length_allocated);
    }

    strcpy(str->c_str, s);
    return 1;
}

/*
Concatena a String dinâmica com um valor

@param str - Instância da String dinâmica
@param s - Valor a ser concatenado
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short cat_string(String* str, const char* s) {
    int len_s = strlen(s);
    char ns[len_s + str->lenght + 2];
    strcpy(ns, "");
    strcpy(ns, str->c_str);
    strcat(ns, s);
    set_string(str, ns);
    return 1;
}

/*
Remove a String dinâmica da memória

@param str - Instância da String dinâmica a ser removida
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short free_string(String* str) {
    str->__length_allocated = 0;
    str->lenght = 0;
    free(str->c_str);
    free(str);
    return 1;
}

/*
Altera uma String dinâmica para receber uma substring de outra
String dinâmica

@param str - Instânciada String dinâmica
@param target - Instância que irá receber a substring. Precisa
    já estar alocada. Não pode ser a mesma instância de target
@param start - Posição inicial da substring
@param end - Posição final da substring (não incluso)
@return - 1 se executado com sucesso, 0 caso contrário
*/
short sub_string(String* str, String* target, int start, int end) {
    if (str == target)
        return 0;

    int len = strlen(str->c_str);

    if (len < end || start > end)
        return 0;

    int len_sub = end - start;

    set_string(target, "");
    set_min__length_allocated(target, len_sub + 1);

    int i;
    for (i = 0; i < len_sub; i++)
        target->c_str[i] = str->c_str[start++];

    target->c_str[len_sub] = '\0';
    target->lenght = len_sub;
    return 1;
}

/*
Retorna o tamanho do array necessário para armazenar
o resultado do método "split_string"

@param str - Instância da String dinâmica que será separada
@param sep - Separador que divide a String em várias partes
@return - Tamanho do array que armazenará o resultado
do split
*/
int size_split_string(String* str, const char* sep) {
    if (strcmp(sep, "") == 0)
        return str->lenght;

    if (str->lenght == 0)
        return 0;

    int size = 1;
    int len_sep = strlen(sep);

    int i;
    String* sub = new_string_allocated("", len_sep + 1);
    for (i = 0; i < str->lenght; i++) {
        sub_string(str, sub, i, i + len_sep);

        if (strcmp(sub->c_str, sep) == 0) {
            size++;
            i += len_sep - 1;
        }
    }

    free_string(sub);
    return size;
}

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
short split_string(String* str, String* target[], const char* sep) {
    int len_sep = strlen(sep);
    int i_target = 0;

    if (str->lenght > 0)
        target[0] = new_string("");

    int i;
    String* sub = new_string_allocated("", len_sep + 1);
    for (i = 0; i < str->lenght; i++) {
        char ch = str->c_str[i];
        sub_string(str, sub, i, i + len_sep);

        if (strcmp(sep, "") == 0) {
            char ch_str[] = { ch, '\0' };
            set_string(target[i_target], ch_str);
            i_target++;            

            if (i+1 < str->lenght)
                target[i_target] = new_string("");
        } else if (strcmp(sub->c_str, sep) == 0) {
            i_target++;
            target[i_target] = new_string("");
            i += len_sep-1;
        } else {
            char ch_str[] = { ch, '\0' };
            cat_string(target[i_target], ch_str);
        }
    }

    free_string(sub);
    return 1;
}
