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

/*construct tree given postorder*/
extern node *construct_tree_post(); 

/*prints all nodes in the given level*/
extern void print_given_level();

/*prints the tree in level order*/
extern void print_level_order();

/*constructs tree given levelorder*/
extern node *construct_tree_level();

/*checks if tree a bst*/
extern int check_if_bst();

/*finds node if exist*/
extern node *find_node();

/*construct tree given preorder*/
extern node *construct_tree_pre();

/*saves the path of given node from root into an array*/
extern int *get_path();

/*prints the path*/
extern void print_path();

/*deallocates the nodes*/
extern void clear_tree();

#endif