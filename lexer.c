#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lexer.h"

TokenArr *initTokenArr() {
    TokenArr *tokens = malloc(sizeof(TokenArr));
    tokens->length = 0;
    tokens->capacity = INITIAL_SIZE;
    tokens->elements = malloc(sizeof(Token) * INITIAL_SIZE);

    return tokens;
}

void appendToken(TokenArr *arr, Token *token) {
    if (arr->length >= arr->capacity) {
        resizeTokenArr(arr);
    }

    arr->elements[arr->length++] = token;
}

void resizeTokenArr(TokenArr *arr) {
    TokenArr *newTokens = malloc(sizeof(TokenArr));

    size_t newCap = arr->capacity * GROWTH_FACTOR;
    Token **newElements = malloc(sizeof(Token *) * newCap);

    if (arr->length > 0) {
        // copy tokens from old to new
        for (size_t i = 0; i < arr->length; ++i) {
            // No need to create new tokens, just reuse
            newTokens->elements[i] = arr->elements[i];
        }
    }

    free(arr->elements);
    arr->elements = newElements;
}

void freeTokenArr(TokenArr *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        freeToken(arr->elements[i]);
    }

    free(arr);
}

void freeToken(Token *token) {
    free(token->lexeme);
    free(token->Literal.string);
    free(token->Literal.identifier);
}

int main(int argc, char **argv) {
    if (argc == 1)
        runPrompt();

    int length = 0;
    int line = 1;
    int numTokens = 0;
    FILE *fptr = fopen("test.txt", "r");

    if (fptr == NULL) {
        printf("File cannot be opened.\n");
        exit(1);
    }

    FileInfo *fileInfo = readFileContents(fptr);

    fclose(fptr);

    return 0;
}

void runPrompt() {
    while (1) {
        return;
    }
}

/**
 * Takes a stream of characters, returns a stream of tokens
 */
TokenArr *lex(String *buffer) {
    TokenArr *tokens = initTokenArr();

    // do stuff

    return tokens;
}

/**
 * Initializes a Token.
 * The responsibility of calling `free` is on the caller.
 * Token.lexeme will be malloced and must also be freed by caller using
 * `freeStr` or if part of an TokenArr, `freeTokenArr`. Other optional fields
 * are initialized to NULL for String types and -1 for integers.
 */
Token *initToken() {
    Token *t = malloc(sizeof(Token));
    t->lexeme = initStr();
    t->Literal.string = NULL;
    t->Literal.identifier = NULL;
    t->line = -1;
    t->type = -1;

    return t;
}
