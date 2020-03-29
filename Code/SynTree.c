#include "SynTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node* Create(char *name, int row,int flag){
    struct Node* ret = (struct Node*)malloc(sizeof(struct Node));
    if(ret == NULL){
        fprintf(stderr,"Memory Used Up\n");
        exit(1);
    }
    memset(ret->name,0,sizeof(ret->name));
    memset(ret->value.type_string,0,sizeof(ret->value.type_string));

    strncpy(ret->name,name,strlen(name));
    ret->row = row;
    ret->s_or_w = flag;
    ret->child = NULL;
    ret->brother = NULL;
    ret->num_child = 0;
    ret->col = 0;
    ret->visit = 0;
    return ret;
}


void AddNode(struct Node * p, struct Node * child){
    if(child == NULL) {
        return;
    }
    if(p->num_child == 0){
        p->child = child;
        p->num_child++;
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

void OutputTree(struct Node* ptr){
    if(ptr-> visit == 1){
        return;
    }
    ptr->visit = 1;
 
    // if(ptr != root)
    //     fprintf(stdout,"\n");
    for(int i = 0; i < ptr->col; ++i){
        fprintf(stdout," ");
    }
    
    fprintf(stdout,"%s",ptr->name);
    if(ptr->s_or_w == 1){
        //syn
        fprintf(stdout," (%d)\n",ptr->row);
    }
    else if(ptr->s_or_w == 0){
        //word
        if(strcmp(ptr->name,"ID") == 0 || strcmp(ptr->name,"TYPE") == 0){
            fprintf(stdout,": %s\n",ptr->value.type_string);
        }
        else if(strcmp(ptr->name,"INT") == 0){
            fprintf(stdout,": %u\n",ptr->value.type_int);
        }
        else if(strcmp(ptr->name,"FLOAT") == 0){
            fprintf(stdout,": %f\n",(float)ptr->value.type_float);
        }
        else
        {
            fprintf(stdout,"\n");
        }
        
    }
    if(ptr->num_child < 1) return;

    struct Node * tmp;
    tmp = ptr->child;
    if(tmp->visit == 0){
       tmp->col = ptr->col + 2;
       OutputTree(tmp);
    }
    for(int i = 1; i < ptr->num_child; ++i){
        tmp = tmp->brother;
        if(tmp->visit == 0){
            tmp->col = ptr->col + 2;
            OutputTree(tmp);
        }
    }

}
