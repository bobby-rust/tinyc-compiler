#include <stdio.h>

#ifndef LEXER_H_
#define LEXER_H_

#define MAX_FILE_LENGTH 100
#define MAX_NUM_TOKENS MAX_FILE_LENGTH // can only have as many tokens as characters in the file

typedef enum
{
    // single-character tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    LESS,
    PLUS,
    MINUS,
    EQUAL,

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

static const char *tokenTypeString[] = {"left_paren", "right_paren", "left_brace", "right_brace", "semicolon", "less", "plus", "minus", "equals", "identifier", "string", "integer", "nil", "if", "else", "do", "while", "end"};

typedef struct
{
    TokenType type;
    char *lexeme; // holds the lexeme as it appears in the source code
    int line;

    struct
    {
        char *identifier;
        int integer;
        char *string;
    } literal;
} Token;

void lex();
void readFileContents(FILE *fptr);
void printFileContents();
void addToken(Token *token);
void createToken(TokenType type, char *lexeme, int line, int integer, char *identifier, char *string);
void setLiteral(char *literal);
void freeTokens();
void printTokens();
char *initStr(char ch);

#endif // LEXER_H_