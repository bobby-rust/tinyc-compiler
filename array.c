#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10
#define GROWTH_FACTOR 2

typedef struct {
    char *chars;
    size_t length;
    size_t capacity;
} String;

String *initStr() {
    char *chars = malloc(sizeof(char) * INITIAL_SIZE);
    String *str = malloc(sizeof(String));
    str->capacity = INITIAL_SIZE;
    str->length = 0;
    str->chars = chars;

    return str;
}

void appendChar(String *str, char ch) {
    printf("Old str length: %zu\n", str->length);

    str->chars[str->length++] = ch;
    str->chars[str->length] = '\0';
    printf("new str length: %zu\n", str->length);
}

void resize(String *str) {
    // init new string with new capacity
    size_t newCapacity = str->capacity * GROWTH_FACTOR;
    char *newChars = malloc(sizeof(char) * newCapacity);

    // copy buffer from old string to new
    strcpy(newChars, str->chars);

    // free old string memory
    free(str->chars);

    str->chars = newChars;
    str->capacity = newCapacity;
}

String *appendStr(String *str, char *chars) {
    size_t size = strlen(chars);

    if ((size + str->length) > str->capacity) {
        // reallocate enough memory for chars
        printf("Initial size of string: %zu\n", str->capacity);
        resize(str);
        printf("New size of string: %zu\n", str->capacity);
    }

    for (int i = 0; i < size; ++i) {
        appendChar(str, chars[i]);
    }

    str->length += size;
    return str;
}

int main(void) {
    String *str = initStr();

    char *input = NULL;
    size_t size = 0;
    printf("> ");
    ssize_t chars_read = getline(&input, &size, stdin);

    if (chars_read < 0) {
        puts("Error reading input.");
        free(input);
        return 1;
    }

    printf("size: %zu\nchars_read: %zd\n", size, chars_read);

    appendStr(str, input);
    printf("%s\n", str->chars);
    free(input);
    free(str->chars);
    free(str);
}

// typedef struct {
//     string *elements;
//     size_t capacity;
// } dynamicStrArr;

/**
 * Initializes a dynamic string array capable of holding <size> strings.
 * Caller is responsible for calling `free()` on the array and its elements.
 */
// dynamicStrArr *initDynamicStrArray(size_t size) {

//     dynamicStrArr *arr = malloc(sizeof(dynamicStrArr));
//     char *elements = malloc(sizeof(char) * size);

//     arr->size = size;
//     arr->elements = elements;

//     return arr;
// }

// void push(dynamicStrArr *arr) {
//     if (sizeof(arr->elements) >= arr->size) { // copy all elements to new
//     array with double the size. size_t newSize = arr->size * 2;
//         dynamicStrArr *newArr = malloc(sizeof(dynamicStrArr));
//         char *newEls = malloc(sizeof(char) * newSize);
//         for (int i = 0; i < arr->size - 1; ++i) {
//         }
//     }
// }
