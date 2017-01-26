#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <inttypes.h>

#define TRUE 1
#define FALSE 0

typedef uint8_t bool;
typedef struct Node Node;

typedef struct {
  Node *head;
  Node *tail;
  uint32_t size;
}List;

struct Node{
  int value;
  Node *next;
};

List new();
Node *copy_node(Node *node);
List copy_list(List *source, uint32_t index_start, uint32_t index_end);
uint16_t size(List *l);
bool empty(List *l);
int value_at(List *l, int index);
void push_front(List *l, int value);
int pop_front(List *l);
void push_back(List *l,int value);
int pop_back(List *l);
int front(List *l);
int back(List *l);
void insert(List *l, int index, int value);
void erase(List *l, int index);
int value_n_from_end(List *l, int n);
void reverse(List *l);
void remove_value(List *l, int value);
void print(List *l);

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
void test_copy_list();


#endif /* LINKED-LIST_H */
