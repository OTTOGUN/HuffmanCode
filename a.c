#define OK 1
#define ERROR 0
#define NODES 7
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef char** HuffmanCode;
typedef struct _HTNode{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HTree;

void Select_Min(const HTree T,int length,int* e1,int* e2){
    int min1,min2;
    min1 = min2 = 1000000;
    int pos1,pos2;
    pos1 = pos2 = 0;

    for(int i = 1;i < length + 1;i++){
        if(T[i].parent == 0){
            if(T[i].weight < min1){
                min2 = min1;
                pos2 = pos1;
                min1 = T[i].weight;
                pos1 = i;
            }else if(T[i].weight < min2){
                min2 = T[i].weight;
                pos2 = i;
            }
        }
    }
    *e1 = pos1;
    *e2 = pos2;
}

void Creat_Huffman(HTree* T,int n){
    if(n <= 1){
        return;
    }
    int m = 2 * n - 1;

    *T = (HTree)malloc(sizeof(HTNode) * (m + 1));

    for(int i = 1;i < m + 1;++i){
        (*T)[i].lchild = (*T)[i].rchild = (*T)[i].rchild = (*T)[i].lchild = 0;
        (*T)[i].parent = 0;
    }

    for(int i = 1;i < n + 1;i++){
        scanf("%d",&(*T)[i].weight);
    }

    int min1,min2;
    for(int i = n + 1;i < m + 1;++i){
        Select_Min(*T,i - 1,&min1,&min2);

        (*T)[min1].parent = (*T)[min2].parent = i;
        (*T)[i].lchild = min1;
        (*T)[i].rchild = min2;
        (*T)[i].weight = (*T)[min1].weight + (*T)[min2].weight;
    }
}

HuffmanCode Creat_HuffmanCode(const HTree HT,int n){
    HuffmanCode HC = (char**)malloc(sizeof(char*) * (n + 1));
    char* temp_string = (char*)malloc(sizeof(char) * n);
    temp_string[n - 1] = '\0';

    for(int i = 1;i < n + 1;i++){
        int parent = HT[i].parent;
        int current = i;
        int start = n - 1;
        while(parent){

            if(current == HT[parent].lchild)
                temp_string[--start] = '0';
            else
                temp_string[--start] = '1';

            current = parent;
            parent = HT[parent].parent;
        }
        HC[i] = (char*)malloc(sizeof(char) * (n - start));
        strcpy(HC[i],&temp_string[start]);
    }

    free(temp_string);
    return HC;
}

int main(){
    HTree T = NULL;
    Creat_Huffman(&T,NODES);

    HuffmanCode HC = Creat_HuffmanCode(T,NODES);
    int a = 65;

    for(int i = 1;i < NODES + 1;i++){
        printf("%c = %s\n",a,HC[i]);
        ++a;
    }
    return 0;
}