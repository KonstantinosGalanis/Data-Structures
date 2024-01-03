#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

void clear(dlist *list1) {
    while(1) {
        if(list1->head->prev==NULL) {
            break;
        }
        list1->head=list1->head->prev;
    }
    struct dlist_node *curr=list1->head;
    while(curr!=NULL) {
        curr=list1->head->next;
        free(list1->head);
        list1->head=curr;
    }
    free(curr);
    free(list1);
}

int *subsequence_with_zero_sum(struct dlist *list1,int size,int temp[]) {
    int arr[size],i,sum=0,j,max_lenght=-1;
    struct dlist_node *curr=list1->head;
    
    for(i=0;i<size;i++) {
        sum+=curr->data;
        for(j=0;j<i;j++) {
            if(sum==arr[j] && max_lenght<i-j) {
                temp[0]=j+1;
                temp[1]=i;
                max_lenght=i-j+1;
                break;
            }
        }
        arr[i]=sum;
        curr=curr->next;
    }
    return temp;
}

int main(int argc, char *argv[]) {
    struct dlist *list1=NULL;
    int num,size=0,*temp,start,stop,max_lenght,i;
    
    temp=calloc(2,sizeof(int));
    list1=dlist_create(list1);
    
    while(1) {
        scanf(" %d",&num);
        if(num==0) {
            break;
        }
        dlist_insert(list1,num);
        size++;
    }

    temp=subsequence_with_zero_sum(list1,size,temp);
    start=temp[0];
    stop=temp[1];
    max_lenght=stop-start+1;
    printf("start: %d, stop: %d, size: %d\n",start,stop,max_lenght);
    for(i=0;i<start;i++){
        list1->head=list1->head->next;
    }
    for(i=start;i<=stop;i++){
        printf("%d ",list1->head->data);
        list1->head=list1->head->next;
    }
    printf("\n");
    clear(list1);
    free(temp);
    return 0;
}