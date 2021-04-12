#include <stdio.h>
#include "cemdutil/dynamic_string.h"

int main (int argc, const char* argv[]) {

    String* str = new_string("123");

    printf("%d\n", string_get_length_allocated(str));

    string_set_min_length_allocated(str, 20);

    printf("%d\n", string_get_length_allocated(str));

    string_set_min_length_allocated(str, 40);

    printf("%d\n", string_get_length_allocated(str));

    string_set_max_length_allocated(str, 2);

    printf("%d\n", string_get_length_allocated(str));

    string_set_max_length_allocated(str, 4);

    printf("%d\n", string_get_length_allocated(str));

    string_set_max_length_allocated(str, 3);

    printf("%d\n", string_get_length_allocated(str));

    string_set_length_allocated(str, 100);

    printf("%d\n", string_get_length_allocated(str));

    string_set_length_allocated(str, 50);

    printf("%d\n", string_get_length_allocated(str));

    string_set_length_allocated(str, 10);

    printf("%d\n", string_get_length_allocated(str));

    string_set(str, "Meu Feijão com Arroz");

    printf("%s\n", string_c(str));
    printf("%d\n", str->lenght);
    printf("%d\n", string_get_length_allocated(str));

    string_cat(str, "oiujmnfghvbfteqaxdpzsu");

    printf("%s\n", string_c(str));
    printf("%d\n", str->lenght);
    printf("%d\n", string_get_length_allocated(str));

    String* sub = new_string("");
    string_sub(str, sub, 4, 30);
    printf("%s\n", string_c(str));
    printf("%d\n", sub->lenght);
    printf("%d\n", string_get_length_allocated(sub));
    string_clear(sub);
    free(sub);

    int sizeSplit = string_size_split(str, "e");
    printf("sizeSplit = %d\n", sizeSplit);
    String* splitArray[sizeSplit];
    string_split(str, splitArray, "e");
    int i;
    for (i = 0; i < sizeSplit; i++) {
        printf("str = %s\n", string_c(splitArray[i]));
    }

    for (i = 0; i < sizeSplit; i++) {
        string_clear(splitArray[i]);
        free(splitArray[i]);
    }

    string_clear(str);
    free(str);

    str = new_string_reallocate_strategy("Hello!", 0, 2, STRING_STRICT_REALLOCATE_STRATEGY);

    printf("%s / %d / %d\n", string_c(str), str->lenght, string_get_length_allocated(str));

    string_cat(str, " World!");

    printf("%s / %d / %d\n", string_c(str), str->lenght, string_get_length_allocated(str));

    string_clear(str);
    free(str);

    str = new_string_reallocate_strategy("Hello!", 0, 2, STRING_HALF_REALLOCATE_STRATEGY);

    printf("%s / %d / %d\n", string_c(str), str->lenght, string_get_length_allocated(str));

    string_cat(str, " World!");

    printf("%s / %d / %d\n", string_c(str), str->lenght, string_get_length_allocated(str));

    string_clear(str);
    free(str);

    str = new_string_reallocate_strategy("Hello!", 0, 2, STRING_DOUBLE_REALLOCATE_STRATEGY);

    printf("%s / %d / %d\n", string_c(str), str->lenght, string_get_length_allocated(str));

    string_cat(str, " World!");

    printf("%s / %d / %d\n", string_c(str), str->lenght, string_get_length_allocated(str));

    string_clear(str);
    free(str);

    str = new_string_allocated("1234567", 9);

    printf("%d\n", string_get_length_allocated(str));

    string_clear(str);
    free(str);

    str = new_string_allocated("1234567", 3);

    printf("%d\n", string_get_length_allocated(str));

    string_clear(str);
    free(str);

    return 0;
}