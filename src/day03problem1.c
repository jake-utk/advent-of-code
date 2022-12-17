// Advent of Code 2022
// Day 3 - Problem 1
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"
#include "hash_table.h"

// Lower and uppercase letters are different elements
// Each line contains single even set of elements
// first half of elements are subset 1
// second half of elements are subset 2

int main(int argc, char** argv)
{
    struct File *file = read_file(argc > 1 ? fopen(argv[1], "r") : stdin);
    struct HashTable *table = create_hash_table();

    // hash table
    // for each char in first half of line, create key in table and a count
    // for each char in second half of line, check table for existing key
    
    for (size_t i = 0; i < file->used; i++) {
        printf("%s\n", file->lines[i]);
        int len = strcspn(file->lines[i], "\n");
        printf("Length %d\n", len);


    }

    delete_hash_table(table);
    close_file(file);
    exit(EXIT_SUCCESS);
}
