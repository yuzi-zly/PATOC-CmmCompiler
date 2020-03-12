#include "SynTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node* Create(char *name, int row){
    struct Node* ret = (struct Node*)malloc(sizeof(struct Node));
    if(ret == NULL){
        exit(1);
    }
    strncpy(ret->name,name,strlen(name));
    ret->row = row;
    ret->child = NULL;
    ret->brother = NULL;
    ret->num_child = 0;
    ret->col = 0;
    ret->first = 0;
    ret->visit = 0;
    return ret;
}


void AddNode(struct Node * p, struct Node * child){
    if(child == NULL) return;
    if(p->num_child == 0){
        p->child = child;
        p->num_child++;
        child->first = 1;
    }
    else{
        struct Node * tmp;
        for(int i = 0; i < p->num_child; ++i){
            if(i == 0)
                tmp = p->child;
            else   
                tmp = tmp->brother;
        }
        tmp->brother = child;
        p->num_child++;
    }
}

void OutputTree(struct Node* root){
    
}