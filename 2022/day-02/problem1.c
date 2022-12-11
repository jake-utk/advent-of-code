// Advent of Code 2022
// Day 2 - Problem 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 1024
#define NUM_PTRS 2


int main(int argc, char **argv)
{
    char   buffer[MAX_CHARS] = {0},
           **lines = NULL;
    size_t num_ptrs = NUM_PTRS,
           used = 0;
    FILE   *file = argc > 1 ? fopen(argv[1], "r") : stdin;

    if (!file) {
        perror("file open failed\n");
        exit(EXIT_FAILURE);
    }

    if ((lines = malloc(num_ptrs * sizeof(*lines))) == NULL) {
        perror("malloc-lines");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX_CHARS, file)) {
        size_t len;
        buffer[(len = strcspn(buffer, "\n"))] = 0;
        if (used == num_ptrs) {
            void *temp = realloc(lines, (2 * num_ptrs) * sizeof(*lines));
            if (!temp) {
                perror("realloc-lines");
                break;
            }
            lines = temp;
            num_ptrs *= 2;
        }

        if (!(lines[used] = malloc(len + 1))) {
            perror("malloc-lines[used]\n");
            break;
        }
        memcpy(lines[used], buffer, len + 1);
        used++;
    }

    if (file != stdin)
        fclose(file);

    // Problem 2 logic
    // First column  A - Rock, B - Paper, C - Scissors
    // Second column X - Rock, Y - Paper, Z - Scissors
    // total_score = sum of scores for each round
    // single_round_score = (1 for rock, 2 for paper, 3 for scissors) + (0
    // lost, 3 draw, 6 win)
    for (size_t i = 0; i < used; i++) {
        printf("%s\n", lines[i]);
        free(lines[i]);
    }

    free(lines);
    exit(EXIT_SUCCESS);
}
