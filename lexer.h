#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>

#include "file.h"

#define MAX_FILE_LENGTH 100
#define MAX_NUM_TOKENS                                                         \
    MAX_FILE_LENGTH // can only have as many tokens as characters in the file

typedef enum {
    // single-character tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    LESS,
    GREATER,
    PLUS,
    MINUS,
    EQUAL,
    QUOTE,
    DOUBLE_QUOTE,

    // Literals
    IDENTIFIER,
    STRING,
    INTEGER,

    // multi-character tokens
    NIL,
    IF,
    ELSE,
    DO,
    WHILE,
    END // eof - not sure if needed?
} TokenType;

static const char *token_type_string[] = {
    // single character tokens
    "left_paren", "right_paren", "left_brace", "right_brace", "semicolon",
    "less", "greater", "plus", "minus", "equal", "quote", "double_quote",

    // literals
    "identifier", "string", "integer",

    // multi-character tokens
    "nil", "if", "else", "do", "while", "end"};

typedef struct {
    TokenType type;
    String *lexeme; // holds the lexeme as it appears in the source code
    size_t line;

    struct {
        String *identifier;
        int integer;
        String *string;
    } Literal;
} Token;

typedef struct {
    Token **elements;
    size_t length;
    size_t capacity;
} TokenArray;

// TokenArr
TokenArray *init_token_array();
void append_token(TokenArray *arr, Token *token);
void resize_token_array(TokenArray *arr);
void free_token_array(TokenArray *arr);

// lexer
TokenArray *lex(String *buffer);
void run(char *buffer);
void print_file_contents(char *contents);

// Token
Token *init_token();
void run_prompt();
void free_token(Token *token);

#endif // LEXER_H_
