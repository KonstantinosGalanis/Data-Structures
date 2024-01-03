#include <stdio.h>
#include <stdlib.h>

typedef struct bt_node {  
    struct bt_node* left;  
    struct bt_node* right;  
    int height;
    int value;
} node;

typedef struct btree {  
    node* root;  
} tree;

tree *tree_create() {
    tree *btree=(tree *)malloc(sizeof(tree));
    
    if(!btree) {
        exit(-1);
    }
    btree->root=NULL;
    return btree;
}

void clear_tree(node *root) {
    if(!root) {
        return;
    }
    clear_tree(root->left);
    clear_tree(root->right);
    free(root);
}

int max(int a,int b) {
    return (a>b)?a:b;
}

int min(int a,int b) {
    return (a>b)?b:a;
}

int height(node *k) {
    if(k==NULL) {
        return 0;
    }

    return k->height;
}

node *construct_tree_pre(int preorder[],int start,int end) {
    int i;
    
    if(start>end) {
        return NULL;
    }
    
    node *root=(node *)malloc(sizeof(node));
    root->value=preorder[start];
    root->left=root->right=NULL;
    root->height=1;
    
    for(i=start;i<=end;i++) {
        if(preorder[i]>root->value) {
            break;
        }
    }
    
    root->left=construct_tree_pre(preorder,start+1,i-1);
    root->right=construct_tree_pre(preorder,i,end);
    root->height=max(height(root->left),height(root->right))+1;
    return root;
}

int check_if_rb_util(node *root, int *max1, int *min1){
    if(root==NULL){
        (*max1)=(*min1)=0;
        return 1;
    }
   
    int lmx1,lmn1;
    int rmx1,rmn1;
    if(check_if_rb_util(root->left,&lmx1,&lmn1)==0) {
        return 0;
    }
        
    if(check_if_rb_util(root->right,&rmx1,&rmn1)==0) {
        return 0;
    }
    
    (*max1)=max(lmx1,rmx1)+1;
    (*min1)=min(lmn1,rmn1)+1;
    
    if((*max1)<=2*(*min1)) {
        return 1;
    }
    
    return 0;
}
int check_if_rb(node *root){
   int max1,min1;
   return check_if_rb_util(root,&max1,&min1);
}

node *find_parent(node *root,int key) {
    if(root==NULL || root->value==key) {
        return NULL;
    }
    
    if((root->left!=NULL && root->left->value==key) || (root->right!=NULL && root->right->value==key)) {
        return root;
    }
    
    node *temp=find_parent(root->left,key);
    
    if(temp !=NULL) {
        return temp;
    }
    
    temp=find_parent(root->right,key);
    return temp;
}

void print_rb(node *root,int flag,int cnt,int black_counter,node *help,int maxh) {
    node *parent=NULL;
    if(root!=NULL) {
        printf("%d",root->value);
        parent=find_parent(help,root->value);
        if(root->height==1 && cnt<black_counter) {
            flag=1;
            printf("#B ");
        }
        else if(root->height-cnt==0 && parent->height-root->height==1) {
            flag=1;
            cnt++;
            printf("#B ");
        }
        else if(flag==0) {
            flag=1;
            cnt++;
            printf("#B ");
        }
        else if(flag==1) {
            flag=0;
            printf("#R ");
        }
        
        print_rb(root->left,flag,cnt,black_counter,help,maxh-1);
        print_rb(root->right,flag,cnt,black_counter,help,maxh-1);
        if(flag==1) {
            cnt--;
        }
    }
}

int main(int argc,char *argv[]) {
    int res;
    struct btree *btree;
    int num,i=0,*preorder,black_counter;
    
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
    res=check_if_rb(btree->root);
    if(res==1) {
        printf("RB OK\n\n");
    }
    else if(res==0){
        printf("RB NOK\n\n");
    }
    black_counter=btree->root->height/2;
    print_rb(btree->root,0,0,black_counter,btree->root,btree->root->height);
    printf("\n");
    printf("\n");
    clear_tree(btree->root);
    free(btree);
    free(preorder);
    return 0;
}
