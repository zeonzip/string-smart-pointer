#include <stdio.h>
#include "string.h"

int main(void) {
    String str = String("Some text!\n");

    printf(str.data);

    string_to(&str, "Some other text!\n");

    printf(str.data);

    free_string(&str);

    return 0;
}
