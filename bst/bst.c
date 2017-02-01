#include "bst.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>



void delete(Node **root, int key){
  Node *to_delete = get_node(*root, key);
  if(to_delete == 0x0){
    printf("Node with key %d doesnt exist...\n", key);
    return;
  }
  if(to_delete->right_child == 0x0 && to_delete->left_child){ //a node with a single left child
    if(to_delete->parent != 0x0){ // isnt a root
      if(to_delete->parent->left_child == to_delete){ // is a left child
        to_delete->parent->left_child = to_delete->left_child; // so i link its partent left child to its left child
        free(to_delete);
      }else{ // is a right child
        to_delete->parent->right_child = to_delete->left_child; // so i link its parent left child to its right child
        free(to_delete);
      }
    }else{ //is a root
      *root = to_delete->left_child; // so the root now becomes its left child
      free(to_delete);
    }
  }else if(to_delete->left_child == 0x0 && to_delete->right_child){ // a node with a single right child
    if(to_delete->parent != 0x0){// isnt a root
      if(to_delete->parent->left_child == to_delete){ //is a left child
        to_delete->parent->left_child = to_delete->right_child; // so i link its parent left child to its right child
        free(to_delete);
      }else{//is a right child
        to_delete->parent->right_child = to_delete->right_child;// so i link its parent right child to its right child
        free(to_delete);
      }
    }
    else{ // is a root
      *root = to_delete->right_child;// so the root now becomes its right child
      free(to_delete);
    }
  }else if(to_delete->right_child == 0x0 && to_delete->left_child == 0x0){ // is a leaf
    if(to_delete->parent != 0x0){// isnt a root
      if(to_delete->parent->left_child == to_delete){// is a left child
        to_delete->parent->left_child = 0x0;// so i link its parent left child to 0x0
        free(to_delete);
      }else{// is a right child
        to_delete->parent->right_child = 0x0;// so i link its parent right child to 0x0
        free(to_delete);
      }
    }else{// is a root
      *root = 0x0;// so root is now 0x0
      free(to_delete);
    }
  }else{ // has two children
    Node *sucessor = get_node(*root, get_sucessor(*root, key));
    int suc_key = sucessor->key;// storing sucessors key
    delete(root, sucessor->key);// delete sucessor (has to be either a leaf or has one child)
    to_delete->key = suc_key;// swapping values with sucessor
  }
}

void insert(Node** root, int key) {
  if((*root) == 0x0){
    (*root) = new_node(0x0, 0x0, 0x0, key); // tree is empty
  }else if(key < (*root)->key){
    //proceed left
    if((*root)->left_child == 0x0){
      (*root)->left_child = new_node((*root), 0x0, 0x0, key);
      //no child, we insert new node
    }else{
      //proceed
      insert(&(*root)->left_child, key);
    }
  }else if(key > (*root)->key){ // we dont allow repetitions 
    //proceed right
    if((*root)->right_child == 0x0){
      //no child, we insert new node
      (*root)->right_child = new_node((*root), 0x0, 0x0, key);
    }else{
      //proceed
      insert(&(*root)->right_child, key);
    }
  }else{
    printf("Key already exists...\n");
  }
}


Node *get_node(Node *root, int key){
  if(root == 0x0){
    return 0x0;
  }else if(key == root->key){
    return root;
  }else if(key < root->key){
    return get_node(root->left_child, key);
  }else if(key > root->key){
    return get_node(root->right_child, key);
  }
}

bool in_tree(Node* root, int key) {
  if(root == 0x0){
    return FALSE;
  }else if(key == root->key){
    return TRUE;
  }else if(key < root->key){
    return in_tree(root->left_child, key);
  }else if(key > root->key){
    return in_tree(root->right_child, key);
  }
}

Node *new_node(Node *parent, Node *left_child, Node *right_child, int key){
  Node *tmp =calloc(1, sizeof(Node));
  tmp->parent = parent;
  tmp->left_child = left_child;
  tmp->right_child = right_child;
  tmp->key = key;
  return tmp;
}

int get_min(Node *root){
  Node *cur = root;
  if(root == 0x0){
    printf("invalid");
    exit(-1);
  }
  while(cur->left_child != 0x0){
    cur = cur->left_child;
  }
  return cur->key;
}

int get_max(Node *root){
  Node *cur = root;
  if(root == 0x0){
    printf("invalid");
    exit(-1);
  }
  while(cur->right_child != 0x0){
    cur = cur->right_child;
  }
  return cur->key;
}

int get_height(Node *root){
  if(root == 0x0){
    return 0;
  }else{
    int a = get_height(root->right_child);
    int b = get_height(root->left_child);
    if(a > b){
      return a+1;
    }else{
      return b+1;
    }
  }
}



int get_predecessor(Node *root, int key){
  Node *cur = get_node(root, key);

  if(root->parent == 0x0  && root->left_child == 0x0){ // for a tree consisting of a single node its sucessor is its only node
    return root->key;
  }
  if(key == get_min(root)){
    return cur->key;
  }
  if(cur->left_child != 0x0){
    return get_max(cur->left_child);
  }
  Node *parent = cur->parent;

  while (parent != 0x0 && cur == parent->left_child){
    cur = parent;
    parent = parent->parent;
  }
  return parent->key;
}

int get_sucessor(Node *root, int key){
  Node *cur = get_node(root, key);
  if(root == 0x0){
    printf("invalid root");
    exit(-1);
  }

  if(root->parent == 0x0  && root->right_child == 0x0){ // for a tree consisting of a single node its sucessor is its only node
    return root->key;
  }
  if(key == get_max(root)){
    return cur->key;
  }
  if(cur->right_child != 0x0){
    return get_min(cur->right_child);
  }
  Node *parent = cur->parent;

  while( parent != 0x0 && cur == parent->right_child){
    cur = parent;
    parent = parent->parent;
  }
  return parent->key;
}


bool is_binary_search_tree(Node *root){
  return is_bst_util(root, INT_MIN, INT_MAX);
}

bool is_bst_util(Node *root, int min, int max){
  if(root == 0x0){
    return TRUE;
  }
  if(root->key > min && root->key < max && is_bst_util(root->left_child, min, root->key) && is_bst_util(root->right_child, root->key, max)){
    return TRUE;
  }else{
    return FALSE;
  }
}

int tree_value_sum(Node* root) {
  if(root == 0x0){
    return 0;
  }else{
    int sum =0;
    sum += root->key;
    sum += tree_value_sum(root->left_child);
    sum += tree_value_sum(root->right_child);
    return sum;
  }
}


void delete_tree(Node* root) {
  if(root != 0x0){
    delete_tree(root->left_child);
    delete_tree(root->right_child);
    free(root);
  }
}



void inorder_walk(Node *root){
  if(root != 0x0 ){
    inorder_walk(root->left_child);
    printf(" %d ", root->key);
    inorder_walk(root->right_child);
  }
}


void postorder_walk(Node* root) {
  if(root != 0x0){
    postorder_walk(root->left_child);
    postorder_walk(root->right_child);
    printf(" %d ", root->key);
  }
}


void preorder_walk(Node* root) {
  if(root != 0x0){
    printf(" %d ", root->key);
    inorder_walk(root->left_child);
    inorder_walk(root->right_child);
  }
}

void test_all(){
  test_in_tree();
  test_insert();
  test_tree_value_sum();
  test_min();
  test_max();
  test_is_bin();
  test_get_node();
  test_sucessor();
  test_get_precedessor();
  test_height();
  test_delete();
}

void test_height(){
  Root = 0x0;
  assert(get_height(Root) == 0);
  insert(&Root, 10);
  assert(get_height(Root) == 1);
  insert(&Root, 9);
  insert(&Root, 8);
  insert(&Root, 7);
  insert(&Root, 6);
  insert(&Root, 5);
  insert(&Root, 4);
  assert(get_height(Root) == 7);
  insert(&Root, 11);
  insert(&Root, 12);
  insert(&Root, 15);
  insert(&Root, 14);
  insert(&Root, 13);
  assert(get_height(Root) == 7);
  insert(&Root, 16);
  insert(&Root, 17);
  insert(&Root, 18);
  insert(&Root, 19);
  assert(get_height(Root) == 8);
}

void test_delete(){
  Root = 0x0;
  insert(&Root, 10);
  delete(&Root, 10);
  assert(Root == 0x0);

  insert(&Root, 10);
  insert(&Root, 11);
  delete(&Root, 10);
  assert(Root->key == 11);
  assert(Root->left_child == 0x0);
  assert(Root->right_child == 0x0);
  delete_tree(Root);

  Root = 0x0;
  insert(&Root, 10);
  insert(&Root, 11);
  insert(&Root, 12);
  delete(&Root, 12);
  delete_tree(Root);

  Root = 0x0;
  insert(&Root, 10);
  insert(&Root, 11);
  insert(&Root, 9);
  delete(&Root, 10);
  inorder_walk(Root);
  printf("\n");
  assert(Root->key == 11);
  assert(Root->left_child->key == 9);

  delete_tree(Root);
  Root = 0x0;

  insert(&Root, 10);
  insert(&Root, 12);
  insert(&Root, 9);
  insert(&Root, 7);
  insert(&Root, 8);
  insert(&Root, 11);
  insert(&Root, 13);
  delete(&Root, 11);
  printf("\n");
  printf("\n");
  inorder_walk(Root);
  printf("\n");
  preorder_walk(Root);
  printf("\n");
  assert(in_tree(Root, 11) == FALSE);

}

void test_get_precedessor(){
  Root = 0x0;
  insert(&Root, 8);
  assert(get_predecessor(Root, 8) == 8);
  insert(&Root, 10);
  insert(&Root, 20);
  insert(&Root, 12);
  insert(&Root, 18);
  insert(&Root, 7);
  insert(&Root, 3);
  insert(&Root, 2);
  insert(&Root, 1);
  insert(&Root, 5);
  assert(get_predecessor(Root, 1) == 1);
  assert(get_predecessor(Root, 2) == 1);
  assert(get_predecessor(Root, 3) == 2);
  assert(get_predecessor(Root, 5) == 3);
  assert(get_predecessor(Root, 7) == 5);
  assert(get_predecessor(Root, 8) == 7);
  assert(get_predecessor(Root, 10) == 8);
  assert(get_predecessor(Root, 12) == 10);
  assert(get_predecessor(Root, 18) == 12);
  assert(get_predecessor(Root, 20) == 18);
}

void test_sucessor(){
  Root = 0x0;
  insert(&Root, 8);
  assert(get_sucessor(Root, 8) == 8);
  insert(&Root, 4);
  insert(&Root, 11);
  insert(&Root, 2);
  insert(&Root, 12);
  insert(&Root, 9);
  assert(get_sucessor(Root, 4) == 8);
  assert(get_sucessor(Root, 8) == 9);
  assert(get_sucessor(Root, 11) == 12);
  assert(get_sucessor(Root, 2) == 4);
  assert(get_sucessor(Root, 12) == 12);
}



void test_max(){
  Root = 0x0;
  insert(&Root, 5);
  insert(&Root, 4);
  insert(&Root, 3);
  insert(&Root, 2);
  insert(&Root, 1);
  assert(get_max(Root) == 5);
  insert(&Root, 10);
  assert(get_max(Root) == 10);
}

void test_is_bin(){
  Root = 0x0;
  assert(is_binary_search_tree(Root) == TRUE);
  insert(&Root, 2);
  assert(is_binary_search_tree(Root) == TRUE);
  insert(&Root, 3);
  assert(is_binary_search_tree(Root) == TRUE);
  insert(&Root, 1);
  assert(is_binary_search_tree(Root) == TRUE);

  delete_tree(Root);
  Root = 0x0;
  insert(&Root, 5);
  insert(&Root, 4);
  insert(&Root, 6);
  insert(&Root, 7);
  get_node(Root, 6)->left_child = new_node(get_node(Root, 6), 0x0, 0x0, 1);
  /* Node *kups = new_node(Root, 0x0, 0x0, 10); */
  /* Root->left_child = kups; */
  assert(is_binary_search_tree(Root) == FALSE);


  delete_tree(Root);
  Root = 0x0;
  insert(&Root, 5);
  insert(&Root, 4);
  insert(&Root, 6);
  insert(&Root, 7);
  get_node(Root, 4)->left_child = new_node(get_node(Root, 4), 0x0, 0x0, 10);
  /* Node *kups = new_node(Root, 0x0, 0x0, 10); */
  /* Root->left_child = kups; */
  assert(is_binary_search_tree(Root) == FALSE);

}


void test_get_node(){
  Root =0x0;
  assert(get_node(Root, 10) == 0x0);
  insert(&Root, 10);
  insert(&Root, 11);
  insert(&Root, 12);
  insert(&Root, 9);
  insert(&Root, 8);
  assert(get_node(Root, 10)->key == 10);
}

void test_min(){
  Root = 0x0;
  insert(&Root, 5);
  insert(&Root, 4);
  insert(&Root, 3);
  insert(&Root, 2);
  insert(&Root, 1);
  insert(&Root, 10);
  assert(get_min(Root) == 1);
}


void test_in_tree(){
  Root = 0x0;
  insert(&Root, 5);
  insert(&Root, 4);
  insert(&Root, 3);
  insert(&Root, 2);
  insert(&Root, 1);
  insert(&Root, 10);
  assert(in_tree(Root, 5) == TRUE );
  assert(in_tree(Root, 4) == TRUE);
  assert(in_tree(Root, 3) == TRUE);
  assert(in_tree(Root, 2) == TRUE);
  assert(in_tree(Root, 10) == TRUE);
  assert(in_tree(Root, 11) == FALSE);
}


void test_tree_value_sum(){
  Root = 0x0;
  insert(&Root, 5);
  insert(&Root, 4);
  insert(&Root, 3);
  insert(&Root, 2);
  insert(&Root, 1);
  assert(tree_value_sum(Root) ==  15);
  insert(&Root, 10);
  assert(tree_value_sum(Root) ==  25);
}

void test_insert(){
  Root = 0x0;
  insert(&Root, 5);
  insert(&Root, 10);
  insert(&Root, 15);
  insert(&Root, 3);
  insert(&Root, 2);
  insert(&Root, 1);
  inorder_walk(Root);
  printf("\n");
  preorder_walk(Root);
  printf("\n");
  postorder_walk(Root);
  printf("\n");
  delete_tree(Root);
}
