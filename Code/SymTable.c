#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SymTable.h"
#include "debug.h"

#define HTSIZE 0x3ff

Item * Hashtable[HTSIZE];
struct SymStack{
    Item * Iptr;
    int deep;
    struct SymStack * next;
} *Stackhead;

struct DTNode *DThead;

unsigned int Hash_pjw(char* name){
    unsigned int val = 0 , i;
    for(; *name; ++name){
        val = (val << 2) + *name;
        if(i = val & ~HTSIZE)
            val = (val ^ (i >> 12)) & HTSIZE;
    }
    return val;
}

/*---------------------- Others ----------------------------*/
char * myitoa(int num, char* str){
    int i = 0;
    do
    {
        str[i++] = num%10+48;
        num /= 10;
    }while(num);
    str[i] = '\0';  
    int j = 0;
    if(str[0]=='-')
    {
        j = 1;
        ++i;
    }    
    for(;j<i/2;j++)
    {      
        str[j] = str[j] + str[i-1-j];
        str[i-1-j] = str[j] - str[i-1-j];
        str[j] = str[j] - str[i-1-j];
    }  
    return str;
}



char *GetAStructName(){
    static int cnt = 0;
    static char defaultname[] = "StructNum"; 
    char *ordder = (char*)malloc(8);
    memset(ordder,0,8);
    char *ret = (char*)malloc(20);
    memset(ret,0,20);

    ordder = myitoa(cnt,ordder);
    strncpy(ret,defaultname,strlen(defaultname));
    strncat(ret,ordder,strlen(ordder));
    cnt++;
    return ret;
}

/*----------------------- DTtable ---------------------------*/
Type GetTypeByName(char* name, int deep){
    struct DTNode * ptr = DThead;
    while(ptr != NULL){
        if(strcmp(name,ptr->name) == 0 && ptr->deep <= deep)
            return &(ptr->type_);
        ptr = ptr->next;
    }
    return NULL;
}

struct DTNode * GetDTNodeByName(char* name){
    struct DTNode * ptr = DThead;
    while(ptr != NULL){
        if(strcmp(name,ptr->name) == 0)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

Type CreateAndAddDTNodeForBasic(char* str){
    Assert((strcmp(str,"int") == 0)||((strcmp(str,"float") == 0)),"Wrong Basic Type.");

    struct DTNode* newDTnode = (struct DTNode*)malloc(sizeof(struct DTNode));
    memset(newDTnode,0,sizeof(struct DTNode));

    strncpy(newDTnode->name, str, strlen(str));
    newDTnode->struct_num = 0;
    newDTnode->deep = 0;
    newDTnode->type_.kind = BASIC;
    newDTnode->type_.u.basic = strcmp(str,"int") == 0 ? 0 : 1;

    struct DTNode* tmp = DThead;
    newDTnode->next = tmp;
    DThead = newDTnode;
    return &(newDTnode->type_);
    
}

void CreateAndAddDTNodeForStruct(char* name, int structnum, int deep){
    struct DTNode* newDTnode = (struct DTNode*)malloc(sizeof(struct DTNode));
    memset(newDTnode,0,sizeof(struct DTNode));
    strncpy(newDTnode->name, name, strlen(name));
    newDTnode->struct_num = structnum;
    newDTnode->deep = deep;
    newDTnode->type_.kind = STRUCTURE;
    newDTnode->type_.u.structure = NULL;

    struct DTNode* tmp = DThead;
    newDTnode->next = tmp;
    DThead = newDTnode;

    #ifdef DEBUG
        LogGreen("The struct Name is %s",newDTnode->name);
    #endif

}


static bool CheckAndAddInFieldList(char* fieldname, Type fieldtype, Type ptype){
    #ifdef DEBUG
    Log("In Check And Add In Field List with name %s, type %d",fieldname,fieldtype->kind);
    #endif

    if(ptype->u.structure == NULL){
        //第一个域
        FieldList newfield = (FieldList) malloc(sizeof(struct FieldList_));
        memset(newfield,0,sizeof(struct FieldList_));
        newfield->name = fieldname;
        newfield->type = fieldtype;
        newfield->tail = NULL;
        ptype->u.structure = newfield;
        return true;
    }
    //不是第一个域

    FieldList structure = ptype->u.structure;
    while(structure != NULL){
        //重复定义
        if(strcmp(fieldname,structure->name) == 0)
            return false;
        if(structure->tail == NULL)
            break;
        structure = structure->tail;
    }

    FieldList newfield = (FieldList) malloc(sizeof(struct FieldList_));
    memset(newfield,0,sizeof(struct FieldList_));
    newfield->name = fieldname;
    newfield->type = fieldtype;
    newfield->tail = NULL;
    structure->tail = newfield;
    #ifdef DEBUG
    Log("before return");
    #endif
    
    return true;
}

bool AddFieldInStruct(int structnum, char* fieldname, Type fieldtype){
    #ifdef DEBUG
    Log("In Add Field In Struct with name %s, type %d",fieldname,fieldtype->kind);
    #endif

    Assert(structnum != 0,"Cannot add a field in Basic or Array.");
    struct DTNode* DTptr = DThead;
    while(DTptr != NULL){
        if(DTptr->struct_num == structnum){
    #ifdef DEBUG
            Log("Meet the struct");
    #endif
            return CheckAndAddInFieldList(fieldname, fieldtype,
                     &(DTptr->type_));
        }
        DTptr = DTptr->next;
    }
    Assert(0,"Need to creat DTNode before add field");
}

Type CreateArrayType(Type basetype, unsigned int size){
    Type ret = (Type)malloc(sizeof(struct Type_));
    memset(ret,0,sizeof(struct Type_));
    ret->kind = ARRAY;
    ret->u.array.elem = basetype;
    ret->u.array.size = (int)size;
    return ret;
}



/*----------------------- Symtable ---------------------------*/
Item * GetItemByName(char* name,int curdeep){
    int pos = Hash_pjw(name);
    Item *tmp = Hashtable[pos];
    while(tmp != NULL){
        if(strcmp(tmp->name,name) == 0 && curdeep == tmp->deep)
            return tmp;
        tmp = tmp->rownext;
    }
    return NULL;
}

//添加变量项
bool CreateAndAddVarInTable(char* name, Type this_type, int deep, int row){
    #ifdef DEBUG
    Log("In Add Variable In Table with name: %s, type: %d, deep: %d, row: %d"
        ,name,this_type->kind,deep,row);
    #endif

    //插入HashTable
    int num = Hash_pjw(name);
    if(Hashtable[num] == NULL){
        #ifdef DEBUG
        LogGreen("Hashtable[num] is NULL with num: %d",num);
        #endif
        Item * newvar  = (Item *)malloc(sizeof(Item));
        memset(newvar,0,sizeof(Item));
        newvar->symkind = VARIABLE;
        newvar->name = name;
        newvar->type = this_type;
        newvar->rownum = row;
        newvar->deep = deep;
        Hashtable[num] = newvar;
    }
    else{
        Item * Rptr = Hashtable[num];
        while(Rptr != NULL){
            if(Rptr->deep < deep)
                break;
            if(Rptr->deep == deep && strcmp(Rptr->name,name) == 0)
                return false;
            Rptr = Rptr->rownext;
        }
        Item * newvar  = (Item *)malloc(sizeof(Item));
        memset(newvar,0,sizeof(Item));
        newvar->symkind = VARIABLE;
        newvar->name = name;
        newvar->type = this_type;
        newvar->rownum = row;
        newvar->deep = deep;
        newvar->rownext = Hashtable[num];
        Hashtable[num] = newvar;
    }

    //插入Stack
    struct SymStack * Chead = Stackhead;
    while(Chead != NULL && Chead->deep >= deep){
        if(Chead->deep == deep){
            //找到了对应的列
            Hashtable[num]->colnext = Chead->Iptr;
            Chead->Iptr = Hashtable[num];
            return true;
        }
        Chead = Chead->next;
    }
    #ifdef DEBUG
    LogGreen("Stackhead is NULL");
    #endif
    //Chead为空或者Chead->deep < deep
    struct SymStack * newhead = (struct SymStack *)malloc(sizeof(struct SymStack));
    memset(newhead,0,sizeof(struct SymStack));
    newhead->next = Chead;
    newhead->Iptr = Hashtable[num];
    newhead->deep = deep;
    Stackhead = newhead;
    return true;

}










