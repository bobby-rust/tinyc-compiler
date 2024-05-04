#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Token *tokens[MAX_NUM_TOKENS];
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
    printf("lexing\n");
    lex();

    fclose(fptr);

    printf("printing tokens\n");
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
        char *lexeme = initLexeme(ch);

        if (isalpha(ch))
        {
            char *id = initIdentifier(ch);
            createToken(IDENTIFIER, lexeme, line, -1, id, NULL);
            continue;
        }

        switch (ch)
        {
        case '+':
            createToken(PLUS, lexeme, line, -1, NULL, NULL);
            break;
        case '-':
            createToken(MINUS, lexeme, line, -1, NULL, NULL);
            break;
        default:
            printf("Unexpected character: %c\n", ch);
            break;
        }
    }
}

char *initLexeme(char ch)
{

    char *l = malloc(sizeof(char) * 2);
    if (l == NULL)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }
    l[0] = ch;
    l[1] = '\0';
    return l;
}

char *initIdentifier(char ch)
{
    char *id = malloc(sizeof(char) * 2);
    if (id == NULL)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }
    id[0] = ch;
    id[1] = '\0';
    return id;
}

void readFileContents(FILE *fptr)
{
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        contents[length] = ch;
        length++;
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
    if (token == NULL || lexeme == NULL)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }

    token->type = type;
    token->lexeme = lexeme;

    switch (type)
    {
    case IDENTIFIER:
        token->type = IDENTIFIER;
        token->literal.identifier = identifier;
        break;
    case INTEGER:
        token->literal.integer = integer;

    case STRING:
        token->type = STRING;
        token->literal.string = string;
        // ... etc

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
            printf("int: %d", tokens[i]->literal.integer);
            break;
        case STRING:
            printf("string: %s", tokens[i]->literal.string);
            break;
        case IDENTIFIER:
            printf("id: %s", tokens[i]->literal.identifier);
            break;
        }
        printf("\n");
    }
}

void freeTokens()
{
    for (int i = 0; i < num_tokens; ++i)
    {
        free(tokens[i]->lexeme);
        free(tokens[i]->literal.identifier);
        free(tokens[i]->literal.string);
        free(tokens[i]);
    }
}