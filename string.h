// Headers
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// The two next functions are already defined in <string.h> as strcpy and strlen, but we have recreated them for control's sake.
// Set a string buffer to a buffer of chars.
void bfr_str_set(char *bfr, char str[]) {
    size_t i = 0;
    for (; str[i] != '\0'; i++) {
        bfr[i] = str[i];
    }
    bfr[i] = '\0';
}

// Get the length of a string.
size_t stringlen(char *bfr) {
    size_t len = 0;
    while (bfr[len] != '\0') {
        len++;
    }
    return len;
}

// Define a macro constructor, and the String smart pointer.
#define String(x) string_from(x)
typedef struct {
    char *data;
    size_t len;
    size_t cap;
} String;

// Generate a String smart pointer from a buffer of chars.
String string_from(char *str) {
    String s = {0};
    s.len = stringlen(str);
    s.data = malloc(s.len+1);
    if (s.data == NULL) exit(1);
    bfr_str_set(s.data, str);

    return s;
}

// Change the string data of an active String smart pointer.
bool string_to(String *s, char *literal) {
    if (s->data == NULL || s->len != stringlen(s->data)) return false;

    size_t len = stringlen(literal);
    size_t cap = len + 1;

    s->data = realloc(s->data, cap);
    if (s->data == NULL) exit(1);
    s->len = len;
    s->cap = cap;
    bfr_str_set(s->data, literal);

    return true;
}

// Free up the memory of the String smart pointer, and do housekeeping to make sure that the pointer won't be used after freeing.
void free_string(String *s) {
    if (s->data != NULL) {
        free(s->data);
        s->data = NULL;
    }
    s->cap = 0;
    s->len = 0;
}