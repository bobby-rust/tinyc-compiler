#include <stdlib.h>

#define INITIAL_SIZE 1
#define GROWTH_FACTOR 2

typedef struct {
    char *chars;
    size_t length;
    size_t capacity;
} String;

typedef struct {
    String *elements;
    size_t capacity;
    size_t length;
} StrArr;

// String
String *initStr();
void appendChar(String *str, char ch);
String *appendCharArr(String *str, char *chars);
void resizeStr(String *str);
void freeStr(String *str);

// String array
StrArr *initStrArr();
StrArr *appendStr(StrArr *arr, String *str);
void resizeStrArr(StrArr *arr);
void freeStrArr(StrArr *arr);
