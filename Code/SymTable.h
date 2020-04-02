//The symbol table
#include "SynTree.h"
#include "DataType.h"
#include <stdbool.h>

#define HTSIZE 0x3ff

// #define DEBUG

struct FuncInfo
{
    enum {DECALARE, DEFINE, NONE} status;
    FieldList params;
};


typedef struct SymItem Item;
struct SymItem
{
    enum {FUNCTION, VARIABLE, CONST} symkind;
    struct FuncInfo* funcinfo;
    int func_num;//表示哪一个函数
    //int struct_num;//表示域名在哪一个结构体内
    char* name;
    Type type;
    //int dimension; //for array
    int paramnums; //for function
    //int fieldnums; //for struct
    //union Val value;
    int rownum;
    int deep;
    Item* rownext;
    Item* colnext;
};
/*---------------------- Others ----------------------------*/
char *GetAStructName();



/*----------------------- DTtable ---------------------------*/
Type GetTypeByName(char* name);
struct DTNode* GetDTNodeByName(char* name);
Type CreateAndAddDTNodeForBasic(char* str);
struct DTNode* CreateDTNodeForStruct(char* name, int structnum);
void AddDTNodeForStruct(struct DTNode* structnode);
bool AddFieldInStruct(struct DTNode* structnode, char* fieldname, Type fieldtype);
Type CreateArrayType(Type basetype, unsigned int size);
bool CheckTypes(Type type1, Type type2);
Type FindFieldInStruct(Type this_type, char* fieldname);

/*----------------------- Symtable ---------------------------*/
Item* GetItemByName(char* name,int curdeep);
bool CreateAndAddVarInTable(char* name, Type this_type, int deep, int row);
Item* CreateFunctionItem(int funcnum, char* funcname, Type functype, int mode, int deep, int rownum);
void AddFuncItemInTable(Item* funcitem,int deep);
void AddParamInFunc(Item* funcitem, char* paramname, Type paramtype);
bool CheckParamInFunc(Item* funcitem, Type paramtype, int pnum);
bool CheckArgInFunc(Item* funcitem, Type argtype, int pnum);
