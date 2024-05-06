#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String *getNextStringFromInput() {
    String *str = initStr();
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
        free(input);

        return NULL;
    }

    appendCharArr(str, input);
    printf("1\n");
    free(input);
    printf("Made it past 1\n");
    return str;
}

int main(void) {
    StrArr *arr = initStrArr();

    while (1) {
        String *str = getNextStringFromInput();

        if (str == NULL) {
            printf("str is NULL\n");
            freeStrArr(arr);
            exit(1);
        }

        if (strcmp(str->chars, "quit\n") == 0) {
            freeStrArr(arr);
            break;
        }

        appendStr(arr, str);
    }

    return 0;
}

/**
 * Initializes a dynamic character array capable of holding <INITIAL_SIZE>
 * strings. Caller is responsible for calling `free()` on the array and its
 * elements.
 */
String *initStr() {
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

void appendChar(String *str, char ch) {
    str->chars[str->length++] = ch;
    str->chars[str->length] = '\0';
}

String *appendCharArr(String *str, char *chars) {
    size_t size = strlen(chars);
    size_t spaceNeeded = size + str->length;

    /**
     * This needs to be a loop because chars could hold any number of elements.
     */
    while (spaceNeeded > str->capacity) {
        // reallocate enough memory for chars
        resizeStr(str);
    }

    for (size_t i = 0; i < size; ++i) {
        appendChar(str, chars[i]);
    }

    str->length += size;

    printf("String was resized from %zu to %zu\n", size, str->length);
    return str;
}

void resizeStr(String *str) {
    size_t oldCap = str->capacity; // just for debug

    // init new string with new capacity
    size_t newCapacity = str->capacity * GROWTH_FACTOR;

    char *newChars = malloc(sizeof(char) * newCapacity);

    if (newChars == NULL) {
        fprintf(stderr, "Unable to allocate memory for new character array.\n");
        exit(1);
    }
    // copy buffer from old string to new
    //

    if ((sizeof(char) * newCapacity) < str->length) {
        printf("Why?\n");
        exit(1);
    }
    strcpy(newChars, str->chars);

    // free old string memory
    printf("2\n");
    free(str->chars);

    str->chars = newChars;
    str->capacity = newCapacity;

    printf("String was resized from %zu to %zu\n", oldCap, newCapacity);
}

void freeStr(String *str) {
    free(str->chars);
    free(str);
}

/**
 * Initializes a dynamic string array capable of holding <INITIAL_SIZE> strings.
 * Caller is responsible for calling `free()` on the array and its elements.
 */
StrArr *initStrArr() {
    StrArr *arr = malloc(sizeof(StrArr));
    String *elements = malloc(sizeof(String) * INITIAL_SIZE);

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
StrArr *appendStr(StrArr *arr, String *str) {

    /**
     * This does not need to be a loop as this function appends
     * exactly one element to the array.
     */
    if (arr->length >= arr->capacity) {
        resizeStrArr(arr);
    }

    arr->elements[arr->length++] = *str;

    printf("Array length is: %zu\n", arr->length);
    return arr;
}

void resizeStrArr(StrArr *arr) {
    size_t oldCap = arr->capacity;
    size_t newCapacity = arr->capacity * GROWTH_FACTOR;

    String *newElements = malloc(sizeof(String) * newCapacity);
    if (newElements == NULL) {
        fprintf(stderr, "Unable to allocate memory for new array elements.\n");
        // I should free here but the OS will do it for me \_( =] )_/
        exit(1);
    }

    for (size_t i = 0; i < arr->length; ++i) {
        String *newStr = initStr();
        newStr->length = arr->elements[i].length;
        newStr->capacity = arr->elements[i].capacity;
        strcpy(newStr->chars, arr->elements[i].chars);
        free(&(arr->elements[i]));
    }

    printf("3\n");
    free(arr->elements);
    printf("made it past 3.");
    arr->elements = newElements;
    arr->capacity = newCapacity;

    printf("Array was resized from %zu to %zu\n", oldCap, newCapacity);
}

void freeStrArr(StrArr *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        freeStr(&(arr->elements[i]));
    }

    free(arr->elements);
    free(arr);
}
