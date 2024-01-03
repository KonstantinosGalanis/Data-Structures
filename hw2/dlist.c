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

dnode *find_target(dnode *low,dnode *high) {
    if(low==high) {
        return low;
    }
    
    int value;
    dnode *pivot=high,*curr=low,*temp=high->prev,*point1=NULL,*point2=NULL;
    high=high->prev;
    
    while(1) {
        while(curr!=NULL) {
            if(curr->data>pivot->data && curr->data!=temp->data) {
                point1=curr;
                break;
            }
            if(curr->data==high->data && curr->data<high->next->data) {
                return curr->next;
            }
            if(curr->data==temp->data) {
                value=pivot->data;
                pivot->data=curr->data;
                curr->data=value;
                return curr;
            }
            curr=curr->next;
        }
        while(temp!=NULL && temp!=low) {
            if(temp->data<pivot->data && temp->data!=curr->data) {
                point2=temp;
                break;
            }
            temp=temp->prev;
            if(temp->data==curr->data) {
                value=pivot->data;
                pivot->data=temp->data;
                temp->data=value;
                return temp;
            }
        }
        value=point1->data;
        point1->data=point2->data;
        point2->data=value;
    }
    
    return curr->next; 
}
void print_list3(dnode *print_start,int cnt,int sorted,int size) {
    int i;
    
    for(i=0;i<cnt;i++) {
        printf("== ");
    }
    
    if(sorted==-1) {
        printf("[%d >] ",cnt);
    }
    else if(sorted==1) {
        printf("[%d <] ",cnt);
    }
    
    while(print_start!=NULL) {
        printf("%d ",print_start->data);
        print_start=print_start->next;
    } 
    printf("\n");
}

dnode *split(dnode *node,int size) {
    int n=0;
    int len=size/2;
    struct dlist_node *temp=node,*curr=node; 
    while (temp->next && temp->next->next && n<len-1) { 
        temp=temp->next->next; 
        curr=curr->next; 
        n++;
    } 

    struct dlist_node *j=curr->next; 
    curr->next=NULL; 
    return j; 
}

dnode *merge(dnode *a,dnode *b) {
    if(a==NULL) {
        return b;
    }

    if(b==NULL) {
        return a;
    }

    if(a->data<=b->data) {
        a->next=merge(a->next,b);
        a->next->prev=a;
        a->prev=NULL;
        return a;
    }
    else {
        b->next=merge(a,b->next);
        b->next->prev=b;
        b->prev=NULL;
        return b;
    }
}

int find_size(dnode *a) {
    int i=0;
    
    while(a!=NULL) {
        i++;
        a=a->next;
    }
    return i;
}

dnode *merge_sort(dnode *node,int cnt,int sorted) {
    int value;
    int size;
    
    size=find_size(node);
    print_list3(node,cnt,sorted=-1,size);
    
    if(size==1) {
        print_list3(node,cnt,sorted=1,size);
        return node;
    }
    
    if(size==2) {
        if(node->data>node->next->data) {
            value=node->next->data;
            node->next->data=node->data;
            node->data=value;
        }
        print_list3(node,cnt,sorted=1,size);
        return node;
    }

    struct dlist_node *b=split(node,size);
    node=merge_sort(node,++cnt,sorted);
    cnt--;
    b=merge_sort(b,++cnt,sorted);
    node=merge(node,b);
    cnt--;
    print_list3(node,cnt,sorted=1,size);
    return node;
}

void buckets_create(dlist **list) {
    (*list)=(dlist *)malloc(sizeof(dlist));
    if(!list){
        exit(-1);
    }
    (*list)->head=NULL;
    (*list)->size=0;
}

void print_list4(dnode *node,int cnt,int n,int curr) {
    if(node==NULL) {
        return ;
    }
    
    int i,h;
    
    for(i=0;i<cnt;i++) {
        printf("== ");
    }
    
    printf("[%d, %d] ",cnt,curr);
    printf("(");
    for(h=1<<(n-1);h>0;h=h/2) {
        (curr&h) ? printf("1") : printf("0");
    }
    printf(") ");
    while(node!=NULL) {
        printf("%d ",node->data);
        node=node->next;
    }
    printf("\n");
}

dnode *merge_lsd(dnode *a,dnode *b) {
    if(a==NULL) {
        return b;
    }

    if(b==NULL) {
        return a;
    }

    
    a->next=merge_lsd(a->next,b);
    a->next->prev=a;
    a->prev=NULL;
    return a;
}

void print_list5(dnode *node,int n,int curr) {
    if(node==NULL) {
        return ;
    }
    
    int h;
    
    while(node!=NULL) {
        printf("%d",node->data);
        printf("(");
        for(h=1<<(n-1);h>0;h=h/2) {
            (curr&h) ? printf("1") : printf("0");
        }
        printf(") ");
        node=node->next;
    }
}