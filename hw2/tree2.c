#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc,char *argv[]) {
    struct btree *btree;
    int num,size=0,*array;
    
    btree=tree_create();
    array=malloc(4*sizeof(char));
    while(1){
        scanf(" %d",&num);
        if(num<0) {
            break;
        }
        array[size]=num;
        size++;
        array=realloc(array,(4+4*size)*sizeof(char));
    }
    insertion_sort(array,size);
    btree->root=contruct_bal_tree(array,0,size-1);
    preorder(btree->root);
    printf("\n");
    free(array);
    clear_tree(btree->root);
    free(btree);
    return 0;
}