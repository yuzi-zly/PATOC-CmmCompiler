#include <stdio.h>
#include <stdlib.h>
#include "SynTree.h"
extern FILE* yyin;
extern void yyrestart();
extern void yyparse();
extern int print_flag;

void OutputTree(struct Node* root);


int main(int argc, char** argv){
    if(argc <= 1) return 1;
    FILE* f = fopen(argv[1],"r");
    if(!f){
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    if(print_flag == 1)
        OutputTree(root);
    return 0;
}
