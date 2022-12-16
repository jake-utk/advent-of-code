#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"

File *create_file(FILE *file_name) {
    File *file = (File *) malloc(sizeof(File));
    file->stream = file_name;
    file->lines = NULL;
    file->num_ptrs = NUM_PTRS;
    file->used = 0;
    return file;
}

File *read_file(FILE *file_name)
{
    if (!file_name) {
        perror("file open failed\n");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_CHARS];
    File *file = create_file(file_name);

    if ((file->lines = malloc(file->num_ptrs * sizeof(*(file->lines)))) == NULL) {
        perror("malloc-lines");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX_CHARS, file->stream)) {
        size_t len;
        buffer[(len = strcspn(buffer, "\n"))] = 0;
        if (file->used == file->num_ptrs) {
            void *temp = realloc(file->lines, (2 * file->num_ptrs) * sizeof(*file->lines));
            if (!temp) {
                perror("realloc-lines");
                break;
            }
            file->lines = temp;
            file->num_ptrs *= 2;
        }

        if (!(file->lines[file->used] = malloc(len + 1))) {
            perror("malloc-lines[used]\n");
            break;
        }
        memcpy(file->lines[file->used], buffer, len + 1);
        file->used++;
    }

    return file;
}

void close_file(File *file) {
    // Free individual strings
    for (size_t i = 0; i < file->used; i++)
        free(file->lines[i]);

    // Free array of strings
    if (file->lines)
        free(file->lines);

    // Close file stream
    if (file->stream != stdin)
        fclose(file->stream);
    
    // Free struct
    if (file)
        free(file);
}
