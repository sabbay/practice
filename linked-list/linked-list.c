#include "linked-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void print(Node* head) {
  int index=0;
  if(head == 0x0){
    return;
  }
  while(head != 0x0){
    printf("%d:[%d, %x] ", index, head->value, head);
    index++;
    head = head->next;
  }
  printf("\n");
}


bool empty(Node* head) {
  if(head == 0x0){
    return TRUE;
  }
  return FALSE;
}

uint16_t size(Node* head) {
  uint16_t n=0;
  if(head == 0x0){
    return 0; // empty list
  }
  while(head != 0x0){
    head = head->next;
    n++;
  }
  return n;
}


int value_at(Node* head, int index) {
  int c_indx = 0;
  while(c_indx < index){
    c_indx++;
    if(head == 0x0){
      printf("invalid index\n"); 
      exit(-1);
    }
    head = head->next;
  }
  return head->value;
}


void push_front(Node** head, int value) {
  Node *new_node =calloc(1, sizeof(Node));
  new_node->value = value;
  new_node->next = *head;
  *head = new_node;
}


int pop_front(Node** head) {
  Node *tmp;
  int value;
  if(*head == 0x0){
    printf("cannot pop empty list...");
    exit(-1);
  }
  tmp = *head;
  value = tmp->value;
  *head = tmp->next;
  free(tmp);
  return value;
}


void push_back(Node** head, int value) {
  Node *new_node = calloc(1, sizeof(Node)); // next is already 0x0 thanks to calloc
  new_node->value = value;

  if(*head == 0x0){
    *head = new_node;
    return;
  }

  int n =0;
  Node *cur = *head;
  while( cur->next != 0x0){
    n++;
    cur = cur->next;
  }
  cur->next = new_node;

}

int pop_back(Node **head){
  int value;
  Node *previous = 0x0;
  if(head == 0x0){
    printf("Cannot pop_back empty list");
    exit(-1);
  }
  Node *cur = *head;
  while(cur ->next != 0x0){
    previous = cur;
    cur = cur->next;
  }
  if(previous != 0x0){
    previous->next = 0x0;
  }else{
    *head = 0x0;
  }
  value = cur->value;
  free(cur);
  return value;
}

int front(Node *head){
  if(head == 0x0){
    printf("empty list");
    exit(-1);
  }
  return head->value;
}

int back(Node *head){
  if(head == 0x0){
    printf("empty list");
    exit(-1);
  }
  while(head->next != 0x0){
    head = head->next;
  }
  return head->value;
}

int value_n_from_end(Node *head, int n){
  if(head == 0x0 || n<1){
    printf("invalid n");
    exit(-1);
  }
  Node *left_bound = head;
  Node *right_bound = head;
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


void erase(Node **head, int index){
  int i;
  Node *prev = 0x0;
  Node *cur = *head;

  if(*head == 0x0){
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


  if(prev != 0x0){
    prev->next = cur->next;
  }else{
    *head =  cur->next;
  }
  free(cur);

}

void insert(Node **head, int index, int value){

  int i;
  Node *prev = 0x0;
  Node *cur = *head;

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

  if(prev == 0x0){
    new_node->next = *head;
    *head = new_node;
  }else{
    prev->next = new_node;
    new_node->next = cur;
  }

}


void reverse(Node **head){
  if(*head == 0x0){
    printf("Cannod reverse empty list");
    exit(-1);
  }
  Node *left, *mid, *right;
  mid = *head;
  right = *head;
  left = 0x0;

  while(mid != 0x0){
    right = mid->next;
    mid->next = left;
    left = mid;
    mid = right;
  }

  *head = left;

}



void remove_value(Node **head, int value){
  Node *prev = 0x0;
  Node *cur = *head;
  bool found = FALSE;
  if(*head == 0x0){
    return;
  }

  while(cur != 0x0){
    if(cur->value == value){
      if(prev == 0x0){
        *head = cur->next;
      }else{
        prev->next = cur->next;
      }
      found = TRUE;
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
}


void test_remove_value(){
  Node *head = 0x0;
  push_back(&head, 2);
  push_back(&head, 2);
  remove_value(&head, 2);
  print(head);
  assert(empty(head) == TRUE);
  push_back(&head, 2);
  push_back(&head, 2);
  push_back(&head, 3);
  remove_value(&head, 2);
  assert(value_at(head, 0) == 3);
  push_back(&head, 2);
  push_back(&head, 3);
  remove_value(&head, 3);
  assert(value_at(head, 0) == 2 );
}

void test_reverse(){
  Node *head = 0x0;
  push_back(&head, 1);
  reverse(&head);
  assert(value_at(head, 0) == 1);
  push_back(&head, 2);
  push_back(&head, 3);
  reverse(&head);
  assert(value_at(head, 0) == 3);
  assert(value_at(head, 1) == 2);
  assert(value_at(head, 2) == 1);
}

void test_erase(){
  Node *head = 0x0;
  push_back(&head, 1);
  erase(&head, 0);
  assert(empty(head) == TRUE);
  push_back(&head, 1);
  push_back(&head, 2);
  erase(&head, 0);
  assert(size(head) == 1);
  assert(value_at(head, 0) == 2);
  erase(&head, 0);
  assert(empty(head) == TRUE);


  push_back(&head, 2);
  push_back(&head, 3);
  push_back(&head, 4);
  push_back(&head, 5);
  erase(&head, 3);
  assert(size(head) == 3);
}

void test_insert(){
  Node *head = 0x0;
  insert(&head, 0, 10);
  assert(value_at(head, 0) == 10);
  insert(&head, 0, 11);
  insert(&head, 0, 12);
  insert(&head, 2, 22);
  insert(&head, 4, 44);
  assert(value_at(head, 0) == 12 );
  assert(value_at(head, 1) == 11 );
  assert(value_at(head, 2) == 22 );
  assert(value_at(head, 3) == 10 );
  assert(value_at(head, 4) == 44 );
}

void test_back(){
  Node *head = 0x0;
  push_back(&head, 5);
  push_back(&head, 4);
  assert(back(head) == 4);
}

void test_front(){
  Node *head = 0x0;
  push_front(&head, 5);
  push_front(&head, 4);
  assert(front(head) == 4);
}

void test_pop_back(){
  Node *head = 0x0;
  push_back(&head, 5);
  push_back(&head, 3);
  push_back(&head, 2);
  assert(size(head) == 3);
  assert(pop_back(&head) == 2);
  assert(pop_back(&head) == 3);
  assert(pop_back(&head) == 5);
  assert(size(head)== 0);
}

void test_push_back(){
  Node *head = 0x0;
  push_back(&head, 10);
  push_back(&head, 11);
  push_back(&head, 12);
  push_back(&head, 13);
  assert(size(head) == 4);
  assert(value_at(head, 0) == 10);
  assert(value_at(head, 1) == 11);
  assert(value_at(head, 2) == 12);
  assert(value_at(head, 3) == 13);
}

void test_pop_front(){
  Node *head = 0x0;
  push_front(&head, 10);
  assert(pop_front(&head) == 10);
  assert(empty(head));
}

void test_value_at(){
  Node *head = 0x0;
  push_front(&head, 5);
  assert(value_at(head, 0) == 5);
  push_front(&head, 6);
  assert(value_at(head, 1) == 5);
  assert(value_at(head, 0) == 6);
}

void test_push_front(){
   Node *head = 0x0;
   push_front(&head, 1);
   push_front(&head, 2);
   push_front(&head, 3);
   push_front(&head, 4);
   push_front(&head, 5);
   assert(size(head) == 5);
   assert(value_at(head, 0) == 5);
   assert(value_at(head, 1) == 4);
   assert(value_at(head, 2) == 3);
   assert(value_at(head, 3) == 2);
   assert(value_at(head, 4) == 1);
}

void test_empty(){
  Node *head = 0x0;
  assert( empty(head) == TRUE);
  push_front(&head, 5);
  assert( empty(head) == FALSE);
}


void test_value_n_from_end() {
  Node *head = 0x0;
  push_back(&head, 1);
  push_back(&head, 2);
  push_back(&head, 3);
  push_back(&head, 4);
  push_back(&head, 5);
  assert(value_n_from_end(head, 1) == 5);
  assert(value_n_from_end(head, 3) == 3);
  assert(value_n_from_end(head, 5) == 1);
}









