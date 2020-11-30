#include <math.h>
#include "cemdutil/dynamic_string.h"

/**
 * Implementa a função realloc usando malloc e free
 *
 * @param _ptr ponteiro a ser realocado
 * @param _new_size novo tamanho para o ponteiro
 * @param _old_size atual tamanho para o ponteiro
 * @return novo ponteiro realocado
 */
void* __mfrealloc(void* _ptr, size_t _new_size, size_t _old_size) {
    void* ptr = malloc(_new_size);
    memcpy(ptr, _ptr, MIN(_old_size, _new_size));
    free(_ptr);
    return ptr;
}

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
size_t STRING_STRICT_STRATEGY_REALLOCATED(size_t length_allocated, size_t lenght) {
    return lenght+1;
}

/**
 * É a estratégia de realocar adicionando a metade do tamanho da string
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param lenght quantidade de caracteres atualmente armazenados na String,
 *        desconsiderando o \0
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
size_t STRING_HALF_STRATEGY_REALLOCATED(size_t length_allocated, size_t lenght) {
    lenght++;
    size_t half = ceil(lenght / 2.0);
    return lenght + half;
}

/**
 * É a estratégia de realocar o dobro do que foi alocado anteriormente
 *
 * @param length_allocated expaço atualmente definido para realocação
 * @param lenght quantidade de caracteres atualmente armazenados na String,
 *        desconsiderando o \0
 * @return novo espaço a ser realocado (se não for o suficiente, a função será
 *         chamada novamente)
 */
size_t STRING_DOUBLE_STRATEGY_REALLOCATED(size_t length_allocated, size_t lenght) {
    length_allocated = MAX(1, length_allocated);
    return length_allocated*2;
}

/**
 * Obtém a String dinâmica no formato C
 *
 * @param str instância da string dinâmica
 * @return string no formato c
 */
char* string_c(String* str) {
    if (str->__c_str == NULL) {
        str->__c_str = (char*) malloc(sizeof(char));
        str->lenght = 0;
        str->__c_str[0] = '\0';
        str->__length_allocated = 1;
    }
    return str->__c_str;
}

void __string_set_c(String* str, char* c_str) {
    str->__c_str = c_str;
}

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
void string_init_reallocate_strategy(String* str, const char* s, size_t min_length_allocated, size_t min_extra, StringReallocateStrategy* reallocate_strategy) {
    if (s == NULL) s = "";
    str->min_extra = min_extra;
    str->reallocate_strategy = reallocate_strategy;
    str->lenght = strlen(s);
    str->__length_allocated = 1;

    while (str->__length_allocated <= str->lenght) {
        str->__length_allocated = str->reallocate_strategy(str->__length_allocated, str->lenght);
    }

    str->__length_allocated = MAX(str->__length_allocated, min_length_allocated);
    str->__length_allocated = MAX(str->__length_allocated, (str->lenght+1) + (str->min_extra));
    __string_set_c(str, (char*) malloc(sizeof(char) * str->__length_allocated));
    strcpy(string_c(str), s);
}

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
void string_init_allocated(String* str, const char* s, size_t min_length_allocated) {
    if (s == NULL) s = "";
    str->min_extra = STRING_DEFAULT_MIN_EXTRA;
    str->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED;
    str->lenght = strlen(s);
    str->__length_allocated = 1;
    str->__length_allocated = MAX(str->__length_allocated, min_length_allocated);
    str->__length_allocated = MAX(str->__length_allocated, (str->lenght+1) + (str->min_extra));
    __string_set_c(str, (char*) malloc(sizeof(char) * str->__length_allocated));
    strcpy(string_c(str), s);
}

/**
 * Inicializador de string dinâmica
 *
 * String->min_extra = STRING_DEFAULT_MIN_EXTRA # 20
 * String->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED # STRING_HALF_STRATEGY_REALLOCATED
 *
 * @param str instância de String dinâmica
 * @param s valor a ser copiado para String dinâmica
 */
void string_init(String* str, const char* s) {
    string_init_reallocate_strategy(str, s, 0, STRING_DEFAULT_MIN_EXTRA, STRING_DEFAULT_STRATEGY_REALLOCATED);
}

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
String* new_string_reallocate_strategy(const char* s, size_t min_length_allocated, size_t min_extra, StringReallocateStrategy* reallocate_strategy) {
    String* str = (String*) malloc(sizeof(String));
    string_init_reallocate_strategy(str, s, min_length_allocated, min_extra, reallocate_strategy);
    return str;
}

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
String* new_string_allocated(const char* s, size_t min_length_allocated) {
    String* str = (String*) malloc(sizeof(String));
    string_init_allocated(str, s, min_length_allocated);
    return str;
}

/**
 * Cria uma string dinâmica
 *
 * String->min_extra = STRING_DEFAULT_MIN_EXTRA # 20
 * String->reallocate_strategy = STRING_DEFAULT_STRATEGY_REALLOCATED # STRING_HALF_STRATEGY_REALLOCATED
 *
 * @param s valor a ser copiado para String dinâmica
 * @return nova instância de String dinâmica
 */
String* new_string(const char* s) {
    String* str = (String*) malloc(sizeof(String));
    string_init(str, s);
    return str;
}

/**
 * @param str instância da String dinâmicas
 * @return quantidade de espaço alocado para a String dinâmica
 */
size_t string_get_length_allocated(String* str) {
    return str->__length_allocated;
}

/**
 * Informa a quantidade mínima de espaço que deve estar alocado
 * para uma determinada String dinâmica (esse método não irá
 * interferir em realocações futuras)
 *
 * @param str String dinâmica
 * @param length_allocated quantidade mínima que deve estar alocada
 * @return 0 se uma realocação foi necessária
 */
short string_set_min_length_allocated(String* str, size_t length_allocated) {
    if (str->__length_allocated >= length_allocated)
        return 1;

    size_t new_length = sizeof(char) * length_allocated;
    size_t old_length = sizeof(char) * str->__length_allocated;
    __string_set_c(str, (char*) __mfrealloc(string_c(str), new_length, old_length));
    str->__length_allocated = length_allocated;
    return 0;
}

/**
 * Informa a quantidade máxima de espaço que deve estar alocado
 * para uma determinada String dinâmica (esse método não irá
 * interferir em uma realocações futuras)
 *
 * @param str String dinâmica
 * @param length_allocated quantidade máxima que deve estar alocada
 * @return 0 se uma realocação foi necessária
 */
short string_set_max_length_allocated(String* str, size_t length_allocated) {
    if (str->__length_allocated <= length_allocated || str->lenght >= length_allocated)
        return 1;

    size_t new_length = sizeof(char) * length_allocated;
    size_t old_length = sizeof(char) * str->__length_allocated;
    __string_set_c(str, (char*) __mfrealloc(string_c(str), new_length, old_length));
    str->__length_allocated = length_allocated;
    return 0;
}

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
short string_set_length_allocated(String* str, size_t length_allocated) {
    if (str->lenght >= length_allocated)
        return 1;

    size_t new_length = sizeof(char) * length_allocated;
    size_t old_length = sizeof(char) * str->__length_allocated;
    __string_set_c(str, (char*) __mfrealloc(string_c(str), new_length, old_length));
    str->__length_allocated = length_allocated;
    return 0;
}

/**
 * Atribui novo valor para a String dinâmica
 *
 * @param str instância da String dinâmica
 * @param s valor a ser atribuído a 'str'
 */
void string_set(String* str, const char* s) {
    str->lenght = strlen(s);
    short flag = 0;
    size_t length_allocated = str->__length_allocated;

    while (length_allocated <= str->lenght) {
        length_allocated = str->reallocate_strategy(length_allocated, str->lenght);
        flag = 1;
    }

    if (flag) {
        length_allocated = MAX(length_allocated, str->lenght + str->min_extra + 1);
        size_t new_length = sizeof(char) * length_allocated;
        size_t old_length = sizeof(char) * str->__length_allocated;
        __string_set_c(str, (char*) __mfrealloc(string_c(str), new_length, old_length));
        str->__length_allocated = length_allocated;
    }

    strcpy(string_c(str), s);
}

/**
 * Concatena a String dinâmica com um valor
 *
 * @param str instância da String dinâmica
 * @param s valor a ser concatenado
 */
void string_cat(String* str, const char* s) {
    size_t len_s = strlen(s);
    char ns[len_s + str->lenght + 2];
    strcpy(ns, "");
    strcpy(ns, string_c(str));
    strcat(ns, s);
    string_set(str, ns);
}

/**
 * Apaga da memória os caracteres da String dinâmica.
 * Não apaga String dinâmica da memória
 *
 * @param _str instância da String dinâmica a ser removida
 */
void string_clear(void* _str) {
    String* str = (String*) _str;
    str->__length_allocated = 0;
    str->lenght = 0;

    char* c_str = string_c(str);
    __string_set_c(str, NULL);
    if (c_str != NULL)
        free(c_str);
}

/**
 * Apaga da memória os caracteres da String dinâmica.
 * Apaga String dinâmica da memória
 *
 * @param _str instância da String dinâmica a ser removida
 */
void string_free(void* _str) {
    string_clear(_str);
    free(_str);
}

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
void string_sub(String* str, String* target, size_t start, size_t end) {
    if (str == target)
        exit(1);

    size_t len = str->lenght;

    if (len < end || start >= end || start < 0)
        exit(1);

    size_t len_sub = end - start;

    string_set(target, "");
    string_set_min_length_allocated(target, len_sub + 1);

    size_t i;
    for (i = 0; i < len_sub; i++)
        string_c(target)[i] = string_c(str)[start++];

    string_c(target)[len_sub] = '\0';
    target->lenght = len_sub;
}

/**
 * Retorna o tamanho do array necessário para armazenar
 * o resultado do método "string_split"
 *
 * @param str instância da String dinâmica que será separada
 * @param sep separador que divide a String em várias partes
 * @return tamanho do array que armazenará o resultado
 *         do split
 */
size_t string_size_split(String* str, const char* sep) {
    if (strcmp(sep, "") == 0)
        return str->lenght;

    if (str->lenght == 0)
        return 0;

    size_t size = 1;
    size_t len_sep = strlen(sep);

    size_t i;
    String* sub = new_string_allocated("", len_sep + 1);
    for (i = 0; i < str->lenght; i++) {
        string_sub(str, sub, i, i + len_sep);

        if (strcmp(string_c(sub), sep) == 0) {
            size++;
            i += len_sep - 1;
        }
    }

    string_clear(sub);
    free(sub);
    return size;
}

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
void string_split(String* str, String* target[], const char* sep) {
    size_t len_sep = strlen(sep);
    size_t i_target = 0;

    if (str->lenght > 0)
        target[0] = new_string("");
    else
        return;

    size_t i;
    String* sub = new_string_allocated("", len_sep + 1);
    for (i = 0; i < str->lenght; i++) {
        char ch = string_c(str)[i];
        string_sub(str, sub, i, i + len_sep);

        if (strcmp(sep, "") == 0) {
            char ch_str[] = { ch, '\0' };
            string_set(target[i_target], ch_str);
            i_target++;

            if (i+1 < str->lenght)
                target[i_target] = new_string("");
        } else if (strcmp(string_c(sub), sep) == 0) {
            i_target++;
            target[i_target] = new_string("");
            i += len_sep-1;
        } else {
            char ch_str[] = { ch, '\0' };
            string_cat(target[i_target], ch_str);
        }
    }

    string_clear(sub);
    free(sub);
}

/**
 * Busca a primeira posição da substring na String dinâmica
 *
 * @param target substring que será buscada
 * @return primeira posição da substring na String dinâmica. -1 se não for encontrado
 */
size_t string_find_sub(String* src, String* value) {
    if (value->lenght == 0)
        return 1;

    String* verify = new_string_allocated("", value->lenght + 1);
    short index = -1;

    size_t i = 0;
    while (i < src->lenght) {
        if (i < src->lenght - value->lenght + 1)
            break;

        string_sub(src, verify, i, value->lenght);

        if (strcmp(string_c(verify), string_c(value)) == 0) {
            index = i;
            break;
        }
    }

    string_clear(verify);
    free(verify);

    return index;
}

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
void string_replace(String* src, String* target, String* replace, String* value) {
    if (src->lenght == 0 || replace->lenght == 0) {
        string_set(target, string_c(src));
        return;
    }

    string_set(target, "");
    String* verify = new_string_allocated("", replace->lenght + 1);

    size_t i = 0;
    while (i < src->lenght) {
        if (i >= src->lenght - replace->lenght + 1) {
            char ch[] = { string_c(src)[i], '\0' };
            string_cat(target, ch);
            i++;
            break;
        }

        string_sub(src, verify, i, replace->lenght);

        if (strcmp(string_c(verify), string_c(replace)) == 0) {
            string_cat(target, string_c(value));
            i += replace->lenght;
            string_sub(src, verify, i, src->lenght);
            string_cat(target, string_c(verify));
            break;
        } else {
            char ch[] = { string_c(src)[i], '\0' };
            string_cat(target, ch);
            i++;
        }
    }

    string_clear(verify);
    free(verify);
}

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
void string_replace_all(String* src, String* target, String* replace, String* value) {
    if (src->lenght == 0 || replace->lenght == 0) {
        string_set(target, string_c(src));
        return;
    }

    string_set(target, "");
    String* verify = new_string_allocated("", replace->lenght + 1);

    size_t i = 0;
    while (i < src->lenght) {
        if (i >= src->lenght - replace->lenght + 1) {
            char ch[] = { string_c(src)[i], '\0' };
            string_cat(target, ch);
            i++;
            break;
        }

        string_sub(src, verify, i, replace->lenght);

        if (strcmp(string_c(verify), string_c(replace)) == 0) {
            string_cat(target, string_c(value));
            i += replace->lenght;
        } else {
            char ch[] = { string_c(src)[i], '\0' };
            string_cat(target, ch);
            i++;
        }
    }

    string_clear(verify);
    free(verify);
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
    short OK = 0;
    short NO_INPUT = 1;
    short TOO_LONG = 2;
    short SMALL_BUFFER = 3;

    size_t ch;
    size_t len_before = 0;

    if (cache->before != NULL)
        len_before = cache->before->lenght;

    if (cache->before == NULL && cache->extra)
        while (((ch = fgetc(file)) != '\n') && (ch != EOF))
            cache->extra = 0;

    if (cache->before != NULL && cache->extra && len_before + 1 >= size)
        return TOO_LONG;

    if (cache->before != NULL && cache->extra) {
        memcpy(buffer, string_c(cache->before), len_before);
        buffer[len_before] = cache->extra;
        buffer[len_before + 1] = '\0';
        cache->extra = 0;

        size_t i = len_before + 1;
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
short string_read_full_line(FILE* file, String* target, short ignore_endl) {
    short OK = 0;
    short NO_INPUT = 1;

    short status = OK;
    struct __ReadLineCache cache;
    __init_read_line_cache(&cache);

    do {
        status = __read_line(string_c(target), target->__length_allocated, file, ignore_endl, &cache);

        if (status != OK && status != NO_INPUT) {
            if (cache.before == NULL)
                cache.before = new_string(string_c(target));
            else
                string_set(cache.before, string_c(target));

            size_t alloc_size = target->reallocate_strategy(target->__length_allocated, target->lenght);
            alloc_size = MAX(alloc_size, (target->lenght+1) + (target->min_extra));
            string_set_min_length_allocated(target, alloc_size);
        }
    } while (status != OK && status != NO_INPUT);

    if (cache.before != NULL) {
        string_clear(cache.before);
        free(cache.before);
        cache.before = NULL;
    }

    if (status == NO_INPUT) {
        string_set(target, "");
        return NO_INPUT;
    }

    return OK;
}
