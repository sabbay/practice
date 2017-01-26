#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>
#include "hash_table.h"


void delete(HashTable *h){
  int i,j;
  for(i = 0 ; i<h->table_size ; i++){
    for(j = 0; j< ARRAY_SIZE; j++){
      free(h->table[i][j]);
    }
    free(h->table[i]);
  }
  free(h->table);
  free(h);
}


void print(HashTable* h) {
  int i;
  printf("---------------size %d, \n",h->table_size 
         );
  for(i = 0 ; i < h->table_size; i++){
    if(h->table[i] == 0x0){
      printf("%d : 0x0\n", i);
    }else{
      int j;
      printf("%d:  ", i);
      for(j = 0; j < ARRAY_SIZE; j++){
        if(h->table[i][j] == 0x0){
          printf("%d : (0x0 ,0x0) ", j);
        }else{
          printf("%d : (%d ,%d) ", j, h->table[i][j]->key, h->table[i][j]->value);
        }
      }
      printf("\n");
    }
  }
  printf("-----------------------------\n");
}

item *new_item(int key, int value) {
  item *b = calloc(1, sizeof(item));
  b->key = key;
  b->value = value;
  return b;
}

HashTable *new(uint32_t table_size){
  HashTable *h = calloc(1, sizeof(HashTable));
  h->table_size = table_size;
  h->table = calloc(table_size, sizeof(item*));
  int i;
  for(i=0;  i < h->table_size; i++){
    h->table[i] = calloc(ARRAY_SIZE, sizeof(item*));
  }
  return h;
}


uint32_t hash(int key, uint32_t table_size) {
  uint64_t p = 16769023;
  uint64_t a = 8414313;
  uint64_t b = 4074212;
  return ((a*key + b) % p) % table_size;
}


bool push_back(item **array_of_items, item* item){
  int i;
  for(i = 0 ; i < ARRAY_SIZE; i++){
    if(array_of_items[i] == 0x0 || array_of_items[i]->key == item->key){
      array_of_items[i] = item;
      return TRUE;
    }
  }
  return FALSE;
}

void add(HashTable** h, int key, int value) {
  uint32_t index = hash(key, (*h)->table_size);
  int i, j;
  if(push_back((*h)->table[index], new_item(key, value)) == FALSE){
    // it means we need to rebuild table....
    HashTable *new_table = new((*h)->table_size * GROWTH_FACTOR);
    push_back(new_table->table[hash(key, new_table->table_size)], new_item(key, value));
    for(i = 0 ; i < (*h)->table_size; i++){
      for(j = 0 ; j < ARRAY_SIZE && (*h)->table[i][j] != 0x0; j++){
        uint32_t new_index = hash((*h)->table[i][j]->key, new_table->table_size);
        if(push_back(new_table->table[new_index], new_item((*h)->table[i][j]->key, (*h)->table[i][j]->value)) == FALSE){
          printf("Exception");
          exit(-1);
        }
      }
    }
    delete(*h);
    *h = new_table;
  }
  //if it returns true item is already added...
  return;
}


void add_item(HashTable* h, item* item) {
  add(h, item->key, item->value);
}

bool exists(HashTable* h, int key) {

  uint32_t index = hash(key, h->table_size);
  int j;

  if(h->table[index] == 0x0){
    return FALSE;
  }

  for(j = 0 ; j < ARRAY_SIZE; j++){
    if(h->table[index][j] == 0x0){
      return FALSE;
    }
    if(h->table[index][j]->key == key){
      return TRUE;
    }
  }
  return FALSE;
}


void remove_item(HashTable** h, int key) {
  uint32_t index = hash(key, (*h)->table_size);
  int  j = 0;
    for(j=0;j< ARRAY_SIZE; j++){
      if((*h)->table[index][j] == 0x0){
        return;
      }
      if((*h)->table[index][j]->key == key){
        free((*h)->table[index][j]);
        (*h)->table[index][j] = 0x0;
      }
  }
}

//////////////////////////


void test_all(){
  test_add();
 test_exists();
  test_push_back();
  test_remove_item();
}


void test_remove_item(){
  HashTable *h  = new(5);
  add(&h, 10, 5);
  assert(exists(h, 10) == TRUE);
  remove_item(&h, 10);
  assert(exists(h, 10) == FALSE);
}



void test_exists(){
  HashTable *h = new(5);
  add(&h, 23, 5);
  add(&h, 53, 5);
  add(&h, 25, 5);
  assert(exists(h, 23) == TRUE);
  assert(exists(h, 3) == FALSE);
  assert(exists(h, 25) == TRUE);
  assert(exists(h, 53) == TRUE);
}

void test_push_back() {
  HashTable *h = new(5);
  push_back((h->table[0]), new_item(10, 2));
  push_back((h->table[0]), new_item(11, 3));
  push_back((h->table[0]), new_item(12, 4));
  push_back((h->table[0]), new_item(13, 4));
  assert(push_back(h->table[0], new_item(15, 5)) == TRUE);
  push_back((h->table[0]), new_item(14, 4));
  assert(push_back(h->table[0], new_item(15, 5)) == TRUE);
  assert(push_back(h->table[0], new_item(18, 5)) == FALSE);
}



void test_add(){
  HashTable *h = new(5);
  add(&h, 5, 10);
  add(&h, 10, 11);
  add(&h, 15, 11);
  add(&h, 20, 11);
  add(&h, 25, 11);
  add(&h, 30, 11);
  add(&h, 35, 11);
  print(h);
}







