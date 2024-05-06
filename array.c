#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numCharArrAllocs = 0;
int numCharArrFrees = 0;
int numStrAllocs = 0;
int numStrFrees = 0;
int numStrArrAllocs = 0;
int numStrArrFrees = 0;
int numElementsAllocs = 0;
int numElementsFrees = 0;

int main(void) {
    StrArr *arr = initStrArr();

    while (1) {
        printf("Getting string from stdin\n");
        String *str = getStringFromStdin();

        if (str == NULL) {
            printf("str is NULL\n");
            freeStrArr(arr);
            exit(1);
        }

        appendStr(arr, str);

        if (strcmp(str->chars, "quit\n") == 0) {
            printStrArr(arr);
            freeStrArr(arr);
            printf("Num char arr allocs: %d\nNum char arr frees: %d\n",
                   numCharArrAllocs, numCharArrFrees);

            printf("Num String allocs: %d\nNum String frees: %d\n",
                   numStrAllocs, numStrFrees);

            printf("Num String Array Allocs: %d\nNum String Array frees: %d\n",
                   numStrArrAllocs, numStrArrFrees);

            printf("Num elements allocs: %d\nNum elements frees: %d\n",
                   numElementsAllocs, numElementsFrees);

            break;
        }
    }

    return 0;
}

void printStrArr(StrArr *arr) {
    printf("Printing string array.\n");
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
        numStrFrees++;
        free(input);

        return NULL;
    }

    appendCharArr(str, input);
    printf("freeing %p\n", input);
    free(input);
    printf("Made it past 1\n");
    return str;
}

/**
 * Initializes a dynamic character array capable of holding <INITIAL_SIZE>
 * strings. Caller is responsible for calling `free()` on the array and its
 * elements.
 */
String *initStr() {
    char *chars = malloc(sizeof(char) * INITIAL_SIZE);
    printf("allocated memory for char arr at: %p\n", chars);
    numCharArrAllocs++;
    String *str = malloc(sizeof(String));
    numStrAllocs++;

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

    printf("Size of input string is: %zu\n", size);
    size_t spaceNeeded = size + str->length + 1; // + 1 for the null terminator.
    printf("Space needed is: %zu\n", spaceNeeded);
    size_t oldCap = str->capacity;
    printf("old capacity is: %zu\n", oldCap);

    /**
     * This needs to be a loop because chars could hold any number of elements.
     * In other words, it is possible for spaceNeeded to be greater
     * than the growth factor * str->capacity
     */
    while (spaceNeeded > str->capacity) {
        // reallocate enough memory for chars
        printf("Resizing string.\n");
        resizeStr(str);
    }

    // resetting length it in the loop would mess with the resize function.
    if (spaceNeeded > oldCap) {
        str->length = 0; // reset str length as it is new memory.
    }

    for (size_t i = 0; i < size; ++i) {
        appendChar(str, chars[i]);
    }

    printf("length after appending: %zu\n", str->length);
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

    printf("Allocated memory for newChars at %p\n", newChars);
    numCharArrAllocs++;

    char *oldChars = str->chars;
    str->chars = newChars;

    if (str->length > 0) {
        for (size_t i = 0; i < str->length; ++i) {
            newChars[i] = str->chars[i];
        }
    }

    printf("Freeing char array: %p\n", oldChars);
    free(oldChars);
    numCharArrFrees++;

    str->capacity = newCapacity;
    printf("String was resized from %zu to %zu\n", oldCap, newCapacity);
}

void freeStr(String *str) {
    printf("Freeing char array: %p\n", str->chars);
    free(str->chars);
    free(str);
    numStrFrees++;
    numCharArrFrees++;
}

//

/**
 * Initializes a dynamic string array capable of holding <INITIAL_SIZE> strings.
 * Caller is responsible for calling `free()` on the array and its elements.
 */
StrArr *initStrArr() {
    StrArr *arr = malloc(sizeof(StrArr));
    numStrArrAllocs++;
    String **elements = malloc(sizeof(String *) * INITIAL_SIZE);
    numElementsAllocs++;

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
        printf("resizing string array.\n");
        resizeStrArr(arr);
    }

    arr->elements[arr->length++] = str;

    printf("Array length is: %zu\n", arr->length);
}

void resizeStrArr(StrArr *arr) {
    size_t oldCap = arr->capacity;
    size_t newCapacity = arr->capacity * GROWTH_FACTOR;

    String **newElements = malloc(sizeof(String *) * newCapacity);
    numElementsAllocs++;

    if (newElements == NULL) {
        fprintf(stderr, "Unable to allocate memory for new array elements.\n");
        // I should free here but the OS will do it for me \_( =] )_/
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

    printf("freeing %p\n", oldElements);
    free(oldElements);
    numElementsFrees++;
    printf("made it past 3.\n");
    arr->capacity = newCapacity;

    printf("Array was resized from %zu to %zu\n", oldCap, newCapacity);
}

void freeStrArr(StrArr *arr) {
    printf("freeing strings\n");

    /**
     * Start at 1 because we free the 0th element after the loop with
     * free(arr->elements)
     */
    for (size_t i = 0; i < arr->length; ++i) {
        freeStr(arr->elements[i]);
    }

    printf("Freeing %p.\n", arr->elements);
    free(arr->elements);
    numElementsFrees++;
    printf("Freeing array %p\n", arr);
    free(arr);
    numStrArrFrees++;
}
