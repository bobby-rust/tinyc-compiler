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

    // Literal.
    LITERAL,

    // multi-character tokens
    NIL,
    IF,
    ELSE,
    DO,
    WHILE,
} TokenType;

typedef enum { INTEGER, STRING, IDENTIFIER } LiteralType;

static const char *token_type_string[] = {
    // single character tokens
    "left_paren", "right_paren", "left_brace", "right_brace", "semicolon",
    "less", "greater", "plus", "minus", "equal", "quote", "double_quote",

    "literal",

    // multi-character tokens
    "nil", "if", "else", "do", "while"};

typedef struct {
    LiteralType type;
    void *data;
} Literal;

typedef struct {
    TokenType type;
    String *lexeme; // holds the lexeme as it appears in the source code
    size_t line;
    Literal *literal;
} Token;

typedef struct {
    Token **elements;
    size_t length;
    size_t capacity;
} TokenArray;

// Literal
Literal *init_literal();
Literal *create_literal(LiteralType type, void *data);
void free_literal(Literal *literal);

// TokenArr
TokenArray *init_token_array();
void append_token(TokenArray *arr, const Token *token);
void resize_token_array(TokenArray *arr);
void free_token_array(TokenArray *arr);
void print_token_array(const TokenArray *arr);

// lexer
TokenArray *lex(String *buffer, size_t *line);
char next(String *buffer);
void run(const String *buffer);
void print_file_contents(const String *contents);
void ignore_whitespace(String *buffer);
void advance(String *buffer);

// Token
Token *init_token();
Token *create_token(TokenType type, String *lexeme, size_t line,
                    Literal *literal);
void run_prompt();
void free_token(Token *token);
void print_token(const Token *token);

#endif // LEXER_H_
