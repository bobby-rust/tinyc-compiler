#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>

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
    char *lexeme; // holds the lexeme as it appears in the source code
    int line;

    struct {
        char *identifier;
        int integer;
        char *string;
    } literal;
} Token;

Token *lex(char *buffer, int *line, int *numTokens);
void readFileContents(FILE *fptr, char *contents);
char *getNextExprFromInput();
void run(char *buffer);
void printFileContents(char *contents);
void addToken(Token *token);
void createToken(TokenType type, char *lexeme, int line, int integer,
                 char *identifier, char *string);
void freeTokens();
void printTokens();
char *initStr(char ch);
void runPrompt();

#endif // LEXER_H_
