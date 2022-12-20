// Advent of Code 2022
// Day 3 - Problem 1
//
#include "read_file.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_UPPERCASE_OFFSET 65
#define ASCII_LOWERCASE_OFFSET 97


int main(int argc, char** argv)
{
    struct File *file = read_file(argc > 1 ? fopen(argv[1], "r") : stdin);
    char *shared = calloc(sizeof(char *), file->used);

    for (size_t i = 0; i < file->used; i++) {
        int found_upper[26] = {0},
            found_lower[26] = {0},
            len = strcspn(file->lines[i], "\n");

        for (size_t ch = 0; ch < len / 2; ch++) {
            if (file->lines[i][ch] >= 'a' && file->lines[i][ch] <= 'z') {
                int index = file->lines[i][ch] - ASCII_LOWERCASE_OFFSET;
                found_lower[index]++;
            }
            if (file->lines[i][ch] >= 'A' && file->lines[i][ch] <= 'Z') {
                int index = file->lines[i][ch] - ASCII_UPPERCASE_OFFSET;
                found_upper[index]++;
            }
        }

        for (size_t ch = len / 2; ch < len; ch++) {
            if (file->lines[i][ch] >= 'a' && file->lines[i][ch] <= 'z') {
                if (found_lower[file->lines[i][ch] - ASCII_LOWERCASE_OFFSET]) {
                    shared[i] = file->lines[i][ch];
                }
            }
            if (file->lines[i][ch] >= 'A' && file->lines[i][ch] <= 'Z') {
                if (found_upper[file->lines[i][ch] - ASCII_UPPERCASE_OFFSET]) {
                    shared[i] = file->lines[i][ch];
                }
            }
        }
    }

    size_t priority_sum = 0;
    for (size_t i = 0; i < file->used; i++) {
        if (islower(shared[i])) {
            // Ensures values are 1-26
            priority_sum += (shared[i] - ASCII_LOWERCASE_OFFSET + 1);
        }
        if (isupper(shared[i])) {
            // Ensures values are 27-52
            priority_sum += (shared[i] - ASCII_UPPERCASE_OFFSET + 27);
        }
    }

    printf("Sum of priority values: %lu\n", priority_sum);

    close_file(file);
    free(shared);
    exit(EXIT_SUCCESS);
}
