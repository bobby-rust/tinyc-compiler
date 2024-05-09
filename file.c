#include <stdio.h>

#include "file.h"

FileInfo *init_file_info() {
    String *contents = init_str();
    FileInfo *f = malloc(sizeof(FileInfo));
    f->contents = contents;
    f->lines = 0;

    return f;
}

void print_file_contents(FileInfo *f) { print_str(f->contents); }

FileInfo *read_file_contents(FILE *fp) {
    FileInfo *f = init_file_info();

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            f->lines++;

        append_char(f->contents, ch);
    }

    return f;
}

// int main(void) { return 0; }
