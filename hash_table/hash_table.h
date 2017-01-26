#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <inttypes.h>

#define TRUE 1
#define FALSE 0
#define GROWTH_FACTOR 2
#define SHRING_FACTOR 0.5
#define ARRAY_SIZE 5 // using fixed length arrays instead of list...

typedef unsigned char bool;

typedef struct{
  int value;
  int key;
}item;


typedef struct {
  item ***table;
  uint32_t table_size;
}HashTable;

bool push_back(item **array_of_items, item* item);
void print(HashTable *h);
item *new_item(int key, int value);
HashTable *new(uint32_t table_size);
uint32_t hash(int key, uint32_t table_size);
void add(HashTable **h, int key , int value);
void add_item(HashTable *h, item *item);
bool exists(HashTable *h, int key);
void remove_item(HashTable **h, int key);
void delete(HashTable *h);


/// tests ///


void test_all();
void test_add();
void test_exists();
void test_remove_item();
void test_push_back();


#endif /* HASH_TABLE_H */
