#include <stdio.h>
#include "include/dynamic_string.h"

int main (int argc, const char* argv[]) {

    String* str = new_string("123");

    printf("%d\n", get_length_allocated_string(str));

    set_min__length_allocated(str, 20);

    printf("%d\n", get_length_allocated_string(str));

    set_min__length_allocated(str, 40);

    printf("%d\n", get_length_allocated_string(str));

    set_max__length_allocated(str, 2);

    printf("%d\n", get_length_allocated_string(str));

    set_max__length_allocated(str, 4);

    printf("%d\n", get_length_allocated_string(str));

    set_max__length_allocated(str, 3);

    printf("%d\n", get_length_allocated_string(str));

    set__length_allocated(str, 100);

    printf("%d\n", get_length_allocated_string(str));

    set__length_allocated(str, 50);

    printf("%d\n", get_length_allocated_string(str));

    set__length_allocated(str, 10);

    printf("%d\n", get_length_allocated_string(str));

    set_string(str, "Meu Feijão com Arroz");

    printf("%s\n", str->c_str);
    printf("%d\n", str->lenght);
    printf("%d\n", get_length_allocated_string(str));

    cat_string(str, "oiujmnfghvbfteqaxdpzsu");

    printf("%s\n", str->c_str);
    printf("%d\n", str->lenght);
    printf("%d\n", get_length_allocated_string(str));

    String* sub = new_string("");
    sub_string(str, sub, 4, 30);
    printf("%s\n", sub->c_str);
    printf("%d\n", sub->lenght);
    printf("%d\n", get_length_allocated_string(sub));
    free_string(sub);

    int sizeSplit = size_split_string(str, "e");
    printf("sizeSplit = %d\n", sizeSplit);
    String* splitArray[sizeSplit];
    split_string(str, splitArray, "e");
    int i;
    for (i = 0; i < sizeSplit; i++) {
        printf("str = %s\n", splitArray[i]->c_str);
    }
    
    for (i = 0; i < sizeSplit; i++) {
        free_string(splitArray[i]);
    }

    free_string(str);

    /*
    String* str = new_string_reallocate_strategy("Hello!", 2, STRICT_STRATEGY_REALLOCATED);

    printf("%s / %d / %d\n", str->c_str, str->lenght, get_length_allocated_string(str));

    cat_string(str, " World!");

    printf("%s / %d / %d\n", str->c_str, str->lenght, get_length_allocated_string(str));

    free_string(str);
    */

    /*
    String* str = new_string_reallocate_strategy("Hello!", 2, HALF_STRATEGY_REALLOCATED);

    printf("%s / %d / %d\n", str->c_str, str->lenght, get_length_allocated_string(str));

    cat_string(str, " World!");

    printf("%s / %d / %d\n", str->c_str, str->lenght, get_length_allocated_string(str));

    free_string(str);
    */
    
    /*
    String* str = new_string_reallocate_strategy("Hello!", 2, DOUBLE_STRATEGY_REALLOCATED);

    printf("%s / %d / %d\n", str->c_str, str->lenght, get_length_allocated_string(str));

    cat_string(str, " World!");

    printf("%s / %d / %d\n", str->c_str, str->lenght, get_length_allocated_string(str));

    free_string(str);
    */

    /*
    String* str = new_string_allocated("1234567", 9);
    
    printf("%d\n", get_length_allocated_string(str));
    
    free_string(str);
    */

    /*
    String* str = new_string_allocated("1234567", 3);
    
    printf("%d\n", get_length_allocated_string(str));
    
    free_string(str);
    */

    return 0;
}