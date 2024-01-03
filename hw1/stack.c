#include <stdlib.h>
#include "stack.h"

slist *stack_create(slist *list) {
    slist *temp=(slist *)malloc(sizeof(slist));
    if(!temp){
        exit(-1);
    }
    temp->head=NULL;
    temp->size=0;
    return temp;
}

int isEmpty(slist *list){
    if(list->head==NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void push(slist *list,int data) {
    snode *new_node=(snode *)malloc(sizeof(snode));
    
    if(new_node==NULL){
        exit(-1);
    }
    else{
        new_node->data=data;
        new_node->next=list->head;
        list->head=new_node;
    }
    list->size++;
}

void pop(slist *list) {
    snode *temp;

    if(list->head==NULL) {
        return;
    }

    temp=list->head;
    list->head=list->head->next;
    free(temp);
    list->size--;
    return;
}

snode *top(slist *list){
    return list->head;
}