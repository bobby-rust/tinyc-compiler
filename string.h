#ifndef STRING_H_
#define STRING_H_

#include <stdlib.h>

#define INITIAL_SIZE 1
#define GROWTH_FACTOR 2

typedef struct {
    char *chars;
    size_t length;
    size_t capacity;
} String;

typedef struct {
    String **elements;
    size_t length;
    size_t capacity;
} StrArr;

String *getStringFromStdin();

// String
String *initStr();
void appendChar(String *str, char ch);
void appendCharArr(String *str, char *chars);
void resizeStr(String *str);
void freeStr(String *str);
void printStr(String *str);

// String array
StrArr *initStrArr();
void appendStr(StrArr *arr, String *str);
void resizeStrArr(StrArr *arr);
void freeStrArr(StrArr *arr);
void printStrArr(StrArr *arr);

#endif // STRING_H_
