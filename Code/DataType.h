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
    //char* struct_name;//用于嵌套下的域名结构体名对比
};

struct FieldList_
{
    char *name;
    Type type;
    FieldList tail;
};

struct DTNode
{
    char* name;
    int struct_num;
    struct Type_ type_;
    struct DTNode* next;
};
