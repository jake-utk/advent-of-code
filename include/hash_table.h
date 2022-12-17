/* Header file for hash_table.c
 */
#include <stdio.h>

#define INITIAL_CAPACITY 16

struct HashEntry {
    char* key;
    void* value;
};

struct HashTable {
    struct HashEntry *entries;
    size_t capacity;
    size_t length;
};

struct HashTable *create_hash_table(void);

void delete_hash_table(struct HashTable *);
