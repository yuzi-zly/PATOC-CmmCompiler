#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SymTable.h"
#include "debug.h"

/* Item */
Item* Hashtable[HTSIZE];
struct SymStack{
    Item* Iptr;
    int deep;
    struct SymStack* next;
} *Stackhead;

/* DataType */
struct DTNode *DThead;

/* Funcitem */
Item* FuncList[HTSIZE];

/*---------------------- Others ----------------------------*/
char* myitoa(int num, char* str){
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

unsigned int Hash_pjw(char* name){
    unsigned int val = 0 , i;
    for(; *name; ++name){
        val = (val << 2) + *name;
        if(i = val & ~HTSIZE)
            val = (val ^ (i >> 12)) & HTSIZE;
    }
    return val;
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
Type GetTypeByName(char* name){
    #ifdef DEBUG
    Log("In Get Type by name %s",name);
    #endif
    struct DTNode* ptr = DThead;
    while(ptr != NULL){
        if(strcmp(name,ptr->name) == 0){
            return &(ptr->type_);
        }     
        ptr = ptr->next;
    }
    return NULL;
}

struct DTNode * GetDTNodeByName(char* name){
    struct DTNode* ptr = DThead;
    while(ptr != NULL){
        if(strcmp(name,ptr->name) == 0)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

Type CreateAndAddDTNodeForBasic(char* str){
    #ifdef DEBUG
    Log("In Create Add DTNode for Basic");
    #endif

    Assert((strcmp(str,"int") == 0)||((strcmp(str,"float") == 0)),"Wrong Basic Type.");

    struct DTNode* newDTnode = (struct DTNode*)malloc(sizeof(struct DTNode));
    memset(newDTnode,0,sizeof(struct DTNode));

    newDTnode->name = str;
    newDTnode->struct_num = 0;
    newDTnode->type_.kind = BASIC;
    newDTnode->type_.u.basic = strcmp(str,"int") == 0 ? 0 : 1;

    struct DTNode* tmp = DThead;
    newDTnode->next = tmp;
    DThead = newDTnode;
    return &(newDTnode->type_);
    
}

//创建结构体DT结点
struct DTNode* CreateDTNodeForStruct(char* name, int structnum){
    struct DTNode* newDTnode = (struct DTNode*)malloc(sizeof(struct DTNode));
    memset(newDTnode,0,sizeof(struct DTNode));
    newDTnode->name = name;
    newDTnode->struct_num = structnum;
    newDTnode->type_.kind = STRUCTURE;
    newDTnode->type_.u.structure = NULL;
    return newDTnode;
}

//添加完整的结构体
void AddDTNodeForStruct(struct DTNode* structnode){
    struct DTNode* tmp = DThead;
    structnode->next = tmp;
    DThead = structnode;
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

bool AddFieldInStruct(struct DTNode* structnode, char* fieldname, Type fieldtype){
    #ifdef DEBUG
    Log("In Add Field In Struct with name %s, type %d",fieldname,fieldtype->kind);
    #endif

    Assert(structnode != NULL,"Cannot add a field in Basic or Array.");
    return CheckAndAddInFieldList(fieldname,fieldtype,&(structnode->type_));
   
}

Type CreateArrayType(Type basetype, unsigned int size){
    Type ret = (Type)malloc(sizeof(struct Type_));
    memset(ret,0,sizeof(struct Type_));
    ret->kind = ARRAY;
    ret->u.array.elem = basetype;
    ret->u.array.size = (int)size;
    return ret;
}

//用于检测两种类型之间是否等价
bool CheckTypes(Type type1, Type type2){
    #ifdef DEBUG
    LogYellow("In CheckTypes with type1 %d, type2 %d",type1->kind,type2->kind);
    #endif

    if(type1->kind != type2->kind)
        return false;
    if(type1->kind == BASIC){
        if(type1->u.basic != type2->u.basic)
            return false;
        else
            return true;
    }
    else if(type1->kind == ARRAY){
        return CheckTypes(type1->u.array.elem, type2->u.array.elem);
    }
    else if(type1->kind ==STRUCTURE){
        FieldList slist1 = type1->u.structure;
        FieldList slist2 = type2->u.structure;
        while (slist1 != NULL && slist2 != NULL)
        {
            if(CheckTypes(slist1->type, slist2->type) == false)
                return false;
            slist1 = slist1->tail;
            slist2 = slist2->tail;
        }    
        if(slist1 == NULL && slist2 == NULL)
            return true;
        return false;
    }
    else
        Assert(0,"No such Type kind");

}

//用于得到结构体域的类型
Type FindFieldInStruct(Type this_type, char* fieldname){
    #ifdef DEBUG
    Log("In Find Field In Struct with fieldname %s.",fieldname);
    #endif
    FieldList plist = this_type->u.structure;
    while(plist != NULL){
        if(strcmp(plist->name,fieldname) == 0)
            return plist->type;
        plist = plist->tail;
    }
    return NULL;
}


/*----------------------- Symtable ---------------------------*/
Item* GetItemByName(char* name,int curdeep){
    #ifdef DEBUG
    LogGreen("In Get Item By Name %s, deep %d",name,curdeep);
    #endif
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
        Hashtable[num]->rowpref = newvar;
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

//创造一个函数项
Item* CreateFunctionItem(int funcnum, char* funcname, Type functype, int mode, int deep, int rownum){
    #ifdef DEBUG
    LogPurple("In Create Function Item,with funcnum %d,funcname %s, functype %d, mode %d"
            ,funcnum,funcname,functype->kind,mode);
    #endif

    Item * newfunc = (Item *)malloc(sizeof(Item));
    memset(newfunc,0,sizeof(Item));
    newfunc->symkind = FUNCTION;
    newfunc->func_num = funcnum;
    newfunc->name = funcname;
    newfunc->type = functype;
    newfunc->rownum = rownum;
    newfunc->deep = deep;
    newfunc->funcinfo = (struct FuncInfo*)malloc(sizeof(struct FuncInfo));
    memset(newfunc->funcinfo,0,sizeof(struct FuncInfo));
    newfunc->funcinfo->status = mode;

    return newfunc;
}

//将函数项添加到表中
void AddFuncItemInTable(Item* funcitem,int deep){
    #ifdef DEBUG
        LogPurple("In the Add Func Item In Table with funcnum %d,funcname %s, functype %d"
            ,funcitem->func_num,funcitem->name,funcitem->type->kind);
    #endif

    //函数数组插入
    FuncList[funcitem->func_num] = funcitem;

    //行插入
    int num = Hash_pjw(funcitem->name);
    funcitem->rownext = Hashtable[num];
    if(Hashtable[num] != NULL)
        Hashtable[num]->rowpref = funcitem;
    Hashtable[num] = funcitem;

    //列插入
    struct SymStack *Chead = Stackhead;
    while(Chead != NULL && Chead->deep >= deep){
        if(Chead->deep == deep){
            //找到对应列
            Hashtable[num]->colnext = Chead->Iptr;
            Chead->Iptr = Hashtable[num];
            return;
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
    return;
}

void ExchangeFuncItem(Item* olditem, Item* newitem){
    #ifdef DEBUG
    LogPurple("In exchange function item with oldnum %d, newnum %d",olditem->func_num,newitem->func_num);
    #endif

    //函数数组
    FuncList[olditem->func_num] = NULL;
    FuncList[newitem->func_num] = newitem;

    //行更换
    int num = Hash_pjw(olditem->name);
    if(olditem->rowpref == NULL){
        //第一个
        Hashtable[num] = newitem;
        if(olditem->rownext != NULL){
            olditem->rownext->rowpref = newitem;
            newitem->rownext = olditem->rownext;
            olditem->rownext = NULL;
        }
    }
    else if(olditem->rownext == NULL){
        //最后一个
        olditem->rowpref->rownext = newitem;
        newitem->rowpref = olditem->rowpref;
        olditem->rowpref = NULL;
    }
    else{
        olditem->rownext->rowpref = newitem;
        olditem->rowpref->rownext = newitem;
        newitem->rowpref = olditem->rowpref;
        newitem->rownext = olditem->rownext;
        olditem->rownext = olditem->rowpref = NULL;
    }

    //列更换
    struct SymStack* Chead = Stackhead;
    while(Chead != NULL && Chead->deep > olditem->deep){
        Chead = Chead->next;
    }
    if(Chead != NULL && Chead->deep == olditem->deep){
        Item* iptr = Chead->Iptr;
        if(iptr == olditem){
            iptr = newitem;
            newitem->colnext = olditem->colnext;
            return;
        }    
        while(iptr != NULL){
            if(iptr->colnext == olditem)
                break;
            iptr = iptr->colnext;
        }
        iptr->colnext = newitem;
        newitem->colnext = olditem;
        return;
    }

}

//添加函数参数
void AddParamInFunc(Item* funcitem, char* paramname, Type paramtype, int paramrow){
    #ifdef DEBUG
    LogPurple("In Add Param In Func with funcnum %d, paramname %s, paramtype %d, paranum %d"
        ,funcitem->func_num,paramname,paramtype->kind,funcitem->paramnums+1);
    #endif

    funcitem->paramnums++;
    FieldList newparam = (FieldList)malloc(sizeof(struct FieldList_));
    memset(newparam,0,sizeof(struct FieldList_));
    newparam->name = paramname;
    newparam->type = paramtype;
    FieldList plist = funcitem->funcinfo->params;
    if(plist == NULL){
        funcitem->funcinfo->params = newparam;
        return;
    }
    while(plist->tail != NULL){
        //检查参数是否同名
        if(strcmp(paramname,plist->name) == 0){
            fprintf(stderr,"Error type 3 at Line %d: Redefined variable \" %s \".\n",paramrow,paramname);
        }
        plist = plist->tail;
    }
    if(strcmp(paramname,plist->name) == 0){
            fprintf(stderr,"Error type 3 at Line %d: Redefined variable \" %s \".\n",paramrow,paramname);
    }
    plist->tail = newparam;
    return;
}


//多次声明或者定义检查函数参数
//并将名字改为最后一次
bool CheckParamInFunc(Item* funcitem, char* paramname, Type paramtype, int pnum, int paramrow){
    #ifdef DEBUG
    LogPurple("In Check Param In Func with funcnum %d, paramtype %d, pnum %d"
        ,funcitem->func_num,paramtype->kind,pnum);
    #endif

    FieldList plist = funcitem->funcinfo->params;
    if(plist == NULL){
    	return false;	 	
    }
    
    for(int i = 1; i < pnum; i++){
        if(strcmp(paramname,plist->name) == 0){
            fprintf(stderr,"Error type 3 at Line %d: Redefined variable \" %s \".\n",paramrow,paramname);
        }
        plist = plist->tail;
    }
    if(plist == NULL)
        return false;
    if(CheckTypes(plist->type,paramtype)){
        plist->name = paramname;
        return true;
    }
    return false;
}

//调用时检查函数参数
bool CheckArgInFunc(Item* funcitem, Type argtype, int pnum){
    #ifdef DEBUG
    LogPurple("In Check Arg In Func with funcnum %d, argtype %d, pnum %d"
        ,funcitem->func_num,argtype->kind,pnum);
    #endif

    FieldList plist = funcitem->funcinfo->params;
    Assert(plist != NULL, "The plist is NULL");
    for(int i = 1; i < pnum; i++){
        plist = plist->tail;
    }
    if(plist == NULL)
        return false;
    if(CheckTypes(plist->type, argtype))
        return true;
    return false;
}


Type GetParamInFunction(char* paramname, Item* funcitem){
    #ifdef DEBUG
    LogPurple("In Get Param In Function with param %s, funcnum %d",paramname,funcitem->func_num);
    #endif
    Assert(funcitem != NULL,"Wrong in Get Param In Function");
    FieldList plist = funcitem->funcinfo->params;
    while(plist != NULL){
        if(strcmp(plist->name,paramname) == 0)
            return plist->type;
        plist = plist->tail;
    }
    #ifdef DEBUG
    LogPurple("Get param return NULL");
    #endif
    return NULL;
}

void DeleteItemInDeep(int deep){
    #ifdef DEBUG
    LogGreen("In Delete Item In Deep");
    #endif
    Assert(deep > 0, "Wrong in Delete");

    struct SymStack* Chead = Stackhead;
    while(Chead != NULL && Chead->deep > deep){
        Chead = Chead->next;
    }
    if(Chead != NULL && Chead->deep == deep){
        Item* ptr = Chead->Iptr;
        while(ptr != NULL){
            if(ptr->rowpref == NULL){
                //第一个
                if(ptr->rownext == NULL){
                    //只有一个
                    Hashtable[Hash_pjw(ptr->name)] = NULL;
                }
                else{
                    ptr->rownext->rowpref = NULL;
                    Hashtable[Hash_pjw(ptr->name)] = ptr->rownext;
                    ptr->rownext = NULL;
                }
            }
            else if(ptr->rownext == NULL){
                //最后一个
                ptr->rowpref->rownext = NULL;
                ptr->rowpref = NULL;
            }
            else{
                Item* pref = ptr->rowpref;
                Item* next = ptr->rownext;
                pref->rownext = next;
                next->rowpref = pref;
                ptr->rowpref = ptr->rownext = NULL;
            }
            ptr = ptr->colnext;
        }
        Chead->Iptr = NULL;
    }

}
