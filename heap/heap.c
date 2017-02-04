#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>


void insert(Heap *heap, int value){
  if(heap->size > heap->capacity){
    *heap = create_heap(heap->array, heap->size, heap->capacity * 2);
    heap->array[heap->size] = value;
    heap->size++;
    max_heapify(heap);
  }else{
    heap->array[heap->size] = value;
    heap->size++;
    sift_up(heap->size-1, heap);
  }
}


void remove_element(Heap *heap, int index){
  change_priority(heap, index, INT_MAX);
  extract_max(heap);
}

void change_priority(Heap* heap, int index, int new_priority) {
  if(index >= heap->size){
    printf("Invalid index");
    exit(-1);
  }
  if(heap->array[index] > new_priority){
    heap->array[index] = new_priority;
    sift_down(index, heap);
  }else if(heap->array[index] < new_priority){
    heap->array[index] = new_priority;
    sift_up(index, heap);
  }
}

int get_max(Heap *heap){
  return heap->array[0];
}

int extract_max(Heap *heap){
  if(heap->size == 1){
    heap->size--;
    return heap->array[0];
  }else{
    int result = heap->array[0];
    swap(0, heap->size - 1, heap->array);
    heap->size--;
    sift_down(0, heap);
    return result;
  }
}

void sift_down(int index, Heap *heap){
  fflush(stdout);
  if(is_leaf(index, heap->size)){
    return;
  }else if(right_index(index, heap->size) == -1){ // has only one child, and after swapping will become leaf
    if(*left_node(index, heap) > heap->array[index]){
      swap(index, left_index(index, heap->size), heap->array);
    }else{
      return;
    }
  }else{// has two children
    if( // left child is the greatest
       *left_node(index, heap) > *right_node(index, heap) &&
       *left_node(index, heap) > heap->array[index]
       ){
      swap(index, left_index(index, heap->size), heap->array);
      sift_down(left_index(index, heap->size), heap);
    }
    fflush(stdout);
    if( // right child is the greatest
       *right_node(index, heap) > * left_node(index, heap) &&
       *right_node(index, heap) > heap->array[index]
             ){
      swap(index, right_index(index, heap->size), heap->array);
      sift_down(right_index(index, heap->size), heap);
    }
    else{ // the node is the greatest
      return;
    }
  }
}


int get_size(Heap *heap){
  return heap->size;
}

bool is_empty(Heap *heap){
  if(heap->size == 0){
    return TRUE;
  }
  return FALSE;
}

void print_array(int *array, int size) {
  int i;
  for(i = 0 ; i < size; i ++){
    printf("%d ", array[i]);
  }
  printf("\n");
}

bool is_leaf(int index, int size){
  if(right_index(index, size) == -1  && left_index(index, size) == -1){
    return TRUE;
  }
  return FALSE;
}

void swap(int dest, int source, int *array){
  int tmp = array[dest];
  array[dest] = array[source];
  array[source] = tmp;
}

void sift_up(int index, Heap *heap){
  if(parent_node(index, heap) == 0x0){
    swap(index, 0, heap->array);
  }
  else{
    if(*parent_node(index, heap) < heap->array[index]){
      swap(parent_index(index), index, heap->array);
      sift_up(parent_index(index), heap);
    }
  }
}


Heap create_heap(int *array, int size, int capacity){
  if(capacity < 0 || size < 0 || size > capacity){
    printf("incorrect data\n");
    exit(-1);
  }
  Heap *new = calloc(1, sizeof(Heap));
  new->array = calloc(capacity, sizeof(int));

  for(int i = 0; i< size; i++){
    new->array[i] = array[i];
  }

  new->size = size;
  new->capacity = capacity;
  return *new;
}

Heap new_heap(int capacity) {
  Heap *new = calloc(1, sizeof(Heap));
  new->array = calloc(capacity, sizeof(int));
  new->capacity = capacity;
  new->size = 0;
  return *new;
}

void max_heapify(Heap *heap){
  int i;
  for(i = (heap->size -1 ) / 2; i>=0; i--){
    __max_heapify(heap, i);
  }
}

void __max_heapify(Heap *heap, int root_index) {
  if(is_leaf(root_index, heap->size)){
    return; // a leaf is already a heap
  }
  if(right_node(root_index, heap) != 0x0  &&
     *right_node(root_index, heap) > heap->array[root_index] &&
     *right_node(root_index, heap) > *left_node(root_index, heap)
     ){ // if right child is greatest
    swap(root_index, right_index(root_index, heap->size), heap->array);
    __max_heapify(heap, right_index(root_index, heap->size));
  }else if(left_node(root_index, heap) != 0x0 &&
           *left_node(root_index, heap) > heap->array[root_index] &&
           *left_node(root_index, heap) > *right_node(root_index, heap)
           ){ // if left child is greatest
    swap(root_index, left_index(root_index, heap->size), heap->array);
    __max_heapify(heap, left_index(root_index, heap->size));
  }else{ // is already heapified
    return;
  }
}

int left_index(int index, int size){
  if(2*index +1 > size){
    return -1;
  }
  return 2*index +1;
}

int *left_node(int index,Heap *heap){
  if(left_index(index, heap->size) != -1){
    return &heap->array[left_index(index, heap->size)];
  }
  return 0x0;
}

int right_index(int index, int size){
  if(2*index +2 > size){
    return -1;
  }
  return 2*index + 2;
}


int *right_node(int index, Heap *heap) {
  if(right_index(index, heap->size) != -1){
    return &heap->array[right_index(index, heap->size)];
  }
  return 0x0;
}

int parent_index(int index){
  if(index == 0){
    return - 1;
  }
  return (index - 1) / 2;
}


int *parent_node(int index, Heap *heap) {
  if(parent_index(index) != -1){
    return &heap->array[parent_index(index)];
  }
  return 0x0;
}






void test_all(){
  test_create_max_heap();
  test_insert();
  test_extract();
  test_change_priority();
  test_remove_element();
}

void test_remove_element(){
  int arr[] = {1, 5, 10, 23, 1, 4, 5};
  Heap h = create_heap(arr, 7, 10);
  max_heapify(&h);
  remove_element(&h, 4);
  assert(h.size == 6);
}

void test_change_priority(){
  int ar[] = {1, 2, 3, 5, 10};
  Heap h = create_heap(ar, 5, 10);
  max_heapify(&h);
  change_priority(&h, 0, 200);
  assert(h.array[0] == 200);
  change_priority(&h, 0, -2);
  assert(h.array[h.size -1] == -2);
}

void test_extract(){
  Heap heap2 = new_heap(1);
  Heap heap = new_heap(5);
  insert(&heap2, 1337);
  assert(extract_max(&heap2) == 1337);
  assert(heap2.size == 0);
  int result[] = {80, 70, 60, 40, 30, 20, 50, 10};
  insert(&heap, 10);
  insert(&heap, 20);
  insert(&heap, 30);
  insert(&heap, 40);
  insert(&heap, 50);
  insert(&heap, 60);
  insert(&heap, 70);
  insert(&heap, 80);
  assert(memcmp(heap.array, result, heap.size) == 0);
  assert(extract_max(&heap) == 80);
  assert(heap.size == 7);
}

void test_insert(){
  Heap heap = new_heap(1);
  int result[] = {80, 70, 60, 40, 30, 20, 50, 10};
  insert(&heap, 10);
  insert(&heap, 20);
  insert(&heap, 30);
  insert(&heap, 40);
  insert(&heap, 50);
  insert(&heap, 60);
  insert(&heap, 70);
  insert(&heap, 80);
  assert(memcmp(heap.array, result, heap.size) == 0);
}


void test_create_max_heap(){
  int arr[] ={1, 2, 3, 10, 9, 23, 451, 2313};
  int result[] = {2313, 10, 451, 2, 9, 23, 3, 1};
  Heap heap = create_heap(arr, sizeof(arr)/sizeof(arr[0]), 20);
  max_heapify(&heap);
  assert(memcmp(heap.array, result, heap.size) == 0);
}






