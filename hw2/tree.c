#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void clear_tree(node *root) {
    if(!root) {
        return;
    }
    clear_tree(root->left);
    clear_tree(root->right);
    free(root);
}

tree *tree_create() {
    tree *btree=(tree *)malloc(sizeof(tree));
    
    if(!btree) {
        exit(-1);
    }
    btree->root=NULL;
    return btree;
} 

node *construct_tree_pre(int preorder[],int start,int end) {
    int i;
    
    if(start>end) {
        return NULL;
    }
    
    node *root=(node *)malloc(sizeof(node));
    root->value=preorder[start];
    root->left=root->right=NULL;
    
    for(i=start;i<=end;i++) {
        if(preorder[i]>root->value) {
            break;
        }
    }
    
    root->left=construct_tree_pre(preorder,start+1,i-1);
    root->right=construct_tree_pre(preorder,i,end);
    return root;
}

node *find_node(node *root,int value,int *size) {
    if(root==NULL || root->value==value) {
        return root;
    }
    else if(value>root->value) {
        (*size)++;
        return find_node(root->right,value,size);
    }
    else {
        (*size)++;
        return find_node(root->left,value,size);
    }
}

void print_at_level(node *root, int len1, int start) {
    if(root!=NULL) {
        if(len1==start)
            printf("%d ",root->value);
        else {
            print_at_level(root->left,len1,start+1);
            print_at_level(root->right,len1,start+1);
        }
    }
}

node *new_node(int data) { 
    node *root=malloc(sizeof(struct bt_node)); 
    root->value=data; 
    root->left=NULL; 
    root->right=NULL; 
  
    return root; 
} 

node *contruct_bal_tree(int array[],int first,int last) {
    if(first>last) {
        return NULL;
    }
    
    int half=(last+first)/2;
    node *root=new_node(array[half]);
    root->left=contruct_bal_tree(array,first,half-1);
    root->right=contruct_bal_tree(array,half+1,last);
    return root;
}

void preorder(node *root) {
    if(root!=NULL) {
        printf("%d ",root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void insertion_sort(int array[],int size) { 
    int i,key,j; 
    for(i=1;i<size;i++) { 
        key=array[i]; 
        j=i-1; 
        while(j>=0 && array[j]>key) { 
            array[j+1]=array[j]; 
            j=j-1; 
        } 
        array[j+1]=key; 
    } 
}