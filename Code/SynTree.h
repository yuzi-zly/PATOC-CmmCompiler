union Val {
    unsigned int type_int;
    double type_float;
    char  type_string[30];
};

struct Node{
    char name[50];
    struct Node * child;
    struct Node * brother;
    int num_child;
    int row,col;
    int visit;
    int s_or_w; //1-syn,0-words
    union Val value;
};

extern struct Node* root;
struct Node* Create(char *name, int row,int flag);
void AddNode(struct Node * p, struct Node * child);
void OutputTree(struct Node* root);
