#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc,char *argv[]) {
    struct btree *btree;
    struct bt_node *temp;
    int num,i=0,*preorder,n,len1=0;
    
    btree=tree_create();
    preorder=malloc(4*sizeof(char));
    while(1){
        scanf(" %d",&num);
        if(num<0) {
            break;
        }
        preorder[i]=num;
        i++;
        preorder=realloc(preorder,(4+4*i)*sizeof(char));
    }
    
    btree->root=construct_tree_pre(preorder,0,i-1);
    printf("Enter integer: ");
    scanf("%d",&n);
    temp=find_node(btree->root,n,&len1);
    if(temp==NULL) {
        printf("%d not found!\n",n);
        return 0;
    }
    else {
        printf("\nintegers in level %d are: ",len1);
        print_at_level(btree->root,len1,0);
    }
    printf("\n");
    clear_tree(btree->root);
    free(btree);
    free(preorder);
    return 0;
}