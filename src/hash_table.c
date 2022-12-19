#include "hash_table.h"
#include "strlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


struct HashTable *create_hash_table(void)
{
    struct HashTable *table = malloc(sizeof(struct HashTable));
    if (table == NULL) {
        perror("malloc-table");
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    if ((table->items = calloc(table->capacity, sizeof(struct HashTableItem))) == NULL) {
        perror("calloc-items");
        free(table);
        return NULL;
    }

    return table;
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function

static uint64_t hash_key(const char* key)
{
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}


void *get_from_hash_table(struct HashTable *table, const char* key)
{
    uint64_t hash = hash_key(key);
    size_t index = (size_t) hash & (uint64_t)(table->capacity - 1);

    // Iterate until empty array is found
    while (table->items[index].key != NULL) {
        if (strcmp(key, table->items[index].key) == 0) {
            // Key located, value returned
            return table->items[index].value;
        }
        // Linear probling:  Key not here; move to next
        index++;
        if (index >= table->capacity) {
            // At end of items array, wrap around
            index = 0;
        }
    }
    return NULL;
}


void delete_hash_table(struct HashTable *table)
{
    // Free allocated keys
    for (size_t i = 0; i < table->capacity; i++)
        free((void*) table->items[i].key);

    // Free array of items
    if (table->items)
        free(table->items);

    // Free struct
    if (table)
        free(table);
}


static const char *update_hash_table(struct HashTableItem *items,
                                     size_t capacity,
                                     const char *key,
                                     void *value,
                                     size_t *table_length)
{
    uint64_t hash = hash_key(key);
    size_t index = (size_t) (hash & (uint64_t) (capacity - 1));

    while (items[index].key != NULL) {
        if (strcmp(key, items[index].key) == 0) {
            // Key exists, update value
            items[index].value = value;
            return items[index].key;
        }
        // COLLISION HANDLING
        // Linear probling:  Key not here; move to next
        index++;
        if (index >= capacity) {
            // At end of items array, wrap around
            index = 0;
        }
    }

    // Key does not exist, allocate+copy if needed
    if (table_length != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*table_length)++;
    }
    items[index].key = (char *) key;
    items[index].value = value;

    return key;
}


static bool resize_hash_table(struct HashTable *table)
{
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) return false; // Overflow, capacity too big

    struct HashTableItem *new_items = calloc(new_capacity, sizeof(struct HashTableItem));
    if (new_items == NULL) return false;

    for (size_t i = 0; i < table->capacity; i++) {
        struct HashTableItem item = table->items[i];
        if (item.key != NULL) {
            update_hash_table(new_items,
                              new_capacity,
                              item.key,
                              item.value,
                              NULL);
        }
    }

    // Free old items array; update table details
    free(table->items);
    table->items = new_items;
    table->capacity = new_capacity;

    return true;
}


const char *set_in_hash_table(struct HashTable *table, const char *key, void *value)
{
    if (value == NULL) return NULL;

    // If table length exceeds capacity limit, resize
    if (table->length >= table->capacity / RESIZE_DIVISOR) {
        if (!resize_hash_table(table)) {
            return NULL;
        }
    }

    // Set item, update length
    return update_hash_table(table->items,
                             table->capacity,
                             key,
                             value,
                             &table->length);
}


size_t hash_table_length(struct HashTable *table)
{
    return table->length;
}


struct HashTableIterator create_hash_table_iterator(struct HashTable *table)
{
    struct HashTableIterator iterator;

    iterator._table = table;
    iterator._index = 0;

    return iterator;
}


bool get_next_hash_table_item(struct HashTableIterator *iterator)
{
    struct HashTable *table = iterator->_table;

    while (iterator->_index < table->capacity) {
        size_t i = iterator->_index;
        iterator->_index++;
        if (table->items[i].key != NULL) {
            // Found next non-empty item
            struct HashTableItem item = table->items[i];
            iterator->key = item.key;
            iterator->value = item.value;
            return true;
        }
    }
    return false;
}
