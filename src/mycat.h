#ifndef MYCAT_H
#define MYCAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 128

// Structure definition (needed by both arguments.c and file_io.c)
typedef struct arguments
{
    unsigned int files_count;
    char** files;

    // flags
    int number_lines;
    int number_nonblank;
    int squeeze_blank;
    int show_ends;
} arguments;

// Function prototypes (declarations, not definitions)
void print_help(const char* program_name);
void parse_arguments(int argc, char** argv, arguments* args);
void print_file(char* path, arguments* args);

#endif
