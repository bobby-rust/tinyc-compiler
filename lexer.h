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
    EQUALS,

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
    char *stringLiteral;
    char *identifierLiteral;
    int integerLiteral;
} Token;

void readFileContents(FILE *fptr);
void addToken(Token *token);
void createToken(Token *token, TokenType type, char *lexeme, char *stringLiteral, char *identifierLiteral, int integerLiteral, int line);
void setLiteral(Token *token, char *literal);
void freeTokens();
void printTokens();

#endif // LEXER_H_