#include <stdlib.h>
#include "fifo.h"

slist *fifo_create(slist *list) {
    slist *temp=(slist *)malloc(sizeof(slist));
    if(!temp){
        exit(-1);
    }
    temp->head=NULL;
    temp->size=0;
    return temp;
}

void enqueue(slist *list,int data) {
    snode *new_node=(snode *)malloc(sizeof(snode));
    snode *temp;
    if(new_node==NULL){
        exit(-1);
    }
    else{
        new_node->data=data;
        if(list->head==NULL) {
            new_node->next=NULL;
            list->head=new_node;
            list->size++;
            return;
        }
        else {
            temp=list->head;
            while(temp!=NULL && temp->next!=NULL) {
                temp=temp->next;
            }
            temp->next=new_node;
        }
    }

    list->size++;
}

void dequeue(slist *list) {
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

