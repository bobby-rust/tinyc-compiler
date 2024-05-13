#include <stdio.h>

#include "file.h"

FileInfo *init_file_info() {
    String *contents = init_str();
    FileInfo *f = malloc(sizeof(FileInfo));
    f->contents = contents;
    f->lines = 0;
    f->current_pos = 0;

    return f;
}

void print_file_contents(FileInfo *f) { print_str(f->contents); }

FileInfo *read_file_contents(FILE *fp) {
    FileInfo *f = init_file_info();

    // holds a single character and a null terminator
    char *ch = malloc(sizeof(char) * 2);
    ch[0] = fgetc(fp);
    ch[1] = '\0';

    while (ch[0] != EOF) {
        if (ch[0] == '\n') {
            /**
             * Don't add the last newline as it's superficial
             */
            ch[0] = fgetc(fp); // peek next char
            if (ch[0] == EOF)
                break;

            f->lines++;
        }

        append_char_array(f->contents, ch);
        ch[0] = fgetc(fp);
    }

    free(ch);

    return f;
}

// int main(void) { return 0; }
