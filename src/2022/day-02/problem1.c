// Advent of Code 2022
// Day 2 - Problem 1
//
// Notes:
// There were 9 possible move combinations with point values from 1-9, so the
// array indexes are used with the points offset to determine move scores.
// Linear search was used to find matches against the moves array.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"

int main(int argc, char **argv)
{
    File *file = read_file(argc > 1 ? fopen(argv[1], "r") : stdin);
    const int POINTS_INDEX_OFFSET = 1,
              POSSIBLE_MOVES = 9;
    const char* moves[] = { "B X", "C Y", "A Z", "A X", "B Y", "C Z", "C X",
                            "A Y", "B Z" };
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
