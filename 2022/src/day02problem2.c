// Advent of Code 2022
// Day 2 - Problem 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"

int main(int argc, char **argv)
{
    struct File *file = read_file(argc > 1 ? fopen(argv[1], "r") : stdin);
    const int POINTS_INDEX_OFFSET = 1,
              POSSIBLE_MOVES = 9;
    const char* moves[] = { "B X", "C X", "A X", "A Y", "B Y", "C Y", "C Z",
                            "A Z", "B Z" };
    int total_score = 0;

    for (size_t i = 0; i < file->used; i++) {
        for (size_t j = 0; j < POSSIBLE_MOVES; j++) {
            if (strcmp(file->lines[i], moves[j]) == 0) {
                total_score += j + POINTS_INDEX_OFFSET;
                break;
            }
        }
    }

    printf("Total score %d\n", total_score);

    close_file(file);
    exit(EXIT_SUCCESS);
}
