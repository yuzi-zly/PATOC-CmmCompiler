// The Type of C--
typedef struct Type_ * Type;
typedef struct FieldList_ * FieldList;

struct Type_
{
    enum {BASIC, ARRAY, STRUCTURE} kind;
    union{
        int basic;//0 for int, 1 for float
        struct {Type elem; int size;} array;
        FieldList structure;
    } u;
};

struct FieldList_
{
    char *name;
    Type type;
    FieldList tail;
};

struct DTNode
{
    char name[50];
    int struct_num;
    int deep;// only for struct
    struct Type_ type_;
    struct DTNode* next;
};
