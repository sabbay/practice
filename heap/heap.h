#ifndef HEAP_H
#define HEAP_H

#define TRUE 1
#define FALSE 0
typedef unsigned char bool;



//idexing from 1
// parent i/2
// left child 2i
// right child 2i + 1

//indexing from 0
// parent (i-1)/2
// left child 2i +1
// right child 2i + 2

typedef struct {
  int capacity;
  int size;
  int *array;
}Heap;

void print_array(int *array, int size);
void insert(Heap *heap, int value);
int hibit(int num);
void __max_heapify(Heap *heap, int root_index);
void max_heapify(Heap *heap);
Heap create_heap(int *array, int size, int capacity);
Heap new_heap(int capacity);
int left_index(int index, int size);
int *left_node(int index, Heap *heap);
int right_index(int index, int size);
int *right_node(int index, Heap *heap);
int parent_index(int index);
int *parent_node(int index, Heap *heap);
void sift_up(int index, Heap *heap);
void sift_down(int index, Heap *heap);
bool is_leaf(int index, int size);
void swap(int dest, int source, int *array);
int get_max(Heap *heap);
int get_height(int size);
int get_size(Heap *heap);
bool is_empty(Heap *heap);
int extract_max(Heap *heap);
void change_priority(Heap *heap, int index, int new_priority);
void remove_element(Heap *heap, int index);



void test_all();
void test_create_max_heap();
void test_insert();
void test_extract();
void test_change_priority();
void test_remove_element();

#endif /* HEAP_H */
