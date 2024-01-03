#ifndef __SLIST_H_
#define __SLIST_H_
#include <stdio.h>

typedef struct slist_node {
    struct slist_node* next;
    int data;
} snode;
    
typedef struct slist {
    struct slist_node *head;
    int size;
} slist;

/*the main function*/
extern int main(); 

/*creates and initializes the fifo*/
extern slist *fifo_create();

/*adds to the end*/
extern void enqueue(); 

/*removes from the start*/
extern void dequeue(); 

#endif