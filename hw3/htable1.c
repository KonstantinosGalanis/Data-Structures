#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void insert(int ***array,int size,int num) {
    int pos;
    pos=num%size;
    if((*array)[pos]==NULL) {
        (*array)[pos]=(int *)malloc(sizeof(int));
        *(*array)[pos]=num;
        return ;
    }
    
    pos=pos+1;
    if(pos>=size) {
        pos=0;
    }
    while(1) {
        if((*array)[pos]==NULL) {
            (*array)[pos]=(int *)malloc(sizeof(int));
            *(*array)[pos]=num;
            return ;
        }
        pos=pos+1;
        if(pos>=size) {
            pos=0;
        }
    }
}

void delete(int ***array,int pos) {
    free((*array)[pos]);
    (*array)[pos]=(int*)0x1;
}

void rehash(int ***array,double *size,int elements,int num,int flag) {
    int temp[elements+1],cnt=0,i;
    int real_size=(*size);
    for(i=0;i<(*size);i++) {
        if((*array)[i]!=NULL && (*array)[i]!=(int*)0x1) {
            temp[cnt]=*(*array)[i];
            cnt++;
        }
    }
    if(flag==0) {
        temp[cnt]=num;
    }
    for(i=0;i<(*size);i++) {
        if((*array)[i]!=NULL && (*array)[i]!=(int*)0x1) {
            free((*array)[i]);
        }
    }
    free(*array);
    if(flag==0) {
        *size=2*(*size);
        real_size=real_size*2;
    }
    else if(flag==1) {
        *size=(*size)/2;
        real_size=real_size/2;
    }
    (*array)=(int **)malloc(real_size*sizeof(int *));
    for(i=0;i<*size;i++) {
        (*array)[i]=NULL;
    }
    if(flag==0) {
        for(i=0;i<elements+1;i++) {
            insert(array,real_size,temp[i]);
        }
    }
    else if(flag==1) {
        for(i=0;i<elements;i++) {
            insert(array,real_size,temp[i]);
        }
    }
}

int find(int ***array,int num,int size) {
    int i;
    for(i=0;i<size;i++) {
        if((*array)[i]!=NULL && (*array)[i]!=(int*)0x1) {
            if(*(*array)[i]==num) {
                return i;
            }
        }
    }
    return -1;
}

void print(int **array,double size,int elements,int deleted_cnt) {
    int i;
    int real_size=size;
    
    printf("SIZE: %d, INSERTED: %d, DELETED: %d\n",real_size,elements,deleted_cnt);
    for(i=0;i<real_size;i++) {
        printf("%3d ",i);
    }
    printf("\n");
    for(i=0;i<real_size;i++) {
        if(array[i]==NULL){
            printf("  * ");
        }
        else if(array[i]==(int*)0x1) {
            printf("  # ");
        }
        else {
            printf("%d ",(*array[i]));
        }
    }
}

int main(int argc,char *argv[]) {
    char option[3];
    int num,res,i,elements=0,deleted_cnt=0;
    double load_factor,size=2;
    int **array;
    
    array=(int **)malloc(size*sizeof(int *));
    for(i=0;i<size;i++) {
        array[i]=NULL;
    }
    
    scanf("%s",option);
    while(1){   
        if(strcmp(option,"-i")==0) {
            while(1) {
                scanf("%s",option);
                if(isdigit(option[0])!=0) {
                    num=atoi(option);
                    res=find(&array,num,size);
                    if(res>0) {
                        printf("\nNOT INSERTED %d\n",num);
                        continue;
                    }
                    load_factor=elements/size;
                    if(load_factor>=0.5) {
                        rehash(&array,&size,elements,num,0);
                        elements++;
                        printf("\nINSERTED %d\n",num);
                        continue;
                    }
                    insert(&array,size,num);
                    elements++;
                    printf("\nINSERTED %d\n",num);
                }
                else {
                    if(strcmp(option,"-p")==0) {
                        printf("\n");
                        print(array,size,elements,deleted_cnt);
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
                    res=find(&array,num,size);
                    if(res==-1) {
                        printf("\nNOT DELETED %d\n",num);
                        continue;
                    }
                    delete(&array,res);
                    printf("\nDELETED %d\n",num);
                    elements--;
                    deleted_cnt++;
                    load_factor=elements/size;
                    if(load_factor<=0.125) {
                        rehash(&array,&size,elements,num,1);
                        deleted_cnt=0;
                        continue;
                    }
                }
                else {
                    if(strcmp(option,"-p")==0) {
                        printf("\n");
                        print(array,size,elements,deleted_cnt);
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
                    res=find(&array,num,size);
                    if(res==-1) {
                        printf("\nNOT FOUND %d\n",num);
                    }
                    else if(res>0) {
                        printf("\nFOUND %d\n",num);
                    }
                }
                else {
                    if(strcmp(option,"-p")==0) {
                       
                    }
                    else {
                        break;
                    }
                }
            }
            continue;
        }
        if(strcmp(option,"-p")==0) {
          
        }
        if(strcmp(option,"-q")==0) {
            for(i=0;i<size;i++) {
                if(array[i]!=NULL && array[i]!=(int*)0x1) {
                    free(array[i]);
                }
            }
            free(array);
            return 0;
        }
    }
}