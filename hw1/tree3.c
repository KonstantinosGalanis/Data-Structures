#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc,char *argv[]) {
    struct btree *btree;
    struct bt_node *temp;
    int num,i=0,*preorder,n1,n2,len1=0,len2=0;
    
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
    printf("Enter 2 integers: ");
    scanf("%d %d",&n1,&n2);
    temp=find_node(btree->root,n1,&len1);
    if(temp==NULL) {
        printf("%d not found!\n",n1);
        return 0;
    }
    temp=find_node(btree->root,n2,&len2);
    if(temp==NULL) {
        printf("%d not found!\n",n2);
        return 0;
    }
    print_path(btree->root,n1,n2,len1,len2);
    printf("\n");
    clear_tree(btree->root);
    free(btree);
    free(preorder);
    return 0;
}

