union Val {
    int type_int;
    float type_float;
    char  type_string[30];
};

struct Node{
    char name[50];
    struct Node * child;
    struct Node * brother;
    int num_child;
    int row,col;
    int first;
    int visit;
    union Val value;
};


struct Node* Create(char *name, int row);
void AddNode(struct Node * p, struct Node * child);
void OutputTree(struct Node* root);