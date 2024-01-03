#ifndef __TREE_H_
#define __TREE_H_
#include <stdio.h>

typedef struct bt_node {  
    struct bt_node* left;  
    struct bt_node* right;  
    int value;
} node;

typedef struct btree {  
    node* root;  
} tree;

/*creates the tree*/
extern tree *tree_create();

/*constructs a bst from preorder*/
extern node *construct_tree_pre();

/*finds node if exist*/
extern node *find_node();

/*prints all items in the same level*/
extern void print_at_level();

/*creates new node*/
extern node *new_node();

/*creates a balanced tree*/
extern node *contruct_bal_tree();

/*prints the preorder traversal of bst*/
extern void preorder();

extern void insertion_sort();

/*deallocates the nodes*/
extern void clear_tree();

#endif
