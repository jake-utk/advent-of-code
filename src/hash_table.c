#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

struct HashTable *create_hash_table(void){
    struct HashTable *table = (struct HashTable *) malloc(sizeof(struct HashTable));
    if (table == NULL) {
        perror("malloc-table");
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    if ((table->entries = malloc(table->capacity * sizeof(*(table->entries)))) == NULL) {
        perror("malloc-entries");
        free(table);
        return NULL;
    }

    return table;
}

void delete_hash_table(struct HashTable *table){
    //TODO Will also need to free allocated keys

    // Free array of entries
    if (table->entries)
        free(table->entries);

    // Free struct
    if (table)
        free(table);
}
