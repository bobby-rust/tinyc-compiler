#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

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
        case 'a':

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

void createToken(Token *token, TokenType type, char lexeme[MAX_LEXEME_LENGTH], char *stringLiteral, char *identifierLiteral, int integerLiteral, int line)
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
        printf("%s %s %d", tokenTypeString[tokens[i].type], tokens[i].lexeme, tokens[i].line);
        if (tokens[i].stringLiteral != NULL)
            printf("%s\n", tokens[i].stringLiteral);
        else if (tokens[i].identifierLiteral != NULL)
            printf("%s\n", tokens[i].identifierLiteral);
        else if (tokens[i].integerLiteral != NULL)
            printf("%s\n", tokens[i].integerLiteral);
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