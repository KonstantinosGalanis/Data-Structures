#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct bt_node {  
    struct bt_node* left;  
    struct bt_node* right;  
    int value;
    int height;
    double weight;
} node;

typedef struct btree {  
    node* root;  
} tree;

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

int count_nodes(node *root) {
    if(root==NULL) {
        return 0;
    }
    else {
        return 1+count_nodes(root->left)+count_nodes(root->right);
    }
}

int max(int a,int b) {
    return (a>b)?a:b;
}

int height(node *k) {
    if(k==NULL) {
        return 0;
    }

    return k->height;
}

node *new_node(int key) {
    node *root=(node *)malloc(sizeof(node));
    root->value=key;
    root->left=NULL;
    root->right=NULL;
    root->height=1;
    return (root);
}

node *right_rotate(node *root) {
    node *k=root->left;
    node *m=k->right;

    k->right=root;
    root->left=m;

    root->height=max(height(root->left),height(root->right))+1;
    k->height=max(height(k->left),height(k->right))+1;
    
    root->weight=count_nodes(root);
    k->weight=count_nodes(k);
    
    return k;
}

node *left_rotate(node *root) {
    node *k=root->right;
    node *m=k->left;

    k->left=root;
    root->right=m;

    root->height=max(height(root->left),height(root->right))+1;
    k->height=max(height(k->left),height(k->right))+1;
    
    root->weight=count_nodes(root);
    k->weight=count_nodes(k);
    
    return k;
}

int get_bal(node *k) {
    if(k==NULL) {
        return 0;
    }

    return height(k->left)-height(k->right);
}

node *insert_node(node *root,int key){
    if(root==NULL) {
        return (new_node(key));
    }

    if(key<root->value) {
        root->left=insert_node(root->left,key);
    }
    else if(key>root->value) {
        root->right=insert_node(root->right,key);
    }
    else {
        return root;
    }


    root->height=1+max(height(root->left),height(root->right));
    root->weight=count_nodes(root);
    
    int bal=get_bal(root);
    int weight=max(1,floor(log2(root->weight)));
    
    if(bal>weight && key<root->left->value) {
        return right_rotate(root);
    }

    if (bal<-weight && key>root->right->value) {
        return left_rotate(root);
    }

    if(bal>weight && key>root->left->value) {
        root->left=left_rotate(root->left);
        return right_rotate(root);
    }

    if(bal<-weight && key<root->right->value) {
        root->right=right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

node *min_val_node(node *temp) {
    node *curr=temp;
    
    while(curr->left!=NULL) {
        curr=curr->left;
    }
    
    return curr;
}

node *check_if_bst(node *root) {
    
    if(root==NULL) {
        return root;
    }
    
    root->weight=count_nodes(root);
    
    int bal=get_bal(root);
    int weight=max(1,floor(log2(root->weight)));
    
    if(bal>weight && get_bal(root->left)>=0) {
        return right_rotate(root);
    }

    if (bal>weight && get_bal(root->left)<0) {
        root->left=left_rotate(root->left);
        return right_rotate(root);
    }

    if(bal<-weight && get_bal(root->right)<=0) {
        return left_rotate(root);
    }

    if(bal<-weight && get_bal(root->right)>0) {
        root->right=right_rotate(root->right);
        return left_rotate(root);
    }
    root->left=check_if_bst(root->left);
    root->right=check_if_bst(root->right);
    return root;
}

node *delete_node(node *root,int key) {
    if(root==NULL) {
        return root;
    }
    
    if(key<root->value) {
        root->left=delete_node(root->left,key);
    }
    else if(key>root->value) {
        root->right=delete_node(root->right,key);
    }
    else {
        if((root->left==NULL) || (root->right==NULL)) {
            node *curr=root->left ? root->left : root->right;
            
            if(curr==NULL) {
                curr=root;
                root=NULL;
            }
            else {
                *root=*curr;
            }
            free(curr);
        }
        else {
            node *curr=min_val_node(root->right);
            root->value=curr->value;
            root->right=delete_node(root->right,curr->value);
        }
    }
    
    if(root==NULL) {
        return root;
    }
    
    root->height=1+max(height(root->left),height(root->right));
    root->weight=count_nodes(root);
    
    int bal=get_bal(root);
    int weight=max(1,floor(log2(root->weight)));
    
    if(bal>weight && get_bal(root->left)>=0) {
        return right_rotate(root);
    }

    if (bal>weight && get_bal(root->left)<0) {
        root->left=left_rotate(root->left);
        return right_rotate(root);
    }

    if(bal<-weight && get_bal(root->right)<=0) {
        return left_rotate(root);
    }

    if(bal<-weight && get_bal(root->right)>0) {
        root->right=right_rotate(root->right);
        return left_rotate(root);
    }
    
    return root;
}

node *find_node(node *root,int value) {
    if(root==NULL || root->value==value) {
        return root;
    }
    else if(value>root->value) {
        return find_node(root->right,value);
    }
    else {
        return find_node(root->left,value);
    }
}

void print_preorder(node* root) { 
    if(root==NULL) {
        return; 
    }

    printf("%d ", root->value);   
    print_preorder(root->left);   
    print_preorder(root->right); 
}

int main(int argc,char *argv[]) {
    struct btree *btree;
    struct bt_node *temp;
    char option[3];
    int num;
    
    btree=tree_create();
    scanf("%s",option);
    while(1){   
        if(strcmp(option,"-i")==0) {
            while(1) {
                scanf("%s",option);
                if(isdigit(option[0])!=0) {
                    num=atoi(option);
                    temp=find_node(btree->root,num);
                    if(temp!=NULL) {
                        printf("\nNOT INSERTED %d\n",num);
                        continue;
                    }
                    btree->root=insert_node(btree->root,num);
                    printf("\nINSERTED %d\n",num);
                }
                else {
                    if(strcmp(option,"-p")==0) {
                        printf("\n");
                        print_preorder(btree->root);
                        printf("\n");
                    }
                    else {
                        break;
                    }
                }
            }
            continue;
        }
        if(strcmp(option,"-d")==0) {
            while(1) {
                scanf("%s",option);
                if(isdigit(option[0])!=0) {
                    num=atoi(option);
                    temp=find_node(btree->root,num);
                    if(temp==NULL) {
                        printf("\nNOT DELETED %d\n",num);
                        continue;
                    }
                    btree->root=delete_node(btree->root,num);
                    btree->root=check_if_bst(btree->root);
                    btree->root=check_if_bst(btree->root);
                    printf("\nDELETED %d\n",num);
                }
                else {
                    if(strcmp(option,"-p")==0) {
                        printf("\n");
                        print_preorder(btree->root);
                        printf("\n");
                    }
                    else {
                        break;
                    }
                }
            }
            continue;
        }
        if(strcmp(option,"-f")==0) {
            while(1) {
                scanf("%s",option);
                if(isdigit(option[0])!=0) {
                    num=atoi(option);
                    temp=find_node(btree->root,num);
                    if(temp==NULL) {
                        printf("\nNOT FOUND %d\n",num);
                    }
                    else {
                        printf("\nFOUND %d\n",num);
                    }
                }
                else {
                    if(strcmp(option,"-p")==0) {
                        printf("\n");
                        print_preorder(btree->root);
                        printf("\n");
                    }
                    else {
                        break;
                    }
                }
            }
            continue;
        }
        if(strcmp(option,"-p")==0) {
            printf("\n");
            print_preorder(btree->root);
            printf("\n");
        }
        if(strcmp(option,"-q")==0) {
            clear_tree(btree->root);
            free(btree);
            return 0;
        }
    }
}