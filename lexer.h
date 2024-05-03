#include <stdio.h>

#ifndef LEXER_H_
#define LEXER_H_

#define MAX_FILE_LENGTH 100
#define MAX_NUM_TOKENS MAX_FILE_LENGTH // can only have as many tokens as characters in the file
#define MAX_LEXEME_LENGTH 20
#define MAX_LITERAL_LENGTH 20
#define MAX_TOKEN_LENGTH 100

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
    char lexeme[MAX_LEXEME_LENGTH]; // holds the lexeme as it appears in the source code, will always have a lexeme so no dynamic memory allocation needed
    int line;
    char *stringLiteral;
    char *identifierLiteral;
    int integerLiteral;
} Token;

void readFileContents(FILE *fptr);
void addToken(Token token);
void createToken(Token *token, TokenType type, char lexeme[MAX_LEXEME_LENGTH], char *stringLiteral, char *identifierLiteral, int integerLiteral, int line);
void setLiteral(Token *token, const char literal[MAX_LITERAL_LENGTH]);
void freeTokens();
void printTokens();

#endif // LEXER_H_