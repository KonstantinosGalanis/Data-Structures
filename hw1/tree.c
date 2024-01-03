#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

tree *tree_create() {
    tree *btree=(tree *)malloc(sizeof(tree));
    
    if(!btree) {
        exit(-1);
    }
    btree->root=NULL;
    return btree;
}

node *construct_tree_post(int postorder[],int start,int end) {
    int i;
    
    if(start>end) {
        return NULL;
    }
    
    node *root=(node *)malloc(sizeof(node));
    root->value=postorder[end];
    root->left=root->right=NULL;
    
    for(i=end;i>=start;i--) {
        if(postorder[i]<root->value) {
            break;
        }
    }
    root->right=construct_tree_post(postorder,i+1,end-1);
    root->left=construct_tree_post(postorder,start,i);
    return root;
}

void print_given_level(node *bnode,int level) {
    if(bnode==NULL) {
        return;
    }
    
    if(level==0) {
        printf("%d ",bnode->value);
    }
    else if(level>0) {
        print_given_level(bnode->left,level-1);
        print_given_level(bnode->right,level-1);
    }
}

void print_level_order(node *bnode,int size) { 
    int max_height=size-1,i;
    
    for(i=0;i<max_height;i++) {
        print_given_level(bnode,i);
    }
}

node *construct_tree_level(int postorder[],node *root,int start,int end) {
    if(start<end) {
        node *bnode=(node *)malloc(sizeof(node));
        bnode->value=postorder[start];
        bnode->left=bnode->right=NULL;
        root=bnode;
        root->left=construct_tree_level(postorder,root->left,2*start+1,end);
        root->right=construct_tree_level(postorder,root->right,2*start+2,end);
    }
    
    return root;
}

int check_if_bst(node *root,int min,int max) {
    if(root==NULL) {
        return 1;
    }
    
    if(root->value<min || root->value>max) {
        return 0;
    }
    
    return check_if_bst(root->left,min,root->value+1) && check_if_bst(root->right,root->value+1,max);
}

node *find_node(node *root,int value,int *size) {
    if(root==NULL || root->value==value) {
        (*size)++;
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

int *get_path(node *root,int *path,int n1,int start,int end) {
    if(!root) {
        return NULL;
    }
    
    if(start<end) {
        path[start]=root->value;
    }
    
    if(root->value==n1) {
        
        return path;
    }
    
    if(get_path(root->left,path,n1,start+1,end) || get_path(root->right,path,n1,start+1,end)) {
        return path;
    }
    
    return NULL;
}

void print_path(node *root,int n1,int n2,int len1,int len2) {
    int *path1,*path2,touch=-1,i=0,j=0;
    path1=malloc(4*(len1+1)*sizeof(char));
    path2=malloc(4*(len2+1)*sizeof(char));
    path1=get_path(root,path1,n1,0,len1);
    path2=get_path(root,path2,n2,0,len2);
    
    while(i!=len1 || j!=len2) {
        if(i==j && path1[i]==path2[j]) {
            i++;
            j++;
        }
        else {
            touch=j-1;
            break;
        }
    }
    
    printf("\nPath is:");
    for(i=len1-1;i>touch;i--) {
        printf(" %d",path1[i]);
    }
    for(i=touch;i<len2;i++) {
        printf(" %d",path2[i]);
    }
    free(path1);
    free(path2);
}

void clear_tree(node *root) {
    if(!root) {
        return;
    }
    clear_tree(root->left);
    clear_tree(root->right);
    free(root);
}