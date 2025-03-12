/*
    A simple hash table implementation for integer-valued entries, 
    using chaining and linear probing.
*/

#include "ht.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct entry {
    int data;
    int key;
    struct entry* next;
};

struct ht{
    struct entry** table;
    int size;
    int cap;
};

ht* ht_new(int capacity) {
    ht* H = malloc(sizeof(ht));
    H->table = calloc(capacity, sizeof(entry*));

    H->size = 0;
    H->cap = capacity;

    return H;
}

int hash(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;

    return abs(x);
}

void resize(ht* H) {
    int new_cap = 2 * H->cap;

    entry **temp = calloc(new_cap, sizeof(entry*));

    for (int i = 0; i < H->cap; i++) {
        entry *e = H->table[i];

        while (e != NULL) {
            int new_index = hash(e->key) % new_cap;
            struct entry *next = e->next;

            e->next = temp[new_index];
            temp[new_index] = e;

            e = next;
        }

    }

    free(H->table);
    H->table = temp;
    H->cap = new_cap;
}

void ht_put(ht* H, int key, int val) {
    if ((float) H->size / H->cap >= 0.7) {
        resize(H);
    }

    int index = hash(key) % H->cap;
    
    entry *e = malloc(sizeof(entry));
    e->data = val;
    e->key = key;
    e->next = H->table[index];
    H->table[index] = e;
    
    H->size++;
}

int ht_get(ht* H, int key) 
{
    assert(ht_contains(H, key));

    int index = hash(key) % H->cap;

    entry *e = H->table[index];

    while (e != NULL) {
        if (e->key == key) {
            return e->data;
        }

        e = e->next;
    }

    return -1;
}

void ht_remove(ht* H, int key) {
    int index = hash(key) % H->cap;

    entry *e = H->table[index];

    if (e == NULL) {
        return;
    }

    if (e->key == key) {
        H->table[index] = e->next;

        free(e);

        H->size--;
        
        return;
    }

    while (e->next != NULL) {
        if (e->next->key == key) {
            entry *temp = e->next;
            e->next = e->next->next;

            free(temp);

            H->size--;

            return;
        }

        e = e->next;
    }
}

bool ht_contains(ht* H, int key) {
    int index = hash(key) % H->cap;

    entry *e = H->table[index];

    while (e != NULL) {
        if (e->key == key) {
            return true;
        }

        e = e->next;
    }

    return false;
}

bool ht_empty(ht* H) {
    return H->size == 0;
}

void free_ht(ht* H) {
    for (int i = 0; i < H->cap; i++) {
        entry *e = H->table[i];

        while (e != NULL) {
            entry *next = e->next;
            
            free(e);
            e = next;
        }
    }

    free(H->table);
    free(H);
}

typedef ht* ht_t;