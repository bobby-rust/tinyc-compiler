#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Token *tokens[MAX_NUM_TOKENS];
char contents[MAX_FILE_LENGTH];
int length = 0;
int num_tokens = 0;
int line = 1;

int main()
{
    FILE *fptr = fopen("test.txt", "r");

    if (fptr == NULL)
    {
        printf("File cannot be opened.\n");
        exit(1);
    }

    readFileContents(fptr);
    lex();

    fclose(fptr);

    printTokens();
    freeTokens();
    return 0;
}

void lex()
{
    char ch;
    for (int i = 0; i < length; ++i)
    {
        ch = contents[i];
        char *lexeme = initStr(ch);

        if (isalpha(ch))
        {
            char *id = initStr(ch);
            createToken(IDENTIFIER, lexeme, line, -1, id, NULL);
            continue;
        }

        if (isdigit(ch))
        {
            char *digit = initStr(ch);
            createToken(INTEGER, lexeme, line, atoi(lexeme), NULL, NULL);
            continue;
        }

        switch (ch)
        {
        case '\n':
            line++;
            break;
        case '+':
            createToken(PLUS, lexeme, line, -1, NULL, NULL);
            break;
        case '-':
            createToken(MINUS, lexeme, line, -1, NULL, NULL);
            break;
        case ' ':
            continue;
        case '(':
            createToken(LEFT_PAREN, lexeme, line, -1, NULL, NULL);
            break;
        case ')':
            createToken(RIGHT_PAREN, lexeme, line, -1, NULL, NULL);
            break;
        case '{':
            createToken(LEFT_BRACE, lexeme, line, -1, NULL, NULL);
            break;
        case '}':
            createToken(RIGHT_BRACE, lexeme, line, -1, NULL, NULL);
            break;
        case '=':
            createToken(EQUAL, lexeme, line, -1, NULL, NULL);
            break;
        case ';':
            createToken(SEMICOLON, lexeme, line, -1, NULL, NULL);
            break;
        default:
            printf("Unexpected character: %c\n", ch);
            break;
        }
    }

    createToken(END, NULL, line, -1, NULL, NULL);
}

char *initStr(char ch)
{

    char *s = malloc(sizeof(char) * 2);
    if (s == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for lexeme.\n");
        exit(1);
    }
    s[0] = ch;
    s[1] = '\0';
    return s;
}

void printFileContents()
{
    for (int i = 0; i < length; i++)
    {
        printf("%c", contents[i]);
    }
    printf("\n");
}

void readFileContents(FILE *fptr)
{
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        contents[length++] = ch;
    }
}

void addToken(Token *token)
{
    if (num_tokens >= MAX_NUM_TOKENS)
        return;

    tokens[num_tokens++] = token;
}

void createToken(TokenType type, char *lexeme, int line, int integer, char *identifier, char *string)
{

    Token *token = malloc(sizeof(Token));
    if (token == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for token.\n");
        exit(1);
    }

    token->type = type;
    token->lexeme = lexeme;
    token->literal.identifier = NULL;
    token->literal.integer = -1;
    token->literal.string = NULL;

    switch (type)
    {
    case IDENTIFIER:
        token->literal.identifier = identifier;
        break;
    case INTEGER:
        token->literal.integer = integer;
        break;

    case STRING:
        token->literal.string = string;
        // ... etc
        break;
    default:
        break;
    }

    token->line = line;
    addToken(token);
}

void printTokens()
{
    for (int i = 0; i < num_tokens; ++i)
    {
        printf("%s %s %d", tokenTypeString[tokens[i]->type], tokens[i]->lexeme, tokens[i]->line);

        switch (tokens[i]->type)
        {
        case INTEGER:
            printf(" int: %d", tokens[i]->literal.integer);
            break;
        case STRING:
            printf(" string: %s", tokens[i]->literal.string);
            break;
        case IDENTIFIER:
            printf(" identifier: %s", tokens[i]->literal.identifier);
            break;
        }
        printf("\n");
    }
}

void freeTokens()
{
    for (int i = 0; i < num_tokens; ++i)
    {
        if (tokens[i] != NULL)
        {
            // printf("lexeme: %p\nid: %p\nstring: %p\ntoken: %p\n", tokens[i]->lexeme, tokens[i]->literal.identifier, tokens[i]->literal.string, tokens[i]);
            free(tokens[i]->lexeme);
            free(tokens[i]->literal.identifier);
            free(tokens[i]->literal.string);
            free(tokens[i]);
        }
    }
}