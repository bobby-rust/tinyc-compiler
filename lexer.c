#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc == 1)
        runPrompt();

    char *contents = NULL;
    int length = 0;
    int line = 1;

    FILE *fptr = fopen("test.txt", "r");

    if (fptr == NULL) {
        printf("File cannot be opened.\n");
        exit(1);
    }

    readFileContents(fptr, contents, &length);
    Token *tokens = lex(contents, &line);

    fclose(fptr);

    printTokens();
    freeTokens(tokens);

    return 0;
}

void run(char *buffer) { lex(buffer); }

void runPrompt() {
    while (1) {
        char *expr = getNextExprFromInput();

        if (expr == NULL) {
            free(expr);
            exit(0);
        }

        // do something with expr (run it)
        run(expr);

        free(expr);
    }
}

char *getNextExprFromInput() {
    size_t size = 0;
    ssize_t chars_read;

    char *input = NULL;
    printf("> ");
    chars_read = getline(&input, &size, stdin);

    // check for errors
    if (chars_read < 0) {
        puts("couldn't read the input");
        return NULL;
    }

    if (strcmp(input, "exit") == 0) {
        return NULL;
    }

    input[chars_read - 1] = '\0'; // get rid of the newline

    return input;
}

/**
 * performs lexical analysis on a buffer and returns an array of tokens
 * records the line of each token's occurrence and the number of total tokens
 */
Token *lex(char *buffer, int *line, int *numTokens) {
    int length = sizeof(buffer);
    Token *tokens = malloc(sizeof(Token) * MAX_NUM_TOKENS);
    char ch;

    for (int i = 0; i < length; ++i) {
        ch = buffer[i];
        char *lexeme = initStr(ch);

        if (isalpha(ch)) {
            char *id = initStr(ch);
            createToken(IDENTIFIER, lexeme, *line, -1, id, NULL);
            continue;
        }

        if (isdigit(ch)) {
            char *digit = initStr(ch);
            createToken(INTEGER, lexeme, *line, atoi(lexeme), NULL, NULL);
            continue;
        }

        switch (ch) {
        case '\n':
            line++;
            break;
        case '+':
            createToken(PLUS, lexeme, *line, -1, NULL, NULL);
            break;
        case '-':
            createToken(MINUS, lexeme, *line, -1, NULL, NULL);
            break;
        case ' ':
            continue;
        case '(':
            createToken(LEFT_PAREN, lexeme, *line, -1, NULL, NULL);
            break;
        case ')':
            createToken(RIGHT_PAREN, lexeme, *line, -1, NULL, NULL);
            break;
        case '{':
            createToken(LEFT_BRACE, lexeme, *line, -1, NULL, NULL);
            break;
        case '}':
            createToken(RIGHT_BRACE, lexeme, *line, -1, NULL, NULL);
            break;
        case '=':
            createToken(EQUAL, lexeme, *line, -1, NULL, NULL);
            break;
        case ';':
            createToken(SEMICOLON, lexeme, *line, -1, NULL, NULL);
            break;
        case '<':
            createToken(LESS, lexeme, *line, -1, NULL, NULL);
            break;
        case '>':
            createToken(GREATER, lexeme, *line, -1, NULL, NULL);
            break;
        case '"':
            createToken(DOUBLE_QUOTE, lexeme, *line, -1, NULL, NULL);
            break;
        case '\'':
            createToken(QUOTE, lexeme, *line, -1, NULL, NULL);
            break;
        default:
            printf("Unexpected character: %c\n", ch);
            break;
        }
    }

    createToken(END, NULL, *line, -1, NULL, NULL);

    return tokens;
}

char *initStr(char ch) {
    char *s = malloc(sizeof(char) * 2);
    if (s == NULL) {
        fprintf(stderr, "Unable to allocate memory for lexeme.\n");
        exit(1);
    }
    s[0] = ch;
    s[1] = '\0';
    return s;
}

void printFileContents(char *contents) {
    int length = sizeof(contents);

    for (int i = 0; i < length; i++) {
        printf("%c", contents[i]);
    }
    printf("\n");
}

void readFileContents(FILE *fptr, char *buffer, int *length) {
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        buffer[*length++] = ch;
    }
}

void addToken(Token *token, int *num_tokens) {
    if (*num_tokens >= MAX_NUM_TOKENS)
        return;

    tokens[*num_tokens++] = token;
}

Token *createToken(TokenType type, char *lexeme, int line, int integer,
                   char *identifier, char *string) {

    Token *token = malloc(sizeof(Token));
    if (token == NULL) {
        fprintf(stderr, "Unable to allocate memory for token.\n");
        exit(1);
    }

    token->type = type;
    token->lexeme = lexeme;
    token->literal.identifier = NULL;
    token->literal.integer = -1;
    token->literal.string = NULL;

    switch (type) {
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
    return token;
}

void printTokens(Token *tokens) {
    int n = sizeof(tokens);
    for (int i = 0; i < n; ++i) {
        printf("%s %s", tokenTypeString[tokens[i]->type], tokens[i]->lexeme);

        switch (tokens[i]->type) {
        case INTEGER:
            printf(" %d", tokens[i]->literal.integer);
            break;
        case STRING:
            printf(" %s", tokens[i]->literal.string);
            break;
        case IDENTIFIER:
            printf(" %s", tokens[i]->literal.identifier);
            break;
        }
        printf("\n");
    }
}

void freeTokens(Token *tokens) {
    int n = sizeof(tokens);
    for (int i = 0; i < n; ++i) {
        if (tokens[i] != NULL) {
            // printf("lexeme: %p\nid: %p\nstring: %p\ntoken: %p\n",
            // tokens[i]->lexeme, tokens[i]->literal.identifier,
            // tokens[i]->literal.string, tokens[i]);
            free(tokens[i]->lexeme);
            free(tokens[i]->literal.identifier);
            free(tokens[i]->literal.string);
            free(tokens[i]);
        }
    }

    free(tokens);
}
