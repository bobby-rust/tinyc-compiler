#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lexer.h"

TokenArray *init_token_array() {
    TokenArray *tokens = malloc(sizeof(TokenArray));
    tokens->length = 0;
    tokens->capacity = INITIAL_SIZE;
    tokens->elements = malloc(sizeof(Token) * INITIAL_SIZE);

    return tokens;
}

void append_token(TokenArray *arr, Token *token) {
    if (arr->length >= arr->capacity) {
        resize_token_array(arr);
    }

    arr->elements[arr->length++] = token;
}

void resize_token_array(TokenArray *arr) {
    TokenArray *new_tokens = malloc(sizeof(TokenArray));

    size_t new_cap = arr->capacity * GROWTH_FACTOR;
    Token **new_elements = malloc(sizeof(Token *) * new_cap);

    if (arr->length > 0) {
        // copy tokens from old to new
        for (size_t i = 0; i < arr->length; ++i) {
            // No need to create new tokens, just reuse
            new_tokens->elements[i] = arr->elements[i];
        }
    }

    free(arr->elements);
    arr->elements = new_elements;
}

void freeTokenArr(TokenArray *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        free_token(arr->elements[i]);
    }

    free(arr);
}

void free_token(Token *token) {
    free(token->lexeme);
    free(token->Literal.string);
    free(token->Literal.identifier);
}

int main(int argc, char **argv) {
    if (argc == 1)
        run_prompt();

    int length = 0;
    int line = 1;
    int num_tokens = 0;
    FILE *fp = fopen("test.txt", "r");

    if (fp == NULL) {
        printf("File cannot be opened.\n");
        exit(1);
    }

    FileInfo *f_info = read_file_contents(fp);

    fclose(fp);

    return 0;
}

void run_prompt() {
    while (1) {
        return;
    }
}

/**
 * Takes a stream of characters, returns a stream of tokens
 */
TokenArray *lex(String *buffer) {
    TokenArray *tokens = init_token_array();

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
Token *init_token() {
    Token *t = malloc(sizeof(Token));
    t->lexeme = init_str();
    t->Literal.string = NULL;
    t->Literal.identifier = NULL;
    t->line = -1;
    t->type = -1;

    return t;
}
