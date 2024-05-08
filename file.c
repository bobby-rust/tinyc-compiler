#include <stdio.h>

#include "file.h"

FileInfo *initFileInfo() {
    String *contents = initStr();
    FileInfo *f = malloc(sizeof(FileInfo));
    f->contents = contents;
    f->lines = 0;

    return f;
}

void printFileContents(FileInfo *f) { printStr(f->contents); }

FileInfo *readFileContents(FILE *fptr) {
    FileInfo *f = initFileInfo();

    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n')
            f->lines++;

        appendChar(f->contents, ch);
    }

    return f;
}

// int main(void) { return 0; }
