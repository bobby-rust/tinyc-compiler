#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_FILE_LENGTH 100
#define MAX_LEXEME_LENGTH 20
#define MAX_LITERAL_LENGTH 20

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

typedef struct
{
    TokenType type;
    char lexeme[MAX_LEXEME_LENGTH];
    int line;
    char *literal;
} Token;

void readFileContents(FILE *fptr);
void addToken(Token token);
void createToken(Token token, TokenType type, char *lexeme, char *literal, int line);
void printTokens();
void setLiteral(Token token, char literal[MAX_LITERAL_LENGTH]);
void freeTokenLiterals();

Token tokens[MAX_FILE_LENGTH];
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
            Token token;
            TokenType type = PLUS;
            createToken(token, type, &ch, NULL, line);
            addToken(token);
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
    freeTokenLiterals();
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
    if (length > MAX_FILE_LENGTH - 1)
        return;

    tokens[num_tokens++] = token;
}

void createToken(Token token, TokenType type, char *lexeme, char *literal, int line)
{
    token.type = type;
    strcpy(lexeme, token.lexeme);

    if (literal != NULL)
        strcpy(literal, token.literal);
    else
        token.literal = NULL;

    token.line = line;
}

void printTokens()
{
    for (int i = 0; i < num_tokens; ++i)
    {
        printf("%s %s %s", tokens[i].lexeme, tokens[i].type);
        if (tokens[i].literal != NULL)
            printf("%s\n", tokens[i].literal);
        else
            printf("NULL\n");
    }
}

void setLiteral(Token token, char literal[MAX_LITERAL_LENGTH])
{
    char *l = malloc(sizeof(literal));
    for (int i = 0; i < sizeof(literal); ++i)
    {
        l[i] = literal[i];
    }

    token.literal = l;
}

void freeTokenLiterals()
{
    for (int i = 0; i < sizeof(tokens); ++i)
    {
        free(tokens[i].literal);
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