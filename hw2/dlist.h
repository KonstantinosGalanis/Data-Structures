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

/*clears the list*/
extern void clear();

/*adds to the dlist*/
extern void dlist_insert(); 

/*removes from the dlist*/
extern void dlist_delete(); 

/*searches in the dlist*/
extern dnode *dlist_search(); 

/*finds and swaps the pivot*/
extern dnode *find_target();

/*prints the merge sort*/
extern void print_list3();

/*splits the list*/
extern dnode *split();

/*merges the list*/
extern dnode *merge();

/*finds the size of each sublist*/
extern int find_size();

/*func for merge sort*/
extern dnode *merge_sort();

/*func to make new buckets*/
extern void buckets_create();

/*prints the stages of radix_msd*/
extern void print_list4();

/*recursive func for radix msd*/
extern dnode *radix_sort_msd();

/*merge for lsd*/
extern dnode *merge_lsd();

/*print for lsd*/
extern void print_list5();

#endif
