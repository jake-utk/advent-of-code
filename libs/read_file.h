/* Header file for read_file
 */
#include <stdio.h>

#define MAX_CHARS 1024
#define NUM_PTRS 2

typedef struct {
    FILE *stream;
    char **lines;
    int num_ptrs,
        used;
} File;

File *read_file(FILE *file_name);

void close_file(File *current_file);
