#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <inttypes.h>

#define TRUE 1
#define FALSE 0

typedef uint8_t bool;
typedef struct Node Node;

struct Node{
  int value;
  Node *next;
}Head;

uint16_t size(Node *head); 
bool empty(Node *head);
int value_at(Node *head, int index);
void push_front(Node **head, int value);
int pop_front(Node **head);
void push_back(Node **head,int value);
int pop_back(Node **head);
int front(Node *head);
int back(Node *head);
void insert(Node **head, int index, int value);
void erase(Node **head, int index);
int value_n_from_end(Node *head, int n);
void reverse(Node **head);
void remove_value(Node **head, int value);
void print(Node *head);

void test_all();
void test_empty();
void test_size();
void test_value_at();
void test_push_front();
void test_pop_front();
void test_push_back();
void test_pop_back();
void test_front();
void test_back();
void test_insert();
void test_erase();
void test_value_n_from_end();
void test_reverse();
void test_remove_value();


#endif /* LINKED-LIST_H */
