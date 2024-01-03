#include <stdlib.h>
#include "dlist.h"

dlist *dlist_create(dlist *list) {
    dlist *temp=(dlist *)malloc(sizeof(dlist));
    if(!temp){
        exit(-1);
    }
    temp->head=NULL;
    temp->tail=NULL;
    temp->size=0;
    return temp;
}

void dlist_insert(dlist *list,int data) {
    dnode *new_node=(dnode *)malloc(sizeof(dnode));
    dnode *last=list->head;
        
    new_node->data=data;
    new_node->next=NULL;

    if(list->head==NULL) {
        new_node->prev=NULL;
        list->head=new_node;
        list->size++;
        return;
    }
        
    while(last->next != NULL) { 
        last=last->next;
    }

    last->next=new_node;
    new_node->prev=last;
    list->size++;
    return;
}

void dlist_delete(dlist *list,dnode *del) {
    if(list->head==NULL || del==NULL){
        return;
    }
        
    if(list->head==del){
        list->head=del->next;
    }

    if(del->next!=NULL){
        del->next->prev=del->prev;
    }

    if(del->prev!=NULL){
        del->prev->next=del->next;
    }

    list->size--;
    free(del);
    return;
}

dnode *dlist_search(dlist *list,int data) {
    dnode *temp=(dnode *)malloc(sizeof(dnode));
    temp=list->head;
    while(temp!=NULL) {
        if(temp->data==data) {
            return temp;
        }
        else{
            temp=temp->next;
        }
    }
    return 0;
}

