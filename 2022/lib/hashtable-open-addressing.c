#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*) (0xFFFFFFFFFFFFFFFFUL)


typedef struct {
    char name[MAX_NAME];
    int age;
} person;

person *hash_table[TABLE_SIZE];

size_t strnlen(const char *str, size_t max) {
    const char *end = memchr(str, 0, max);
    return end ? (size_t) (end - str) : max;
}

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}


void print_table() {
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else if (hash_table[i] == DELETED_NODE) {
            printf("\t%i\t---<deleted>\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("End\n");
}


bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL ||
            hash_table[try] == DELETED_NODE) {
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

person *hash_table_lookup(char *name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) {
            return false; // not here
        }
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
                return hash_table[try];
        }
    }
    return NULL;
}

person *hash_table_delete(char *name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i)  % TABLE_SIZE;
        if (hash_table[try] == NULL) {
            return false; // not here
        }
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[index]->name, name, TABLE_SIZE)==0) {
            person *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    } 
    return NULL;
}

int main() {

    init_hash_table();
    print_table();

    person jake = {.name="Jake", .age=33};
    person mack = {.name="Mack", .age=28};
    person owen = {.name="Owen", .age=1};

    hash_table_insert(&jake);
    hash_table_insert(&mack);
    hash_table_insert(&owen);

    print_table();

    person *tmp = hash_table_lookup("Jake");
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s\n", tmp->name);
    }

    tmp = hash_table_lookup("Chris");
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s\n", tmp->name);
    }

    hash_table_delete("Jake");
    tmp = hash_table_lookup("Jake");
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s\n", tmp->name);
    }

    print_table();

    /*printf("Jake => %u\n", hash("Jake"));*/
    /*printf("Mackenzie => %u\n", hash("Mackenzie"));*/
    /*printf("Owen => %u\n", hash("Owen"));*/
    /*printf("Jared => %u\n", hash("Jared"));*/
    /*printf("Ryan => %u\n", hash("Ryan"));*/
    /*printf("Anne => %u\n", hash("Anne"));*/
    /*printf("James => %u\n", hash("James"));*/
    return 0;
}
