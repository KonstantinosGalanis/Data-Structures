#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc,char *argv[]) {
    struct btree *btree;
    int num,size=0,*postorder;
    
    btree=tree_create();
    postorder=malloc(4*sizeof(char));
    while(1){
        scanf(" %d",&num);
        if(num<0) {
            break;
        }
        postorder[size]=num;
        size++;
        postorder=realloc(postorder,(4+4*size)*sizeof(char));
    }
    
    btree->root=construct_tree_post(postorder,0,size-1);
    print_level_order(btree->root,size);
    printf("\n");
    clear_tree(btree->root);
    free(btree);
    free(postorder);
    return 0;
}