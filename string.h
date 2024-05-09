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
} StrArray;

String *get_str_from_stdin();

// String
String *init_str();
void append_char(String *str, char ch);
void append_char_array(String *str, char *chars);
void resize_str(String *str);
void free_str(String *str);
void print_str(String *str);

// String array
StrArray *init_str_array();
void append_str(StrArray *arr, String *str);
void resize_str_array(StrArray *arr);
void free_str_array(StrArray *arr);
void print_str_array(StrArray *arr);

#endif // STRING_H_
