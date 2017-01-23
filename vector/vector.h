#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
#include <stdint.h>

#define DEFAULT_CAPACITY 1
#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 2

#define TRUE 1
#define FALSE 0
typedef unsigned char bool;

typedef struct
{
  int *arr;
  uint32_t size;
  uint32_t capacity;
}Vector;

Vector* new(int32_t capacity); // pass 0 to use defaults
uint32_t size(Vector *v);
uint32_t capacity(Vector *v);
bool is_empty(Vector *v);
int32_t at(Vector *v, int32_t index);
void push(Vector *v, int item);
void insert(Vector *v, int32_t index, int item);
int pop(Vector *v);
void delete(Vector *v, int32_t index);
int find(Vector *v, int item);
void resize(Vector *v, int32_t new_capacity);
void destroy(Vector *v);
void print(Vector *v);

//tests here

void test_all();
void test_new();
void test_is_empty();
void test_push();
void test_resize();
void test_insert();
void test_find();
void test_pop();






#endif /* VECTOR_H */
