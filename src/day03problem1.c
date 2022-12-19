// Advent of Code 2022
// Day 3 - Problem 1
//
#include "read_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_UPPERCASE_OFFSET 65
#define ASCII_LOWERCASE_OFFSET 97


int main(int argc, char** argv)
{
    struct File *file = read_file(argc > 1 ? fopen(argv[1], "r") : stdin);
    char *shared = malloc(sizeof(char *) * file->used);

    for (size_t i = 0; i < file->used; i++) {
        printf("%s\n\n", file->lines[i]);
        int found_upper[26] = {0},
            found_lower[26] = {0},
            len = strcspn(file->lines[i], "\n");

        for (size_t c = 0; c < len / 2; c++) {
            printf("\nchar: %c\n", file->lines[i][c]);
            if (file->lines[i][c] >= 'a' || file->lines[i][c] <= 'z') {
                int index = c - ASCII_LOWERCASE_OFFSET;
                printf("Found %d\n", found_lower[index]);
                found_lower[index]++;
            }
            if (file->lines[i][c] >= 'A' || file->lines[i][c] <= 'Z') {
                int index = c - ASCII_UPPERCASE_OFFSET;
                printf("Found %d\n", found_upper[index]);
                found_upper[index]++;
            }
        }
        // Just printing
        for (int i = 0; i < 26; i++) {
            if (found_upper[i])
                printf("%c: %d\n", i + ASCII_UPPERCASE_OFFSET, found_upper[i]);
            if (found_lower[i])
                printf("%c: %d\n", i + ASCII_LOWERCASE_OFFSET, found_lower[i]);
        }

        for (size_t c = len / 2; c < len; c++) {
            printf("char: %c\n", file->lines[i][c]);
            /*if (file->lines[i][c] >= 'a' || file->lines[i][c] <= 'z') {*/
                /*if (found_lower[c - ASCII_LOWERCASE_OFFSET])*/
                    /*// found a char*/
            /*}*/
            /*if (file->lines[i][c] >= 'A' || file->lines[i][c] <= 'Z') {*/
                /*[>found_upper[c - ASCII_UPPERCASE_OFFSET]++;<]*/
            /*}*/
        }
        break;
    }

    // Parse shared characters into priority values
    // Sum priority values
    // print priority values

    close_file(file);
    free(shared);
    exit(EXIT_SUCCESS);
}
