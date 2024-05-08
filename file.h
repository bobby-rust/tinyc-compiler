#ifndef FILE_H_
#define FILE_H_

#include <ctype.h>
#include <stdio.h>

#include "string.h"

typedef struct {
    String *contents;
    size_t lines;
} FileInfo;

// FileInfo
FileInfo *initFileInfo();
FileInfo *readFileContents(FILE *fptr);

#endif // FILE_H_
