#include <stdio.h>
#include <stdlib.h>
extern FILE* yyin;
extern void yyrestart();
extern void yyparse();
extern struct Node * root;
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
    OutputTree(root);
    return 0;
}
