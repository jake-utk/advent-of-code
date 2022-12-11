// Advent of Code 2022
// C Version
// Source: https://stackoverflow.com/a/66116048
// Day 1 - Problem 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_CHARS 1024
#define NUMBER_OF_POINTERS 2


int main(int argc, char *argv[])
{
    char   buffer[MAX_BUFFER_CHARS],
           **lines = NULL;
    size_t number_of_pointers = NUMBER_OF_POINTERS,
           used = 0;
    FILE   *file = argc > 1 ? fopen(argv[1], "r") : stdin;

    if (!file) {
        perror("file open failed\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for initial number_of_pointers
    if ((lines = malloc(number_of_pointers * sizeof *lines)) == NULL) {
        perror("malloc-lines\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX_BUFFER_CHARS, file)) {
        size_t len;
        buffer[(len = strcspn(buffer, "\n"))] = 0; // Find \n, zero it out
        if (used == number_of_pointers) {
            void *tmp = realloc(lines, (2 * number_of_pointers) * sizeof *lines);
            if (!tmp) {
                perror("realloc-lines\n");
                break;
            }
            lines = tmp;
            number_of_pointers *= 2;
            // (optionally) Zero all newly allocated memory here
        }

        if (!(lines[used] = malloc(len + 1))) {
            perror("malloc-lines[used]\n");
            break;
        }
        memcpy(lines[used], buffer, len + 1);
        used++;
    }
    // (optionally) realloc to 'used' pointers to size no. of pointers exactly here

    if (file != stdin)
        fclose(file);

    size_t highest_total = 0,
           current_total = 0;
    for (size_t i = 0; i < used; i++) {
        size_t line_value = strtol(lines[i], NULL, 10);
        if (line_value) {
            current_total += line_value;
        } else {
            if (current_total > highest_total)
                highest_total = current_total;
            current_total = 0;
        }
        // Free individual line mem
        free(lines[i]);
    }

    printf("highest total %lu\n", highest_total);

    // Free pointers mem block
    free(lines);
    exit(EXIT_SUCCESS);
}
