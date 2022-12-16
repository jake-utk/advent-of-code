// Advent of Code 2022
// Day 1 - Problem 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_CHARS 1024
#define NUMBER_OF_POINTERS 2
#define TOTALS_TRACKED 3

void insertion_sort(size_t *, size_t);

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

    if ((lines = malloc(number_of_pointers * sizeof *lines)) == NULL) {
        perror("malloc-lines\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX_BUFFER_CHARS, file)) {
        size_t len;
        buffer[(len = strcspn(buffer, "\n"))] = 0;
        if (used == number_of_pointers) {
            void *temp = realloc(lines, (2 * number_of_pointers) * sizeof *lines);
            if (!temp) {
                perror("realloc-lines\n");
                break;
            }
            lines = temp;
            number_of_pointers *= 2;
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

    size_t highest_totals[TOTALS_TRACKED + 1] = {0},
           current_total = 0;
    for (size_t i = 0; i < used; i++) {
        size_t line_value = strtol(lines[i], NULL, 10);
        if (line_value) {
            current_total += line_value;
        } else {
            highest_totals[0] = current_total;
            insertion_sort(highest_totals, (sizeof(highest_totals) / sizeof(highest_totals[0])));
            current_total = 0;
        }
        free(lines[i]);
    }

    size_t sum_totals = 0;
    for (int i = TOTALS_TRACKED; i > 0; sum_totals+=highest_totals[i--]);
    printf("sum of top %d highest totals: %lu\n", TOTALS_TRACKED, sum_totals);

    free(lines);
    exit(EXIT_SUCCESS);
}


void insertion_sort(size_t *arr, size_t size) {
    size_t temp;
    for (size_t i = 1; i < size; i++) {
        temp = arr[i];
        size_t j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
