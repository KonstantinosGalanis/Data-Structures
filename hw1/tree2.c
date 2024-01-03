#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc,char *argv[]) {
    struct btree *btree;
    int num,size=0,*levelorder,res,min,max;
    
    btree=tree_create();
    levelorder=malloc(4*sizeof(char));
    while(1){
        scanf(" %d",&num);
        if(num<0) {
            break;
        }
        if(size==0) {
            min=num;
            max=num;
        }
        else {
            if(num<min) {
                min=num;
            }
            if(num>max) {
                max=num;
            }
        }
        levelorder[size]=num;
        size++;
        levelorder=realloc(levelorder,(4+4*size)*sizeof(char));
    }
    
    btree->root=construct_tree_level(levelorder,btree->root,0,size);
    res=check_if_bst(btree->root,min,max);
    
    if(res==1){
        printf("Binary Search Tree\n");
    }
    else {
        printf("Binary Tree\n");
    }
    clear_tree(btree->root);
    free(btree);
    free(levelorder);
    return 0;
}