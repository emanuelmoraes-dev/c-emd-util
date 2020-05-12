#include <stdio.h>
#include "include/dynamic_string.h"

int main (int argc, char* argv[]) {
    String* str = new_string("Hello World!");
    printf("%s\n", str->c_str);
    eraser_string(str);
    return 0;
}