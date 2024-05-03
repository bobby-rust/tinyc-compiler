#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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

typedef union
{
    char token[MAX_TOKEN_LENGTH]; // holds the string representation of the enum fields
} TokenData;

typedef struct
{
    TokenType type;
    TokenData data;
    char lexeme[MAX_LEXEME_LENGTH]; // holds the lexeme as it appears in the source code
    int line;
    char stringLiteral[MAX_LITERAL_LENGTH];
    char identifierLiteral[MAX_LITERAL_LENGTH];
    int integerLiteral;
} Token;

void readFileContents(FILE *fptr);
void addToken(Token token);
void createToken(Token *token, TokenType type, const char lexeme[MAX_LEXEME_LENGTH], const char stringLiteral[MAX_LITERAL_LENGTH], const char identifierLiteral[MAX_LITERAL_LENGTH], int integerLiteral, int line);
void setLiteral(Token *token, const char literal[MAX_LITERAL_LENGTH]);
void freeTokens();
void printTokens();

Token tokens[MAX_NUM_TOKENS];
char contents[MAX_FILE_LENGTH];
int length = 0;
int num_tokens = 0;
int line = 0;

int main()
{
    FILE *fptr = fopen("test.txt", "r");

    if (fptr == NULL)
    {
        printf("File cannot be opened.\n");
        exit(1);
    }

    readFileContents(fptr);

    char ch;
    for (int i = 0; i < length; ++i)
    {
        ch = contents[i];
        switch (ch)
        {
        case '+':
            Token *token = (Token *)malloc(sizeof(Token));
            TokenType type = PLUS;
            createToken(token, type, &ch, NULL, NULL, -1, line);
            addToken(*token);
            break;
        case 'i':

        default:
            printf("Unexpected character: %c\n", ch);
            break;
        }
        length++;
    }

    fclose(fptr);

    printTokens();
    freeTokens();
    return 0;
}

void readFileContents(FILE *fptr)
{
    char ch;
    for (int i = 0; ((i < MAX_FILE_LENGTH) && (!feof(fptr))); ++i)
    {
        ch = fgetc(fptr);
        contents[i] = ch;
        length++;
    }
}

void addToken(Token token)
{
    if (num_tokens >= MAX_NUM_TOKENS)
        return;

    tokens[num_tokens++] = token;
}

void createToken(Token *token, TokenType type, const char lexeme[MAX_LEXEME_LENGTH], const char stringLiteral[MAX_LITERAL_LENGTH], const char identifierLiteral[MAX_LITERAL_LENGTH], int integerLiteral, int line)
{
    token->type = type;
    strcpy(lexeme, token->lexeme);

    switch (type)
    {
    case IDENTIFIER:
        strncpy(token->identifierLiteral, identifierLiteral, MAX_LITERAL_LENGTH);
    case INTEGER:
        token->integerLiteral = integerLiteral;
    // ... etc
    default:
        break;
    }

    token->line = line;
}

void printTokens()
{
    for (int i = 0; i < num_tokens; ++i)
    {
        printf("%s %s %s", tokens[i].lexeme, tokens[i].type);
        if (tokens[i].stringLiteral != NULL)
            printf("%s\n", tokens[i].stringLiteral);
        else
            printf("NULL\n");
    }
}

void freeTokens()
{
    for (int i = 0; i < sizeof(tokens); ++i)
    {
        free(&tokens[i]);
    }
}

char *typeToString(TokenType type)
{
    switch (type)
    {
    case LEFT_PAREN:
        return "left_paren";
    case RIGHT_PAREN:
        return "right_paren";
    case LEFT_BRACE:
        return "left_brace";
    case RIGHT_BRACE:
        return "right_brace";
    case SEMICOLON:
        return "semicolon";
    case LESS:
        return "less";
    case PLUS:
        return "plus";
    case MINUS:
        return "minus";
    case EQUALS:
        return "equals";
    case IDENTIFIER:
        return "identifier";
    case STRING:
        return "string";
    case INTEGER:
        return "integer";
    case NIL:
        return "nil";
    case IF:
        return "if";
    case ELSE:
        return "else";
    case DO:
        return "do";
    case WHILE:
        return "while";
    case END:
        return "eof"; // eof - not sure if needed?
    default:
        return "unknown type";
    }
}