//The symbol table
#include "SynTree.h"
#include "DataType.h"
#include <stdbool.h>

//#define DEBUG

struct FuncInfo
{
    enum {DECALARE, DEFINE, NONE} status;
    FieldList params;
};


typedef struct SymItem Item;
struct SymItem
{
    enum {FUNCTION, VARIABLE, CONST, USER_DEF} symkind;
    struct FuncInfo funcinfo;
    char* name;
    Type type;
    int dimension; //for array
    int paramnums; //for function
    int fieldnums; //for struct
    union Val value;
    int deep;
    Item * rownext;
    Item * colnext;
};
/*---------------------- Others ----------------------------*/
char *GetAStructName();



/*----------------------- DTtable ---------------------------*/
Type GetTypeByName(char* name);
Type CreateAndAddDTNodeForBasic(char* str);
void CreateAndAddDTNodeForStruct(char* name, int structnum, int deep);
bool AddFieldInStruct(int structnum, char* fieldname, Type fieldtype);
Type CreateArrayType(Type basetype, unsigned int size);


/*----------------------- Symtable ---------------------------*/
Item * GetItemByName(char* name,int curdeep);