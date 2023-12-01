/* Header file for hash_table.c
 * Source: https://benhoyt.com/writings/hash-table-in-c/
 */
#include <stdio.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 16
#define RESIZE_DIVISOR 2


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Open addressing hash table that deals with collision handling via linear
 * probing and leverages the hashing algorithm FNV-1a.
 *
 * Attributes:
 *     items:  Pointer to an array of HashTableItems, each containing
 *     a key/value pair to store.
 *     capacity:  The integer representation of the current capacity of the
 *     data structure.
 *     length:  The integer representation of the current length of the data
 *     structure.
 */
struct HashTable {
    struct HashTableItem *items;
    size_t capacity;
    size_t length;
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Representation of an item, containing a key and a value, of the hash table.
 *
 * Attributes:
 *     items:  Pointer to an array of HashTableItems, each containing
 *     a key/value pair to store.
 *     capacity:  The integer representation of the current capacity of the
 *     data structure.
 *     length:  The integer representation of the current length of the data
 *     structure.
 */
struct HashTableItem {
    const char *key;
    void *value;
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Usable for iteration throughout the hash table, keeping track of the current
 * item's key/value as well as the current index.
 *
 * Attributes:
 *     key:  Pointer to the first element of the current key.
 *     value:  Pointer to the value.
 *     _table:  Private; pointer to the hash table being iterated upon.
 *     _index:  Private; iterator's current index.
 */
struct HashTableIterator {
    const char *key;
    void *value;
    struct HashTable *_table; // private
    size_t _index; // private
};


// Functions
struct HashTable *create_hash_table(void);
void delete_hash_table(struct HashTable *);
const char *set_in_hash_table(struct HashTable *table, const char *key, void *value);
void *get_from_hash_table(struct HashTable *table, const char* key);
size_t hash_table_length(struct HashTable *table);
struct HashTableIterator create_hash_table_iterator(struct HashTable *table);
bool get_next_hash_table_item(struct HashTableIterator *iterator);
