#ifndef __DLIST_H_
#define __DLIST_H_
#include <stdio.h>

typedef struct dlist_node {
    struct dlist_node* next;  
    struct dlist_node* prev;  
    int data;
} dnode;
    
typedef struct dlist {
    struct dlist_node *head, *tail;
    int size;
} dlist;

/*the main function*/
extern int main(); 

/*creates and initializes the dlist*/
extern dlist *dlist_create();

/*adds to the dlist*/
extern void dlist_insert(); 

/*removes from the dlist*/
extern void dlist_delete(); 

/*searches in the dlist*/
extern dnode *dlist_search(); 

#endif