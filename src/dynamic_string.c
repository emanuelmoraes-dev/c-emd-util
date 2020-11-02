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
int STRING_STRICT_STRATEGY_REALLOCATED(int length_allocated, int lenght) {
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
int STRING_HALF_STRATEGY_REALLOCATED(int length_allocated, int lenght) {
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
int STRING_DOUBLE_STRATEGY_REALLOCATED(int length_allocated, int lenght) {
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
String* new_string_reallocate_strategy(const char* s, int min_extra, StringReallocateStrategy* reallocate_strategy) {
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

String->min_extra = STRING_DEFAULT_MIN_EXTRA # 20
String->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED # STRING_HALF_STRATEGY_REALLOCATED

@param s - Valor a ser copiado para String dinâmica
@param min_length_allocated - Quantidade mínima que estar alocado
@return Nova instância de String dinâmica
*/
String* new_string_allocated(const char* s, int min_length_allocated) {
    String* str = (String*) malloc(sizeof(String));
    str->min_extra = STRING_DEFAULT_MIN_EXTRA;
    str->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED;
    str->lenght = strlen(s);
    str->__length_allocated = 0;
    str->__length_allocated = STRING_STRICT_STRATEGY_REALLOCATED(str->__length_allocated, str->lenght);
    str->__length_allocated = MAX(str->__length_allocated, min_length_allocated);
    str->c_str = (char*) malloc(sizeof(char) * str->__length_allocated);
    strcpy(str->c_str, s);
    return str;
}

/*
Construtor da string dinâmica

String->min_extra = STRING_DEFAULT_MIN_EXTRA # 20
String->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED # STRING_HALF_STRATEGY_REALLOCATED

@param s - Valor a ser copiado para String dinâmica
@return Nova instância de String dinâmica
*/
String* new_string(const char* s) {
    return new_string_reallocate_strategy(s, STRING_DEFAULT_MIN_EXTRA, STRING_DEFAULT_STRATEGY_REALLOCATED);
}

/*
@param str - Instância da String dinâmicas
@return - quantidade de espaço alocado para a String dinâmica
*/
int string_get_length_allocated(String* str) {
    return str->__length_allocated;
}

/*
Implementa a função realloc usando malloc e free
*/
void* __mfrealloc(void* __ptr, size_t __new_size, size_t __old_size) {
    void* ptr = malloc(__new_size);
    memcpy(ptr, __ptr, MIN(__old_size, __new_size));
    free(__ptr);
    return ptr;
}

/*
Informa a quantidade mínima de espaço que deve estar alocado
para uma determinada String dinâmica (esse método não irá
interferir em uma realocações futuras)

@param str - String dinâmica
@param length_allocated - quantidade mínima que deve estar alocada
@return - 1 se uma realocação foi necessária, 0 caso contrário
*/
short string_set_min_length_allocated(String* str, int length_allocated) {
    if (str->__length_allocated >= length_allocated)
        return 0;

    str->c_str = (char*) __mfrealloc(str->c_str, sizeof(char) * length_allocated, str->__length_allocated);
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
short string_set_max_length_allocated(String* str, int length_allocated) {
    if (str->__length_allocated <= length_allocated || str->lenght >= length_allocated)
        return 0;

    str->c_str = (char*) __mfrealloc(str->c_str, sizeof(char) * length_allocated, str->__length_allocated);
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
short string_set_length_allocated(String* str, int length_allocated) {
    if (str->lenght >= length_allocated)
        return 0;

    str->c_str = (char*) __mfrealloc(str->c_str, sizeof(char) * length_allocated, str->__length_allocated);
    str->__length_allocated = length_allocated;
    return 1;
}

/*
Atribui novo valor para a String dinâmica

@param str - Instância da String dinâmica
@param s - Valor a ser atribuído a 'str'
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short string_set(String* str, const char* s) {
    str->lenght = strlen(s);
    int flag = 0;

    while (str->__length_allocated <= str->lenght) {
        str->__length_allocated = str->reallocate_strategy(str->__length_allocated, str->lenght);
        flag = 1;
    }

    if (flag) {
        str->__length_allocated = MAX(str->__length_allocated, (str->lenght+1) + (str->min_extra));
        str->c_str = (char*) __mfrealloc(str->c_str, sizeof(char) * str->__length_allocated, str->__length_allocated);
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
short string_cat(String* str, const char* s) {
    int len_s = strlen(s);
    char ns[len_s + str->lenght + 2];
    strcpy(ns, "");
    strcpy(ns, str->c_str);
    strcat(ns, s);
    string_set(str, ns);
    return 1;
}

/*
Remove a String dinâmica da memória

@param str - Instância da String dinâmica a ser removida
@return - 1 se foi executado com sucesso, 0 caso contrário
*/
short string_free(String* str) {
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
    já estar alocada. Não pode ser a mesma instância de str
@param start - Posição inicial da substring
@param end - Posição final da substring (não incluso)
@return - 1 se executado com sucesso, 0 caso contrário
*/
short string_sub(String* str, String* target, int start, int end) {
    if (str == target)
        return 0;

    int len = strlen(str->c_str);

    if (len < end || start >= end)
        return 0;

    int len_sub = end - start;

    string_set(target, "");
    string_set_min_length_allocated(target, len_sub + 1);

    int i;
    for (i = 0; i < len_sub; i++)
        target->c_str[i] = str->c_str[start++];

    target->c_str[len_sub] = '\0';
    target->lenght = len_sub;
    return 1;
}

/*
Retorna o tamanho do array necessário para armazenar
o resultado do método "string_split"

@param str - Instância da String dinâmica que será separada
@param sep - Separador que divide a String em várias partes
@return - Tamanho do array que armazenará o resultado
do split
*/
int string_size_split(String* str, const char* sep) {
    if (strcmp(sep, "") == 0)
        return str->lenght;

    if (str->lenght == 0)
        return 0;

    int size = 1;
    int len_sep = strlen(sep);

    int i;
    String* sub = new_string_allocated("", len_sep + 1);
    for (i = 0; i < str->lenght; i++) {
        string_sub(str, sub, i, i + len_sep);

        if (strcmp(sub->c_str, sep) == 0) {
            size++;
            i += len_sep - 1;
        }
    }

    string_free(sub);
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
short string_split(String* str, String* target[], const char* sep) {
    int len_sep = strlen(sep);
    int i_target = 0;

    if (str->lenght > 0)
        target[0] = new_string("");

    int i;
    String* sub = new_string_allocated("", len_sep + 1);
    for (i = 0; i < str->lenght; i++) {
        char ch = str->c_str[i];
        string_sub(str, sub, i, i + len_sep);

        if (strcmp(sep, "") == 0) {
            char ch_str[] = { ch, '\0' };
            string_set(target[i_target], ch_str);
            i_target++;

            if (i+1 < str->lenght)
                target[i_target] = new_string("");
        } else if (strcmp(sub->c_str, sep) == 0) {
            i_target++;
            target[i_target] = new_string("");
            i += len_sep-1;
        } else {
            char ch_str[] = { ch, '\0' };
            string_cat(target[i_target], ch_str);
        }
    }

    string_free(sub);
    return 1;
}

/*
Retorna 1 se existir uma substring igual a "value". 0 caso
contrário

@param value - substring que será buscada
*/
short string_find_sub(String* src, String* value) {
    if (value->lenght == 0)
        return 1;

    String* verify = new_string_allocated("", value->lenght + 1);
    short finded = 0;

    int i = 0;
    while (i < src->lenght) {
        if (i < src->lenght - value->lenght + 1)
            break;

        string_sub(src, verify, i, value->lenght);

        if (strcmp(verify->c_str, value->c_str) == 0) {
            finded = 1;
            break;
        }
    }

    string_free(verify);

    return finded;
}

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
void string_replace(String* src, String* target, String* replace, String* value) {
    if (src->lenght == 0 || replace->lenght == 0) {
        string_set(target, src->c_str);
        return;
    }

    string_set(target, "");
    String* verify = new_string_allocated("", replace->lenght + 1);

    int i = 0;
    while (i < src->lenght) {
        if (i >= src->lenght - replace->lenght + 1) {
            char ch[] = { src->c_str[i], '\0' };
            string_cat(target, ch);
            i++;
            break;
        }

        string_sub(src, verify, i, replace->lenght);

        if (strcmp(verify->c_str, replace->c_str) == 0) {
            string_cat(target, value->c_str);
            i += replace->lenght;

            if (string_sub(src, verify, i, src->lenght))
                string_cat(target, verify);

            break;
        } else {
            char ch[] = { src->c_str[i], '\0' };
            string_cat(target, ch);
            i++;
        }
    }

    string_free(verify);
}

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
void string_replace_all(String* src, String* target, String* replace, String* value) {
    if (src->lenght == 0 || replace->lenght == 0) {
        string_set(target, src->c_str);
        return;
    }

    string_set(target, "");
    String* verify = new_string_allocated("", replace->lenght + 1);

    int i = 0;
    while (i < src->lenght) {
        if (i >= src->lenght - replace->lenght + 1) {
            char ch[] = { src->c_str[i], '\0' };
            string_cat(target, ch);
            i++;
            break;
        }

        string_sub(src, verify, i, replace->lenght);

        if (strcmp(verify->c_str, replace->c_str) == 0) {
            string_cat(target, value->c_str);
            i += replace->lenght;
        } else {
            char ch[] = { src->c_str[i], '\0' };
            string_cat(target, ch);
            i++;
        }
    }

    string_free(verify);
}

struct __ReadLineCache {
    short extra;
    String* before;
};

void __init_read_line_cache(struct __ReadLineCache* cache) {
    cache->extra = 0;
    cache->before = NULL;
}

short __read_line(char* buffer, size_t size, FILE* file, short ignore_endl, struct __ReadLineCache* cache) {
    short NO_INPUT = 0;
    short OK = 1;
    short TOO_LONG = 2;
    short SMALL_BUFFER = 3;

    int ch;
    size_t len_before = 0;

    if (cache->before != NULL)
        len_before = cache->before->lenght;

    if (cache->before == NULL && cache->extra)
        while (((ch = fgetc(file)) != '\n') && (ch != EOF))
            cache->extra = 0;

    if (cache->before != NULL && cache->extra && len_before + 1 >= size)
        return TOO_LONG;

    if (cache->before != NULL && cache->extra) {
        memcpy(buffer, cache->before->c_str, len_before);
        buffer[len_before] = cache->extra;
        buffer[len_before + 1] = '\0';
        cache->extra = 0;

        int i = len_before + 1;
        while (((ch = fgetc(file)) != '\n') && (ch != EOF)) {
            if (strlen(buffer) + 2 > size) {
                cache->extra = ch;
                return TOO_LONG;
            } else {
                buffer[i++] = ch;
                buffer[i] = '\0';
            }
        }

        return OK;
    }

    if (size < 2)
        return SMALL_BUFFER;

    if (fgets(buffer, size, file) == NULL)
        return NO_INPUT;

    size_t len = strlen(buffer);

    if (len < 1)
        return NO_INPUT;

    if (buffer[len - 1] != '\n') {
        ch = fgetc(file);

        if (ch == EOF)
            cache->extra = 0;
        else
            cache->extra = ch;

        return cache->extra ? TOO_LONG : OK;
    }

    if (ignore_endl)
        buffer[len - 1] = '\0';

    return OK;
}

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
short string_read_full_line(FILE* file, String* target, short ignore_endl) {
    short NO_INPUT = 0;
    short OK = 1;
    short TOO_LONG = 2;
    short SMALL_BUFFER = 3;

    short status = OK;
    struct __ReadLineCache cache;
    __init_read_line_cache(&cache);

    do {
        status = __read_line(target->c_str, target->__length_allocated, file, ignore_endl, &cache);

        if (status != OK && status != NO_INPUT) {
            if (cache.before == NULL)
                cache.before = new_string(target->c_str);
            else
                string_set(cache.before, target->c_str);

            size_t alloc_size = target->reallocate_strategy(target->__length_allocated, target->lenght);
            alloc_size = MAX(alloc_size, (target->lenght+1) + (target->min_extra));
            string_set_min_length_allocated(target, alloc_size);
        }
    } while (status != OK && status != NO_INPUT);

    if (cache.before != NULL) {
        string_free(&cache.before);
        cache.before = NULL;
    }

    if (status == NO_INPUT) {
        string_set(target, "");
        return NO_INPUT;
    }

    return OK;
}
