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

static const char *tokenTypeString[] = {
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
} TokenArr;

// TokenArr
TokenArr *initTokenArr();
void appendToken(TokenArr *arr, Token *token);
void resizeTokenArr(TokenArr *arr);
void freeTokenArr(TokenArr *arr);

// lexer
TokenArr *lex(String *buffer);
void run(char *buffer);
void printFileContents(char *contents);

// Token
Token *initToken();
void runPrompt();
void freeToken(Token *token);

#endif // LEXER_H_
