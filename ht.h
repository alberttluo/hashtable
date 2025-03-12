#ifndef HT_H
#define HT_H

#include <stdbool.h>

typedef struct entry entry;
typedef struct ht ht;

ht* ht_new(int capacity);
void free_ht(ht* H);

void ht_put(ht* H, int key, int val);
int ht_get(ht* H, int key);
void ht_remove(ht* H, int key);
bool ht_contains(ht* H, int key);
bool ht_empty(ht* H);

#endif