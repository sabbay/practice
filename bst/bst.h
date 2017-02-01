#ifndef BST_H
#define BST_H
#define TRUE 1
#define FALSE 0
typedef unsigned char bool;


typedef struct Node Node;

struct Node{
  int key;
  Node *parent;
  Node *left_child;
  Node *right_child;
} *Root;


void insert(Node **root, int key );
Node *new_node(Node *paernt, Node *left_child, Node *right_child, int key);
void inorder_walk(Node *root);
void postorder_walk(Node *root);
void preorder_walk(Node *root);
int tree_value_sum(Node *root);
void delete_tree(Node *root);
bool in_tree(Node *root, int key);
Node *get_node(Node *root, int key);
int get_height(Node *root);
int get_min(Node *root);
int get_max(Node *root);
bool is_binary_search_tree(Node *root);
bool is_bst_util(Node *root, int min, int max);
int get_sucessor(Node *root, int key);
int get_predecessor(Node *root, int key);
void delete(Node **root, int key);



void test_get_precedessor();
void test_is_bin();
void test_all();
void test_get_node();
void test_min();
void test_max();
void test_insert();
void test_tree_value_sum();
void test_sucessor();
void test_in_tree();
void test_delete();
void test_height();

#endif /* BST_H */
