#include <stdio.h>
#include "sort.h"
#include "dlist.h"

void print_list(dnode *print,int n) {
    
    printf(" [%d]: ",n);
    while(print!=NULL) {
        printf("%d ",print->data);
        print=print->next;
    } 
    printf("\n");
}

void insertion_sort(dlist *list1) {
    struct dlist_node *curr;
    int j,n=1;
    
    curr=list1->head;

    if(curr->next==NULL) {
        return;
    }
    
    struct dlist_node *ptr,*temp,*print;
    curr=curr->next;

    while(curr!=NULL) {
        j=0;
        ptr=curr;
        temp=curr->prev;
        curr=curr->next;
        
        while(temp!=NULL && temp->data>ptr->data) {
            temp=temp->prev;
            j++;
        }
        
        if(j) {
            ptr->prev->next=ptr->next;
            
            if(ptr->next!=NULL) {
                ptr->next->prev=ptr->prev;    
            }
            
            if(temp==NULL) {
                temp=list1->head;
                ptr->prev=NULL;
                ptr->next=temp;
                ptr->next->prev=ptr;
                list1->head=ptr;
            }
            else {
                temp=temp->next;
                temp->prev->next=ptr;
                ptr->prev=temp->prev;
                temp->prev=ptr;
                ptr->next=temp;
            }
        }
        print=list1->head;
        print_list(print,n);
        n++;
    }
}

void selection_sort(dlist *list1) {
    int value,n=1;
    dnode *temp=list1->head,*print;

    while(temp) {
        dnode *start=temp;
        dnode *r=temp->next;
         
        while(r) {
            if(start->data>r->data) {
                start=r;
            }
            r=r->next;
        }
        value=temp->data;
        temp->data=start->data;
        start->data=value;
        temp=temp->next;
        
        if(temp!=NULL) {
            print=list1->head;
            print_list(print,n);
            n++;
        }
    }
}

void print_list2(dnode *print_start,dnode *print_end,int cnt,int sorted) {
    int i;
    
    for(i=0;i<cnt;i++) {
        printf("== ");
    }
    
    if(sorted==-1) {
        printf("[%d >] ",cnt);
    }
    else if(sorted==0) {
        printf("[%d -] ",cnt);
    }
    else if(sorted==1) {
        printf("[%d <] ",cnt);
    }
    
    while(print_start!=print_end) {
        printf("%d ",print_start->data);
        print_start=print_start->next;
    } 
    printf("%d ",print_start->data);
    printf("\n");
}

void quick_sort(dnode *low,dnode *high,int cnt,int sorted) {
    dnode *target=NULL;
    
    if(high!=NULL && low!=high && low!=high->next) {
        print_list2(low,high,cnt,sorted=-1);
        target=find_target(low,high);
        if(low->next->data==high->data) {
            print_list2(low,high,cnt,sorted=1);
            return;
        }
        print_list2(low,high,cnt,sorted=0);
        quick_sort(low,target->prev,++cnt,sorted);
        cnt--;
        quick_sort(target->next,high,++cnt,sorted);
        cnt--;
        print_list2(low,high,cnt,sorted=1);
    }
}

