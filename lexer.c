/**
 * Author: Bobby Rust
 * Date: Spring 2024
 *
 * Description:
 *      This is my first attempt at creating a lexer. This lexer is for a small
 *      subset of the C programming language. This is purely a pedagogical
 *      exercise which I hope to continue to complete a full (small) compiler.
 */

#include <assert.h>
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

void append_token(TokenArray *arr, const Token *token) {
    if (arr->length >= arr->capacity) {
        resize_token_array(arr);
    }

    arr->elements[arr->length++] = (Token *)token;
}

void resize_token_array(TokenArray *arr) {
    size_t new_cap = arr->capacity * GROWTH_FACTOR;
    Token **new_elements = malloc(sizeof(Token *) * new_cap);

    if (arr->length > 0) {
        // copy tokens from old to new
        for (size_t i = 0; i < arr->length; ++i) {
            // No need to create new tokens, just reuse
            new_elements[i] = arr->elements[i];
        }
    }

    free(arr->elements);
    arr->elements = new_elements;
}

void free_token_array(TokenArray *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        free_token(arr->elements[i]);
    }

    free(arr);
}

void free_token(Token *token) {
    free(token->lexeme);
    free_literal(token->literal);
}

void print_token(const Token *token) {
    printf("%s %s\n", token_type_string[token->type], token->lexeme->chars);
}

void print_token_array(const TokenArray *arr) {
    for (size_t i = 0; i < arr->length; ++i) {
        print_token(arr->elements[i]);
    }
}

int main(int argc, char **argv) {
    if (argc == 1)
        run_prompt();

    size_t length = 0;
    size_t line = 1;
    size_t num_tokens = 0;
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("File cannot be opened.\n");
        exit(1);
    }

    FileInfo *f_info = read_file_contents(fp);

    TokenArray *token_array = lex(f_info->contents, &line);

    print_token_array(token_array);

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
TokenArray *lex(String *buffer, size_t *line) {
    TokenArray *tokens = init_token_array();
    char *cur = malloc(sizeof(char) * 2);
    cur[1] = '\0';

    // do stuff
    for (int i = 0; i < buffer->length; ++i) {
        cur[0] = next(buffer);

        if (cur[0] == EOF)
            break;

        String *str = init_str();
        append_char_array(str, cur);

        switch (cur[0]) {
        case '\n':
            line++;
            continue;
        case ' ':
            ignore_whitespace(buffer);
            break;
        case '(':
            append_token(tokens, create_token(LEFT_PAREN, str, *line, NULL));
            break;
        }

        advance(buffer);
    }

    free(cur);
    return tokens;
}

char next(String *buffer) {
    if (buffer->current_pos >= buffer->length)
        return EOF;

    return buffer->chars[buffer->current_pos];
}

void ignore_whitespace(String *buffer) {
    while (next(buffer) == ' ') {
        advance(buffer);
    }
}

void advance(String *buffer) { buffer->current_pos++; }

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
    t->literal = init_literal();
    t->line = -1;
    t->type = -1;

    return t;
}

Literal *init_literal() {
    Literal *l = malloc(sizeof(Literal));
    if (l == NULL) {
        perror("Unable to allocate memory for literal.\n");
        exit(1);
    }

    l->data = NULL;
    l->type = -1;

    return l;
}

Literal *create_literal(LiteralType type, void *data) {
    Literal *l = init_literal();
    l->type = type;
    l->data = data;

    return l;
}

void free_literal(Literal *literal) {
    if ((literal->type == STRING || literal->type == IDENTIFIER) &&
        literal->data != NULL) {
        free(literal->data);
        literal->data = NULL;
    }

    free(literal);
    literal = NULL;
    assert(literal == NULL);
}

Token *create_token(TokenType type, String *lexeme, size_t line,
                    Literal *literal) {
    Token *token = init_token();

    token->type = type;
    token->lexeme = lexeme;
    token->line = line;

    token->literal = literal;

    return token;
}
