#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10


typedef struct person {
    char name[MAX_NAME];
    int age;
    struct person *next;
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
        } else {
            printf("\t%i\t", i);
            person *tmp = hash_table[i];
            while (tmp != NULL) {
                printf("%s - ", tmp->name);
                tmp = tmp -> next;
            }
        }
    }
    printf("End\n");
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

person *hash_table_lookup(char *name) {
    int index = hash(name);
    person *tmp = hash_table[index];
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
        tmp = tmp->next;
    }
    return tmp;
}

person *hash_table_delete(char *name) {
    int index = hash(name);
    person *tmp = hash_table[index];
    person *prev = NULL;
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp != NULL) return NULL;
    if (prev == NULL) {
        // deleting the head
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    return tmp;
}

int main() {

    init_hash_table();
    print_table();

    person jake = {.name="Jake", .age=33};
    person jake1 = {.name="Jake", .age=33};
    person jake2 = {.name="Jake", .age=33};
    person mack = {.name="Mack", .age=28};
    person owen = {.name="Owen", .age=1};

    hash_table_insert(&jake);
    hash_table_insert(&jake1);
    hash_table_insert(&jake2);
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

    return 0;
}
