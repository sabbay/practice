#include "linked-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>




Node* copy_node(Node* node) {
  if(node == 0x0){
    return 0x0;
  }
  Node *new = calloc(1, sizeof(Node));
  new->value = node->value;
  return new;
}

List copy_list(List *source, uint32_t index_start, uint32_t index_end){
  List *l = calloc(1, sizeof(List));
  uint32_t cur_index = 0;

  if(index_start < 0 || index_start > index_end || index_end > source->size -1){
    printf("cannot copy, invalid index");
    exit(-1);
  }

  Node *cur;
  cur = source->head;

  while(cur_index < index_start){
    cur = cur->next;
    cur_index++;
  }

  l->head = copy_node(cur);
  Node *cur_list= l->head;

  while(cur_index < index_end){
    printf("currently copying with value %d\n", cur->value);
    cur = cur->next;
    cur_list->next = copy_node(cur);
    if(cur_index == index_end){
      l->tail = cur_list;
    }
    cur_list = cur_list->next;
    cur_index++;
  }

 return *l;
}

List new(){
  List *l = calloc(1, sizeof(List));
  return *l;
}


void print(List *l) {
  int index=0;
  if(l->head == 0x0){
    return;
  }

  Node *cur = l->head;

  while(cur != 0x0){
    printf("%d:[%d, %x] ", index, cur->value, cur);
    index++;
    cur = cur->next;
  }
  printf("\n");
  printf("size %d   head %x   tail %x", l->size, l->head, l->tail);
  printf("\n");
}



bool empty(List *l) {
  if(l->head == 0x0){
    return TRUE;
  }
  return FALSE;
}

uint16_t size(List *l) {
  uint16_t n=0;
  if(l->head == 0x0){
    return 0; // empty list
  }

  Node *cur = l->head;

  while(cur!= 0x0){
    cur= cur->next;
    n++;
  }
  return n;
}


int value_at(List *l, int index) {
  int c_indx = 0;
  Node *cur = l->head;
  while(c_indx < index){
    c_indx++;
    if(l->head == 0x0){
      printf("invalid index\n"); 
      exit(-1);
    }
    cur= cur->next;
  }
  return cur->value;
}


void push_front(List *l, int value) {
  Node *new_node =calloc(1, sizeof(Node));
  new_node->value = value;
  new_node->next = l->head;
  if(l->head == 0x0){
    l->tail = new_node; // first elemnt of a one element list is at the same time tail and head
  }
  l->head = new_node;
  l->size++;
}


int pop_front(List *l) {
  Node *tmp;
  int value;
  if(l->head == 0x0){
    printf("cannot pop empty list...");
    exit(-1);
  }
  tmp = l->head;
  value = tmp->value;
  l->head = tmp->next;
  free(tmp);
  l->size--;
  if(l->size == 0){ // quick dirty fix
    l->tail = 0x0;
  }
  return value;
}


void push_back(List *l, int value) {
  Node *new_node = calloc(1, sizeof(Node)); // next is already 0x0 thanks to calloc
  new_node->value = value;

  if(l->head == 0x0){
    l->head = new_node;
    l->tail = new_node;
    l->size++;
    return;
  }

  l->tail->next = new_node;
  l->tail = new_node;
  l->size++;

}

int pop_back(List *l){
  int value;
  Node *previous = 0x0;
  if(l->head == 0x0){
    printf("Cannot pop_back empty list");
    exit(-1);
  }
  Node *cur = l->head;
  while(cur ->next != 0x0){
    previous = cur;
    cur = cur->next;
  }
  if(previous != 0x0){
    previous->next = 0x0;
    l->tail = previous;
  }else{
    l->head = 0x0;
    l->tail = 0x0;
  }
  value = cur->value;
  free(cur);
  l->size--;
  return value;
}

int front(List *l){
  if(l->head == 0x0){
    printf("empty list");
    exit(-1);
  }
  return l->head->value;
}

int back(List *l){
  if(l->head == 0x0){
    printf("empty list");
    exit(-1);
  }
  Node *cur = l->head;
  while(cur->next != 0x0){
    cur = cur->next;
  }
  return cur->value;
}

int value_n_from_end(List *l, int n){
  if(l->head == 0x0 || n<1){
    printf("invalid n");
    exit(-1);
  }
  Node *left_bound = l->head;
  Node *right_bound = l->head;
  int i;
  for(i=0; i<n && right_bound!=0x0; i++){
    right_bound = right_bound->next;
  }
  if(i!= n){
    printf("List is too shotrt");
    exit(-1);
  }
  while(right_bound!=0x0){
    right_bound = right_bound->next;
    left_bound = left_bound->next;
  }
  return left_bound->value;
}


void erase(List *l, int index){
  int i;
  Node *prev = 0x0;
  Node *cur = l->head;

  if(l->head == 0x0){
    printf("Unable to erase from empty list");
  }

  for(i = 0; i<index && cur != 0x0; i++){
    prev = cur;
    cur = cur->next;
  }

  if(i != index){
    printf("Index out of bounds");
    return;
  }

  if(index == l->size -1){ // quick fix
    l->tail = prev;
  }

  if(prev != 0x0){
    prev->next = cur->next;
  }else{
    l->head =  cur->next;
  }
  l->size--;
  free(cur);

}

void insert(List *l, int index, int value){

  int i;
  Node *prev = 0x0;
  Node *cur = l->head;

  Node *new_node = calloc(1, sizeof(Node));
  new_node->value = value;

  for(i = 0; i<index && cur != 0x0; i++){
    prev = cur;
    cur = cur->next;
  }

  if(i != index){
    printf("Index out of bounds");
    return;
  }

  if(cur == 0x0){l->tail = new_node; }
  if(prev == 0x0){
    new_node->next = l->head;
    l->head = new_node;
  }else{
    prev->next = new_node;
    new_node->next = cur;
  }
  l->size++;
}


void reverse(List *l){
  if(l->head == 0x0){
    printf("Cannod reverse empty list");
    exit(-1);
  }
  Node *left, *mid, *right;
  mid = l->head;
  right = l->head;
  left = 0x0;

  while(mid != 0x0){
    right = mid->next;
    mid->next = left;
    left = mid;
    mid = right;
  }

  l->head = left;

}



void remove_value(List *l, int value){
  Node *prev = 0x0;
  Node *cur = l->head;
  bool found = FALSE;
  if(l->head == 0x0){
    return;
  }

  while(cur != 0x0){
    if(cur->value == value){
      if(prev == 0x0){
        l->head = cur->next;
      }else{
        prev->next = cur->next;
      }
      found = TRUE;
      l->size--;
      free(cur);
    }
    if(found){
      found = FALSE;
      prev = 0x0;
    }else{
      prev = cur;
    }
    cur = cur->next;
  }

}




/////////// tests ///////////////

void custom_test(){
  List l = new();
  insert(&l, 0, 123);
  print(&l);
  insert(&l, 1, 23);
  print(&l);
  /* erase(&l, 1); */
  /* erase(&l, 0); */
  /* assert(l.tail == 0x0); */
  print(&l);
}

void test_all(){
  test_value_at();
  test_push_front();
  test_empty();
  test_pop_front();
  test_push_back();
  test_pop_back();
  test_back();
  test_front();
  test_insert();
  test_erase();
  test_value_n_from_end();
  test_reverse();
  test_remove_value();
  custom_test();
  test_copy_list();
}


void test_copy_list(){
  List l = new();
  push_back(&l, 10);
  push_back(&l, 11);
  push_back(&l, 12);
  push_back(&l, 13);
  push_back(&l, 14);
  List kek = copy_list(&l, 1, 3);
  print(&l);
  print(&kek);
}


void test_remove_value(){
  List l = new();
  push_back(&l, 2);
  push_back(&l, 2);
  
  assert(l.size == size(&l));
  remove_value(&l, 2);
  assert(l.size == size(&l));
  
  assert(empty(&l) == TRUE);
  push_back(&l, 2);
  push_back(&l, 2);
  push_back(&l, 3);
  remove_value(&l, 2);
  assert(value_at(&l, 0) == 3);
  push_back(&l, 2);
  push_back(&l, 3);
  remove_value(&l, 3);
  assert(value_at(&l, 0) == 2 );
}

void test_reverse(){
  List l = new();
  push_back(&l, 1);
  reverse(&l);
  assert(l.size == size(&l));
  assert(value_at(&l, 0) == 1);
  push_back(&l, 2);
  push_back(&l, 3);
  reverse(&l);
  assert(l.size == size(&l));
  assert(value_at(&l, 0) == 3);
  assert(value_at(&l, 1) == 2);
  assert(value_at(&l, 2) == 1);
}

void test_erase(){
  List l = new();
  push_back(&l, 1);
  erase(&l, 0);
  assert(l.size == size(&l));
  assert(empty(&l) == TRUE);
  push_back(&l, 1);
  push_back(&l, 2);
  erase(&l, 0);
  assert(l.size == size(&l));
  assert(size(&l) == 1);
  assert(value_at(&l, 0) == 2);
  erase(&l, 0);
  assert(empty(&l) == TRUE);

  assert(l.size == size(&l));

  push_back(&l, 2);
  push_back(&l, 3);
  push_back(&l, 4);
  push_back(&l, 5);
  erase(&l, 3);
  assert(size(&l) == 3);
}

void test_insert(){
  List l = new();
  insert(&l, 0, 10);
  
  assert(value_at(&l, 0) == 10);
  insert(&l, 0, 11);
  insert(&l, 0, 12);
  insert(&l, 2, 22);
  insert(&l, 4, 44);
  
  assert(l.size == size(&l));
  assert(value_at(&l, 0) == 12 );
  assert(value_at(&l, 1) == 11 );
  assert(value_at(&l, 2) == 22 );
  assert(value_at(&l, 3) == 10 );
  assert(value_at(&l, 4) == 44 );
}

void test_back(){
  List l = new();
  push_back(&l, 5);
  push_back(&l, 4);
  assert(l.size == size(&l));
  assert(back(&l) == 4);
}

void test_front(){
  List l = new();
  push_front(&l, 5);
  push_front(&l, 4);
  assert(l.size == size(&l));
  assert(front(&l) == 4);
}

void test_pop_back(){
  List l = new();
  push_back(&l, 5);
  push_back(&l, 3);
  push_back(&l, 2);
  assert(l.size == size(&l));
  assert(size(&l) == 3);
  assert(pop_back(&l) == 2);
  
  assert(pop_back(&l) == 3);
  assert(l.size == size(&l));
  assert(pop_back(&l) == 5);
  assert(l.size == size(&l));
  
  assert(l.tail == 0x0);
  assert(size(&l)== 0);
}

void test_push_back(){
  List l = new();
  push_back(&l, 10);
  push_back(&l, 11);
  push_back(&l, 12);
  push_back(&l, 13);
  assert(l.size == size(&l));
  assert(size(&l) == 4);
  assert(l.size == size(&l));
  assert(value_at(&l, 0) == 10);
  assert(value_at(&l, 1) == 11);
  assert(value_at(&l, 2) == 12);
  assert(l.size == size(&l));
  assert(value_at(&l, 3) == 13);
}

void test_pop_front(){
  List l = new();
  push_front(&l, 10);
  assert(l.size == size(&l));
  
  assert(pop_front(&l) == 10);
  assert(l.size == size(&l));
  assert(empty(&l));
}

void test_value_at(){
  List l = new();
  push_front(&l, 5);
  assert(value_at(&l, 0) == 5);
  push_front(&l, 6);
  assert(l.size == size(&l));
  assert(value_at(&l, 1) == 5);
  assert(l.size == size(&l));
  assert(value_at(&l, 0) == 6);
}

void test_push_front(){
   List l = new();
   push_front(&l, 1);
   push_front(&l, 2);
   push_front(&l, 3);
   assert(l.size == size(&l));
   push_front(&l, 4);
   push_front(&l, 5);
   
   assert(size(&l) == 5);
   assert(value_at(&l, 0) == 5);
   assert(value_at(&l, 1) == 4);
   assert(l.size == size(&l));
   assert(value_at(&l, 2) == 3);
   assert(value_at(&l, 3) == 2);
   assert(value_at(&l, 4) == 1);
}

void test_empty(){
  List l = new();
  assert( empty(&l) == TRUE);
  assert(l.size == size(&l));
  push_front(&l, 5);
  assert( empty(&l) == FALSE);
  assert(l.size == size(&l));
}


void test_value_n_from_end() {
  List l = new();
  push_back(&l, 1);
  push_back(&l, 2);
  assert(l.size == size(&l));
  push_back(&l, 3);
  push_back(&l, 4);
  push_back(&l, 5);
  assert(value_n_from_end(&l, 1) == 5);
  assert(value_n_from_end(&l, 3) == 3);
  assert(value_n_from_end(&l, 5) == 1);
  assert(l.size == size(&l));
}









