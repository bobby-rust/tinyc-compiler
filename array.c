#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    StrArr *arr = initStrArr();

    while (1) {
        String *str = getStringFromStdin();

        if (str == NULL) {
            fprintf(stderr, "str is NULL\n");
            freeStrArr(arr);
            exit(1);
        }

        appendStr(arr, str);

        if (strcmp(str->chars, "quit\n") == 0) {
            printStrArr(arr);
            freeStrArr(arr);
            break;
        }
    }

    return 0;
}

void printStrArr(StrArr *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        printf("%s\n", arr->elements[i]->chars);
    }
}

String *getStringFromStdin() {
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
        // numStrFrees++;
        free(input);

        return NULL;
    }

    appendCharArr(str, input);
    free(input);
    return str;
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

void appendCharArr(String *str, char *chars) {
    size_t size = strlen(chars);
    size_t spaceNeeded = size + str->length + 1; // + 1 for the null terminator.
    size_t oldCap = str->capacity;

    /**
     * This needs to be a loop because chars could hold any number of elements.
     * In other words, it is possible for spaceNeeded to be greater
     * than the growth factor * str->capacity
     */
    while (spaceNeeded > str->capacity) {
        // reallocate enough memory for chars
        resizeStr(str);
    }

    // resetting length it in the loop would mess with the resize function.
    if (spaceNeeded > oldCap) {
        str->length = 0; // reset str length as it is new memory.
    }

    for (size_t i = 0; i < size; ++i) {
        appendChar(str, chars[i]);
    }
}

void resizeStr(String *str) {
    // init new string with new capacity
    size_t newCapacity = str->capacity * GROWTH_FACTOR;
    char *newChars = malloc(sizeof(char) * newCapacity);

    if (newChars == NULL) {
        fprintf(stderr, "Unable to allocate memory for new character array.\n");
        exit(1);
    }

    char *oldChars = str->chars;
    str->chars = newChars;

    if (str->length > 0) {
        for (size_t i = 0; i < str->length; ++i) {
            newChars[i] = str->chars[i];
        }
    }

    free(oldChars);
    str->capacity = newCapacity;
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
void appendStr(StrArr *arr, String *str) {
    /**
     * This does not need to be a loop as this function appends
     * exactly one element to the array.
     */
    if (arr->length >= arr->capacity) {
        resizeStrArr(arr);
    }

    arr->elements[arr->length++] = str;
}

void resizeStrArr(StrArr *arr) {
    size_t oldCap = arr->capacity;
    size_t newCapacity = arr->capacity * GROWTH_FACTOR;

    String **newElements = malloc(sizeof(String *) * newCapacity);

    if (newElements == NULL) {
        fprintf(stderr, "Unable to allocate memory for new array elements.\n");
        freeStrArr(arr);
        exit(1);
    }

    String **oldElements = arr->elements;
    arr->elements = newElements;
    size_t numOldEls = arr->length;
    arr->length = 0;
    for (size_t i = 0; i < numOldEls; ++i) {
        appendStr(arr, oldElements[i]);
    }

    free(oldElements);
    arr->capacity = newCapacity;
}

void freeStrArr(StrArr *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        freeStr(arr->elements[i]);
    }

    free(arr->elements);
    free(arr);
}
