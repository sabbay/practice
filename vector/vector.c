#include "vector.h"
#include <stdio.h>
#include <assert.h>


Vector* new(int32_t capacity){
  if(capacity <= 0){
    capacity = DEFAULT_CAPACITY;
  }
  Vector *v = malloc(sizeof(Vector));
  v->arr =  calloc(capacity, sizeof(int));
  v->capacity = capacity;
  v->size = 0;
  return v;
}

uint32_t size(Vector *v){
  return v->size;
}

uint32_t capacity(Vector *v){
  return v->capacity;
}

bool is_empty(Vector *v){
  if (v->size == 0){
    return TRUE;
  }
  return FALSE;
}

int32_t at(Vector *v, int32_t index){
  if(index < 0 || index >= v->size){
    printf("Invalid index");
    exit(-1);
  }else{
    return v->arr[index];
  }
}

void destroy(Vector *v){
  free(v->arr);
  free(v);
}

void resize(Vector *v, int32_t new_capacity){
  int i;
  int *new_arr = calloc(new_capacity, sizeof(int));
  for(i=0; i < v->capacity; i++){
    new_arr[i] = v->arr[i];
  }
  v->capacity = new_capacity;
  v->arr = new_arr;
}


void push(Vector *v, int item){

  if(v->size == v->capacity){
    resize(v, v->capacity * GROWTH_FACTOR);
  }
    v->arr[v->size] = item;
    v->size++;
}

int find(Vector *v, int item){
  int i;
  for(i=0; i< size(v); i++){
    if(at(v, i) == item){
      return i;
    }
  }
  return -1;
}

int pop(Vector *v){
  int tmp;
  if(is_empty(v)){
    printf("vector is empty... cannot pop");
    exit(-1);
  }
  tmp = at(v, size(v) -1);
  v->arr[size(v)-1] = 0;
  v->size--;
  return tmp;
}


void insert(Vector *v, int32_t index, int item){
  if(index == v->size){
    push(v, item);
  }else if(index > v->size -1 || index < 0){
    printf("Invalid index");
    exit(-1);
  }else{
    int i;
    if(v->size == v->capacity){
      resize(v, v->capacity * GROWTH_FACTOR);
    }
    for(i=v->size-1; i >=index ; i--){
      v->arr[i+1] = v->arr[i];
    }
    v->arr[index] = item;
    v->size++;
  }
}



void print(Vector *v){
  int i;
  printf("Size:%d\nCapacity:%d\nItems\n", size(v), capacity(v));
  for(i=0; i< size(v); i++){
    printf("%d:%d  ", i,at(v, i));
  }
  printf("\n");
}

//////////////// tests ///////////////

void test_all(){
  printf("Running all tests\n");
  test_new();
  test_push();
  test_resize();
  test_insert();
  test_find();
  test_pop();
}

void test_pop(){
  int i;
  Vector *v = new(2);
  for(i=0; i< 5; i++){
    push(v, i);
  }
  assert(pop(v) == 4);
  assert(size(v) == 4);
  destroy(v);
}

void test_find(){
  Vector *v = new(4);
  int i;
  for(i=0; i< 4; i++){
    push(v, i);
  }
  assert (find(v, 0) == 0);
  assert (find(v, 3) == 3);
  assert (find(v, 2) == 2);
  destroy(v);
}

void test_insert(){
  Vector *v = new(6);
  int i;

  for(i = 0 ; i < 6; i++){
    push(v, i);
  }

  insert(v, 2, 10);
  assert(at(v, 2) == 10);
  assert(at(v, 3) == 2);
  assert(at(v, 1) == 1);
  assert(size(v) == 7);
  assert(capacity(v) == 6 * GROWTH_FACTOR);
  insert(v, 6, 10);
  assert(at(v, 6) == 10);
  assert(at(v, 7) == 5);
  insert(v, 8, 10);
  assert(at(v,8) == 10);
  assert(size(v) == 9);
  destroy(v);
}

void test_push(){
  Vector *v = new(1);
  push(v, 1);
  assert(at(v, 0) == 1);
  push(v, 2);
  assert(at(v, 1) == 2);
  destroy(v);
}

void test_resize(){
  int i;
  Vector *v = new(2);
  for(i= 0; i< 3; i++){
    push(v, i);
  }
  assert(v->capacity == 2* GROWTH_FACTOR);
  assert(v->size == 3);
  destroy(v);
}


void test_new(){
  /* printf("new test...\n"); */

  Vector *v = new(-12); // invalid capacity, using default
  assert(v->capacity == DEFAULT_CAPACITY);
  assert(v->size == 0);
  destroy(v);

  v = new(123);
  assert(v->capacity == 123);
  assert(v->size == 0);
  destroy(v);
}


void test_is_empty() {
  Vector *v = new(123);
  assert(is_empty(v) == TRUE);
  push(v, 2);
  assert(is_empty(v) == FALSE);
  destroy(v);
}
