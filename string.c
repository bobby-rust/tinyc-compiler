#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

void print_str_array(StrArray *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        printf("%s\n", arr->elements[i]->chars);
    }
}

String *get_str_from_stdin() {
    String *str = init_str();
    if (str == NULL) {
        exit(1);
    }

    char *input = NULL;
    size_t size = 0;
    printf("> ");
    ssize_t chars_read = getline(&input, &size, stdin);

    if (chars_read < 0) {
        puts("Error reading input.");
        free(str);
        // numStrFrees++;
        free(input);

        return NULL;
    }

    append_char_array(str, input);
    free(input);
    return str;
}

/**
 * Initializes a dynamic character array capable of holding <INITIAL_SIZE>
 * strings. Caller is responsible for calling `free()` on the array and its
 * elements.
 */
String *init_str() {
    char *chars = malloc(sizeof(char) * INITIAL_SIZE);
    String *str = malloc(sizeof(String));

    if (chars == NULL || str == NULL) {
        fprintf(stderr, "Unable to allocate memory for string.\n");
        return NULL;
    }

    str->capacity = INITIAL_SIZE;
    str->length = 0;
    str->chars = chars;

    return str;
}

void append_char(String *str, char ch) {
    str->chars[str->length++] = ch;
    str->chars[str->length] = '\0';
}

void append_char_array(String *str, char *chars) {
    size_t size = strlen(chars);
    size_t space_needed =
        size + str->length + 1; // + 1 for the null terminator.
    size_t old_cap = str->capacity;

    /**
     * This needs to be a loop because chars could hold any number of elements.
     * In other words, it is possible for spaceNeeded to be greater
     * than the growth factor * str->capacity
     */
    while (space_needed > str->capacity) {
        // reallocate enough memory for chars
        resize_str(str);
    }

    // resetting length it in the loop would mess with the resize function.
    if (space_needed > old_cap) {
        str->length = 0; // reset str length as it is new memory.
    }

    for (size_t i = 0; i < size; ++i) {
        append_char(str, chars[i]);
    }
}

void resize_str(String *str) {
    // init new string with new capacity
    size_t new_cap = str->capacity * GROWTH_FACTOR;
    char *new_chars = malloc(sizeof(char) * new_cap);

    if (new_chars == NULL) {
        fprintf(stderr, "Unable to allocate memory for new character array.\n");
        exit(1);
    }

    char *old_chars = str->chars;
    str->chars = new_chars;

    if (str->length > 0) {
        for (size_t i = 0; i < str->length; ++i) {
            new_chars[i] = str->chars[i];
        }
    }

    free(old_chars);
    str->capacity = new_cap;
}

void free_str(String *str) {
    free(str->chars);
    free(str);
}

void print_str(String *str) {
    size_t len = str->length;

    for (size_t i = 0; i < len; ++i) {
        printf("%c", str->chars[i]);
    }

    printf("\n");
}

/**
 * Initializes a dynamic string array capable of holding <INITIAL_SIZE> strings.
 * Caller is responsible for calling `free()` on the array and its elements.
 */
StrArray *init_str_array() {
    StrArray *arr = malloc(sizeof(StrArray));
    String **elements = malloc(sizeof(String *) * INITIAL_SIZE);

    if (arr == NULL || elements == NULL) {
        fprintf(stderr, "Unable to allocate memory for string.\n");
        return NULL;
    }

    arr->capacity = INITIAL_SIZE;
    arr->elements = elements;
    arr->length = 0;

    return arr;
}

/**
 * Appends a string <str> to the end of the string array <arr>
 */
void append_str(StrArray *arr, String *str) {
    /**
     * This does not need to be a loop as this function appends
     * exactly one element to the array.
     */
    if (arr->length >= arr->capacity) {
        resize_str_array(arr);
    }

    arr->elements[arr->length++] = str;
}

void resize_str_array(StrArray *arr) {
    size_t new_cap = arr->capacity * GROWTH_FACTOR;

    String **new_elements = malloc(sizeof(String *) * new_cap);

    if (new_elements == NULL) {
        fprintf(stderr, "Unable to allocate memory for new array elements.\n");
        free_str_array(arr);
        exit(1);
    }

    String **old_elements = arr->elements;
    arr->elements = new_elements;
    size_t num_old_elements = arr->length;
    arr->length = 0;
    for (size_t i = 0; i < num_old_elements; ++i) {
        append_str(arr, old_elements[i]);
    }

    free(old_elements);
    arr->capacity = new_cap;
}

void free_str_array(StrArray *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        free_str(arr->elements[i]);
    }

    free(arr->elements);
    free(arr);
}

// int main(void) { return 0; }

// int main(void) {
//     StrArr *arr = initStrArr();

//     while (1) {
//         String *str = getStringFromStdin();

//         if (str == NULL) {
//             fprintf(stderr, "str is NULL\n");
//             freeStrArr(arr);
//             exit(1);
//         }

//         appendStr(arr, str);

//         if (strcmp(str->chars, "quit\n") == 0) {
//             printStrArr(arr);
//             freeStrArr(arr);
//             break;
//         }
//     }

//     return 0;
// }
