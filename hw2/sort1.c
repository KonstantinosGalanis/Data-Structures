#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dlist.h"
#include "sort.h"

dnode *radix_sort_lsd(dnode *node,dlist **buckets,int n,int cnt) {
    if(node==NULL) {
        return NULL;
    }
    
    int index,i,j;
    dnode *temp=node;
    
    for(i=0;i<32/n;i++){
        while(temp!=NULL) {
            index=(temp->data>>(n*cnt)) & ((1<<n)-1);
            dlist_insert(buckets[index],temp->data);
            temp=temp->next;
        }
        printf(" [%d] ",cnt);
        for(j=0;j<pow(2,n);j++) {
            print_list5(buckets[j]->head,n,j);
        }
        printf("\n");
        for(j=0;j<pow(2,n)-1;j++) {
            buckets[j+1]->head=merge_lsd(buckets[j]->head,buckets[j+1]->head);
        }
        temp=buckets[j]->head;
        cnt++;
        for(j=0;j<pow(2,n);j++) {
            if(buckets[j]->head==NULL) {
                continue;
            }
            struct dlist_node *curr=buckets[j]->head;
            while(curr!=NULL) {
                curr=buckets[j]->head->next;
                buckets[j]->head=NULL;
                buckets[j]->head=curr;
            }
            free(curr);
        }
    }
    
    return temp;
}

dnode *radix_sort_msd(dnode *node,int n,int cnt) {
    if(node==NULL) {
        return NULL;
    }
    
    int index,i;
    dlist **buckets;
    dnode *temp=node;
    
    buckets=(dlist **)malloc((pow(2,n))*sizeof(dlist *));
    for(i=0;i<pow(2,n);i++) {
        buckets_create(&buckets[i]);
    }
    
    while(temp!=NULL) {
        index=(temp->data>>(32-n*cnt)) & ((1<<n)-1);
        dlist_insert(buckets[index],temp->data);
        temp=temp->next;
    }
    for(i=0;i<pow(2,n);i++) {
        print_list4(buckets[i]->head,cnt,n,i);
        if(buckets[i]->head!=NULL && buckets[i]->head->next!=NULL) {
            buckets[i]->head=radix_sort_msd(buckets[i]->head,n,cnt+1);
        }
    }
    
    for(i=0;i<pow(2,n)-1;i++) {
        buckets[i+1]->head=merge(buckets[i]->head,buckets[i+1]->head);
    }
    
    return buckets[i]->head;
}

int main(int argc, char *argv[]) {   
    struct dlist *list1=NULL,**buckets;
    struct dlist_node *temp=NULL;
    int num,size=0,i,cnt=0,sorted=0;
    
    list1=dlist_create(list1);
    
    while(1) {
        scanf(" %d",&num);
        if(num<0) {
            break;
        }
        dlist_insert(list1,num);
        size++;
    }
    temp=list1->head;
    for(i=0;i<size;i++) {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
    printf("\n");
    
    if(atoi(argv[1])<0 || atoi(argv[1])>6) {
        printf("Invalid argument\n");
        return 0;
    }

    if((atoi(argv[1])==5 || atoi(argv[1])==6) && ((argc!=3) || (atoi(argv[2])!=1 && atoi(argv[2])!=2 && atoi(argv[2])!=4 && atoi(argv[2])!=8 && atoi(argv[2])!=16))) {
        printf("Invalid argument\n");
        return 0;
    }

    if(atoi(argv[1])==1) {
        insertion_sort(list1);
        temp=list1->head;
        printf("\n");
        for(i=0;i<size;i++) {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
    else if(atoi(argv[1])==2) {
        selection_sort(list1);
        temp=list1->head;
        printf("\n");
        for(i=0;i<size;i++) {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
    else if(atoi(argv[1])==3) {
        temp=list1->head;
        do{
            temp=temp->next;
        }while(temp->next!=NULL);
        quick_sort(list1->head,temp,cnt,sorted);
        temp=list1->head;
        printf("\n");
        for(i=0;i<size;i++) {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
    else if(atoi(argv[1])==4) {
        temp=list1->head;
        merge_sort(temp,cnt,sorted);
        printf("\n");
        while(temp->prev!=NULL){
            temp=temp->prev;
        }
        for(i=0;i<size;i++) {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
    else if(atoi(argv[1])==5) {
        list1->head=radix_sort_msd(list1->head,atoi(argv[2]),cnt=1);
        printf("\n");
        temp=list1->head;
        for(i=0;i<size;i++) {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
    else if(atoi(argv[1])==6) {
        buckets=(dlist **)malloc((pow(2,atoi(argv[2])))*sizeof(dlist *));
        for(i=0;i<pow(2,atoi(argv[2]));i++) {
            buckets_create(&buckets[i]);
        }
        list1->head=radix_sort_lsd(list1->head,buckets,atoi(argv[2]),cnt=0);
        printf("\n");
        temp=list1->head;
        for(i=0;i<size;i++) {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
    clear(list1);
    return 0;
}