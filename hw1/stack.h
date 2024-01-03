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

/*creates and initializes the slist*/
extern slist *stack_create();

/*tells us if stack is empty or not*/ 
extern int isEmpty();

/*adds to the stack*/
extern void push(); 

/*removes from the stack*/
extern void pop(); 

/*returns the top element*/
extern snode *top();

#endif