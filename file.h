#ifndef FILE_H_
#define FILE_H_

#include <ctype.h>
#include <stdio.h>

#include "string.h"

typedef struct {
    String *contents;
    size_t lines;
    size_t current_pos;
} FileInfo;

// FileInfo
FileInfo *init_file_info();
FileInfo *read_file_contents(FILE *fp);

#endif // FILE_H_
