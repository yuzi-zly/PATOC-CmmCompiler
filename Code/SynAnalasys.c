#include "SymTable.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*----------------------------functions declaration------------------------*/
Type AnalasysForSpecifier(struct Node* ptr);
Type AnalasysForExp(struct Node* ptr);
bool AnalasysForCompSt(struct Node* ptr, Type _functype);

/*----------------------------static variables------------------------*/
static int basedeep = 0;//函数
static int structdeep = 0;//防止结构体嵌套定义
//当进入一个函数Compst时需要structdeep = basedeep
static int structnum = 0;//第几个结构体
static int funcnum = 0;//第几个函数
static int paramsnum;//用于标定检查到第几个参数
static char basic_int[5] = "int";
static char basic_float[10] = "float";

static bool calledfunc[HTSIZE];
extern Item* FuncList[HTSIZE];

/*----------------------------functions definition------------------------*/

// for VarDec
//_structnode 用于添加结构体域名，默认为NULL
//_funcitem 用于添加函数参数，默认为NULL
bool AnalasysForVarDec(struct Node* ptr,Type this_type, struct DTNode* _structnode, Item* _funcitem){
    #ifdef DEBUG
        Log("In the VarDec with type %d",this_type->kind);
    #endif

    Assert(strcmp(ptr->name,"VarDec") == 0,"wrong at AnalasysForVarDec");
    struct Node* child1 = ptr->child;
    if(strcmp(child1->name,"ID") == 0){
        //在定义结构体中
        if(structdeep > basedeep){
            if(!AddFieldInStruct(_structnode, child1->value.type_string, this_type)){
                fprintf(stderr,"Error type 15 at Line %d: Redefined field \" %s \".\n",child1->row,child1->value.type_string);
                return false;
            }
            //是否要添加到符号表
        }
        else if(_funcitem != NULL){
            //函数参数

            //查找结构体名不为空，冲突
            if(GetTypeByName(child1->value.type_string) != NULL){
                fprintf(stderr,"Error type 3 at Line %d: Redefined variable \" %s \".\n",child1->row,child1->value.type_string);
                return false;
            }

            if(_funcitem->funcinfo->status == NONE){
                AddParamInFunc(_funcitem, child1->value.type_string, this_type);
                return true;
            }
            else{
                return CheckParamInFunc(_funcitem, this_type, paramsnum);
            }
        }
        else{
        
            //查找结构体名不为空，冲突
            if(GetTypeByName(child1->value.type_string) != NULL){
                fprintf(stderr,"Error type 3 at Line %d: Redefined variable \" %s \".\n",child1->row,child1->value.type_string);
                return false;
            }
        
            //添加到HashTable中，期间检查是否有同名变量
            if(!CreateAndAddVarInTable(child1->value.type_string, this_type, basedeep, child1->row)){
                fprintf(stderr,"Error type 3 at Line %d:  Redefined variable \" %s \".\n",child1->row,child1->value.type_string);
                return false;
            }
        }
        return true;
    }
    else {
        //数组定义
        struct Node* intnode = child1->brother->brother;
        Type array = CreateArrayType(this_type, intnode->value.type_int);
        return AnalasysForVarDec(child1, array, _structnode, _funcitem);
    }
}

// for ParamDec
bool AnalasysForParamDec(struct Node* ptr, Item* _funcitem){
    #ifdef DEBUG
        Log("In the ParamDec with funcitem %d", _funcitem->func_num);
    #endif
    Assert(strcmp(ptr->name,"ParamDec") == 0, "wrong at AnalasysForParamDec");

    struct Node* specifier = ptr->child;
    struct Node* vardec = specifier->brother;

    Type curtype = AnalasysForSpecifier(specifier);
    if(curtype == NULL){
        struct Node* tmp = specifier->child->child->brother;
        if(strcmp(tmp->name, "Tag") != 0){
            //说明不是struct A x; 其中strcut A未定义，而是是报错。
            return false;
        }
        else{
           fprintf(stderr,"Error type 17 at Line %d: Undefined struct \" %s\".\n",specifier->row,tmp->child->value.type_string);
           return false;
        }
    }

    return AnalasysForVarDec(vardec, curtype, NULL, _funcitem);
}


// for VarList
bool AnalasysForVarList(struct Node* ptr, Item* _funcitem){
    #ifdef DEBUG
        Log("In the VarList with funcitem %d", _funcitem->func_num);
    #endif
    Assert(strcmp(ptr->name,"VarList") == 0, "wrong at AnalasysForVarList");

    struct Node* paramdec = ptr->child;
    struct Node* comma = paramdec->brother;
    struct Node* varlist = NULL;
    paramsnum++;

    if(!AnalasysForParamDec(paramdec, _funcitem))
        return false;
    if(comma != NULL){
        varlist = comma->brother;
        return AnalasysForVarList(varlist, _funcitem);
    }
    return true;
}


// for FunDec
Item* AnalasysForFunDec(struct Node* ptr, Type this_type, int mode){
    #ifdef DEBUG
        Log("In the FunDec with type %d",this_type->kind);
    #endif
    Assert(strcmp(ptr->name,"FunDec") == 0, "wrong at AnalasysForFunDec");

    struct Node* id = ptr->child;
    struct Node* child3 = id->brother->brother;

    Item *funcitem  = GetItemByName(id->value.type_string, basedeep);
    if(funcitem == NULL){
        //表示当前为第一次申明或定义
        #ifdef DEBUG
        LogPurple("Fisrt times");
        #endif
        funcnum++;
        funcitem = CreateFunctionItem(funcnum, id->value.type_string, this_type, NONE, basedeep, id->row);
        Assert(funcitem!=NULL,"Wrong while create funcitem");
    }
    if(funcitem->symkind != FUNCTION) 
        Assert(0,"The name of Function cannot be the same as Variable.");
   
   //多次定义
    if(funcitem->funcinfo->status == DEFINE && mode == DEFINE){
        fprintf(stderr,"Error type 4 at Line %d: Redefined Function \" %s \".\n"
            ,id->row,id->value.type_string);
        return NULL;
    }

    //返回类型不一致
    if(funcitem->type != this_type){
        if(funcitem->funcinfo->status == DEFINE && mode == NONE){
            fprintf(stderr,"Error type 4 at Line %d: Redefined Function \" %s \".\n"
            ,id->row,id->value.type_string);
            return NULL;
        }
        fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
                ,id->row,id->value.type_string);
        return NULL;
    }
 
    if(strcmp(child3->name,"VarList") == 0){
        #ifdef DEBUG
        LogYellow("FunDec with VarList");
        #endif

        paramsnum = 0;//开始标记参数
        if(AnalasysForVarList(child3, funcitem)){
            funcitem->funcinfo->status = mode;
            return funcitem;
        }
        else {
            fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
                ,id->row,id->value.type_string);
            return NULL;
        }
            
    }
    else{
        #ifdef DEBUG
        LogYellow("FunDec with no VarList");
        #endif
        if(funcitem->paramnums != 0){
            //参数数量不一致
            if(funcitem->funcinfo->status == DEFINE && mode == NONE){
                fprintf(stderr,"Error type 4 at Line %d: Redefined Function \" %s \".\n"
                     ,id->row,id->value.type_string);
                return NULL;
            }
            fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
                    ,id->row,id->value.type_string);
            return NULL;
        }    
        funcitem->funcinfo->status = mode;
        return funcitem;
    }
}

// for Args
bool AnalasysForArgs(struct Node* ptr, Item* _funcitem){
    #ifdef DEBUG
    Log("In Args with function %d",_funcitem->func_num);
    #endif
    Assert(strcmp(ptr->name,"Args") == 0, "Wrong in Args");

    struct Node* exp = ptr->child;
    struct Node* comma = exp->brother;

    Type curtype = AnalasysForExp(exp);
    if(curtype == NULL)
        return false;
    paramsnum++;
    if(CheckArgInFunc(_funcitem, curtype, paramsnum) == false)
        return false;
    //参数过少,过多已经包含在Check调用中
    if(comma == NULL){
        if(paramsnum < _funcitem->paramnums)
            return false;
        else
            return true;
    }

    return AnalasysForArgs(comma->brother, _funcitem); 
}

//NOT 在Exp中已经处理
bool IS_LOGICALOP(struct Node* ptr){
    Assert(ptr != NULL,"Wrong in IS_LOGICALOP");
    if(strcmp(ptr->name,"AND") == 0)
        return true;
    if(strcmp(ptr->name,"OR") == 0)
        return true;
    return false;
}

bool IS_ARITHMETICOP(struct Node* ptr){
    Assert(ptr != NULL,"Wrong in IS_ARITHMETIC");
    if(strcmp(ptr->name,"RELOP") == 0)
        return true;
    if(strcmp(ptr->name,"PLUS") == 0)
        return true;
    if(strcmp(ptr->name,"MINUS") == 0)
        return true;
    if(strcmp(ptr->name,"STAR") == 0)
        return true;
    if(strcmp(ptr->name,"DIV") == 0)
        return true;
    return false;
}

// for Exp
Type AnalasysForExp(struct Node* ptr){
    #ifdef DEBUG
    Log("In the Exp");
    #endif
    Assert(strcmp(ptr->name,"Exp") == 0, "Wrong in Exp");

    struct Node* child1 = ptr->child;
    struct Node* child2 = NULL;
    struct Node* child3 = NULL;

    if(strcmp(child1->name,"INT") == 0){
        return GetTypeByName("int");
    }
    else if(strcmp(child1->name,"FLOAT") == 0){
        return GetTypeByName("float");
    }
    else if(strcmp(child1->name,"LP") == 0 || strcmp(child1->name,"MINUS") == 0){
        // LP Exp RP || MINUS Exp
        return AnalasysForExp(child1->brother);
    }
    else if(strcmp(child1->name,"NOT") == 0){
        //NOT Exp,逻辑运算
        Type rettype = AnalasysForExp(child1->brother);
        if(rettype == NULL)
            return NULL;
        if(rettype->kind == BASIC && rettype->u.basic == 0)
            return rettype;
        fprintf(stderr,"Error type 7 at Line %d: Type mismatch for NOT.\n",child1->brother->row);
        return NULL;
    }
    else if(strcmp(child1->name,"ID") == 0){
        //ID || ID LP Args RP || ID LP RP
        child2 = child1->brother;
        Item* tmpitem = NULL;
        for(int tmpdeep = basedeep; tmpdeep >= 0; --tmpdeep){
            tmpitem = GetItemByName(child1->value.type_string,tmpdeep);
            if(tmpitem != NULL)
                break;
        }
        if(child2 == NULL){
            //ID,变量
            if(tmpitem == NULL || tmpitem->symkind != VARIABLE){
                fprintf(stderr,"Error type 1 at Line %d: Undefined variable \" %s \".\n",child1->row,child1->value.type_string);
                return NULL;
            }
            return tmpitem->type;
        }
        else{
            //ID LP RP || ID LP Args RP
            if(tmpitem == NULL){
                fprintf(stderr,"Error type 2 at Line %d: Undefined function \" %s \".\n",child1->row,child1->value.type_string);
                return NULL;
            }
            //是否是函数
            if(tmpitem->symkind == VARIABLE){
                fprintf(stderr,"Error type 11 at Line %d: \" %s \" is not a function.\n",child1->row,child1->value.type_string);
                return NULL;
            }
            //参数是否匹配
            paramsnum = 0;
            child3 = child2->brother;
            //参数数目匹配
            if(strcmp(child3->name,"Args") == 0 && tmpitem->paramnums == 0){
                fprintf(stderr,"Error type 9 at Line %d: The number or type of the arguments is wrong in called function \" %s \".\n",child3->row,child1->value.type_string);
                return NULL;
            }
            if(strcmp(child3->name,"Args") != 0 && tmpitem->paramnums != 0){
                fprintf(stderr,"Error type 9 at Line %d: The number or type of the arguments is wrong in called function \" %s \".\n",child3->row,child1->value.type_string);
                return NULL;
            }
            //数目都为0
            if(strcmp(child3->name,"Args") != 0 && tmpitem->paramnums == 0){
                if(tmpitem->funcinfo->status == DECALARE)
                    calledfunc[tmpitem->func_num] = true;
                return tmpitem->type;
            }
                
            //数目均不为0
            if(AnalasysForArgs(child3,tmpitem) == false){
                fprintf(stderr,"Error type 9 at Line %d: The number or type of the arguments is wrong in called function \" %s \".\n",child3->row,child1->value.type_string);
                return NULL;
            }
            if(tmpitem->funcinfo->status == DECALARE)
                calledfunc[tmpitem->func_num] =true;
            return tmpitem->type;
        }
    }
    else if(strcmp(child1->name,"Exp") == 0){
        child2 = child1->brother;
        child3 = child2->brother;
        Type type1 = AnalasysForExp(child1);
        if(type1 == NULL)
            return NULL;
        if(strcmp(child2->name,"ASSIGNOP") == 0){
            if(strcmp(child1->child->name,"INT") == 0 || strcmp(child1->child->name,"FLOAT") == 0){
                fprintf(stderr,"Error type 6 at Line %d: The left of ASIIGNOP is Rvalue.\n",child1->row);
                return NULL;
            }
            Type type2 = AnalasysForExp(child3);
            if(type2 == NULL)
                return NULL;
            if(CheckTypes(type1,type2) == false){
                fprintf(stderr,"Error type 5 at Line %d: The type of the Exp on both sides of the ASSIGNOP does not match.\n",child2->row);
                return NULL;
            }
            return type1;
        }
        else if(IS_LOGICALOP(child2)){
            if((type1->kind != BASIC) || (type1->kind == BASIC && type1->u.basic != 0)){
                fprintf(stderr,"Error type 7 at Line %d: Operand types do not match or operand types do not match operators.\n",child1->row);
                return NULL;
            }
            Type type2 = AnalasysForExp(child3);
            if(type2 == NULL)
                return NULL;
            if((type2->kind != BASIC) || (type2->kind == BASIC && type2->u.basic != 0)){
                fprintf(stderr,"Error type 7 at Line %d: Operand types do not match or operand types do not match operators.\n",child2->row);
                return NULL;
            }
            return type1;
        }
        else if(IS_ARITHMETICOP(child2)){
            if(type1->kind != BASIC){
                fprintf(stderr,"Error type 7 at Line %d: Operand types do not match or operand types do not match operators.\n",child1->row);
                return NULL;
            }
            Type type2 = AnalasysForExp(child3);
            if(type2 == NULL)
                return NULL;
            if(CheckTypes(type1,type2) == false){
                fprintf(stderr,"Error type 7 at Line %d: Operand types do not match or operand types do not match operators.\n",child2->row);
                return NULL;
            }
            return type1;
        }
        else if(strcmp(child2->name,"LB") == 0){
            if(type1->kind != ARRAY){
                fprintf(stderr,"Error type 10 at Line %d: Cannot use \' [] \' operator when the variable is not an array.\n",child2->row);
                return NULL;
            }
            Type type2 = AnalasysForExp(child3);
            if(type2 == NULL) 
                return NULL;
            if(type2->kind != BASIC || (type2->kind == BASIC && type2->u.basic != 0)){
                fprintf(stderr,"Error type 12 at Line %d: The type of the Exp in [] operator is not \" int \".\n",child3->row);
                return NULL;
            }
            return type1->u.array.elem;
        }
        else if(strcmp(child2->name,"DOT") == 0){
            if(type1->kind != STRUCTURE){
                fprintf(stderr, "Error type 13 at Line %d: Cannot use \' . \' operator when the variable is not a struct.\n",child2->row);
                return NULL;
            }
            Type ret = FindFieldInStruct(type1, child3->value.type_string);
            if(ret == NULL){
                fprintf(stderr, "Error type 14 at Line %d: \" %s \" is not a field of the struct.\n",child3->row,child3->value.type_string);
                return NULL;
            }
            return ret;
        }
        else
            Assert(0,"No such a Operator");
    }
    else 
        Assert(0,"No such a production");
    
}

// for Dec
bool AnalasysForDec(struct Node* ptr, Type this_type, struct DTNode* _structnode){
    #ifdef DEBUG
    if(_structnode != NULL)
        Log("In the Dec with type %d, structnum %d",this_type->kind,_structnode->struct_num);
    else
        Log("In the Dec with type %d",this_type->kind);
    #endif

    Assert(strcmp(ptr->name,"Dec") == 0,"wrong at AnalasysForDec");
    struct Node* vardec = ptr->child;
    struct Node* assign = NULL;
    struct Node* exp = NULL;

    if(AnalasysForVarDec(vardec, this_type, _structnode, NULL) == false)
        return false;
    if(vardec->brother == NULL)
        return true;
    assign = vardec->brother;
    exp = assign->brother;
    if(structdeep > basedeep){
        fprintf(stderr,"Error type 15 at Line %d: Assigned variable whlie defining a struct.\n",exp->row);
        return false;
    }
    else{
        //CompSt内定义
        Type exptype = AnalasysForExp(exp);
        if(exptype == NULL)
            return false;
        else{
            if(CheckTypes(this_type,exptype))
                return true;
            fprintf(stderr,"Error type 5 at Line %d: The type of the Exp on both sides of the ASSIGNOP does not match.\n",assign->row);
            return false;
        }        
    }
}


// for DecList
bool AnalasysForDecList(struct Node* ptr, Type this_type, struct DTNode* _structnode){
    #ifdef DEBUG
    if(_structnode != NULL)
        Log("In the DecList with type %d, structnum %d",this_type->kind,_structnode->struct_num);
    else
        Log("In the DecList with type %d",this_type->kind);
    #endif

    Assert(strcmp(ptr->name,"DecList") == 0,"wrong at AnalasysForDecList");
    struct Node* dec = ptr->child;
    
    if(AnalasysForDec(dec,this_type,_structnode) == false)
        return false;
    if(dec->brother != NULL)
       return AnalasysForDecList(dec->brother->brother,this_type,_structnode);
    return true;
}

// for Def
/* 
* 如果要考虑结构体嵌套定义下的域名和结构体名冲突，
* 需要在其中调用AnalasysForSpecifier中加入参数_structnode
*/
bool AnalasysForDef(struct Node* ptr, struct DTNode* _structnode){
    #ifdef DEBUG
    if(_structnode != NULL)
        Log("In the Def with structnum %d",_structnode->struct_num);
    else
        Log("In the Def");
    #endif

    Assert(strcmp(ptr->name,"Def") == 0,"wrong at AnalasysForDef");
    struct Node* specifier  = ptr->child;
    struct Node* declist = specifier->brother;
    // struct Node* semi = declist->brother;

    Type curtype = AnalasysForSpecifier(specifier);
    if(curtype == NULL){
        struct Node* tmp = specifier->child->child->brother;
        if(strcmp(tmp->name,"Tag") != 0){
            //说明是报错
            return false;
        } 
        fprintf(stderr,"Error type 17 at Line %d: Undefined struct \" %s \".\n",tmp->row,tmp->child->value.type_string);
        return false;
    }
        
    return AnalasysForDecList(declist,curtype, _structnode);
}

// for DefList
bool AnalasysForDefList(struct Node* ptr, struct DTNode* _structnode){
    #ifdef DEBUG
    if(_structnode != NULL)
        Log("In the DefList with structnum %d",_structnode->struct_num);
    else
        Log("In the DefList");
    #endif

    if(ptr == NULL)
        return true;
    Assert(strcmp(ptr->name,"DefList") == 0,"wrong at AnalasysForDefList");
    struct Node* def = ptr->child;
    struct Node* deflist = def->brother;

    if(AnalasysForDef(def, _structnode) == false)
        return false;
    #ifdef DEBUG
        Log("After Def");
    #endif
    return AnalasysForDefList(deflist, _structnode);
}


// for Struct
/* 
* 如果要考虑结构体嵌套定义下的域名和结构体名冲突，
* 可以在此多加一个 _structnode 从而在创建的时候能否访问
* 该结构体所属的外层结构体的域列表。
*/
Type AnalasysForStruct(struct Node* ptr){
    #ifdef DEBUG
        Log("In the Struct");
    #endif

    Assert(strcmp(ptr->name,"StructSpecifier") == 0,"wrong at AnalasysForStruct");
    struct Node* child1 = ptr->child;
    struct Node* child2 = child1->brother;
    struct Node* child3 = child2->brother;
    Type ret = NULL;
    struct DTNode* structnode = NULL;

    if(child3 == NULL){
        /*
        * STRUCT Tag
        * 定义该结构体类型的变量
        */
        ret = GetTypeByName(child2->child->value.type_string);
        return ret;
    }
    else{
        /*
        * STRUCT OptTag LC DefList RC
        * 定义一个新的结构体类型
        * 重复定义仅需要根据是否同名
        */

        if(strcmp(child2->name,"LC") == 0){
            char *defualt_name = GetAStructName();
            //创建新结构体
            structdeep++;
            structnum++;
            structnode = CreateDTNodeForStruct(defualt_name, structnum);
            if(AnalasysForDefList(child3, structnode)){
                AddDTNodeForStruct(structnode);
                structdeep--;
                return &(structnode->type_);
            }
            structdeep--;
            return NULL;
        }
        else{
            struct Node* id = child2->child;
            //检查是否重名结构体
            if(GetTypeByName(id->value.type_string) != NULL){
                fprintf(stderr,"Error type 16 at Line %d: Redefined struct \" %s \".\n",id->row,id->value.type_string);
                return NULL;
            }
            //检查是否和Item的名字相同，注意此时要考虑的Item的deep <= basedeep.
            for(int tmpdeep = basedeep; tmpdeep >= 0; --tmpdeep){
                    if(GetItemByName(id->value.type_string, tmpdeep) != NULL){
                        fprintf(stderr,"Error type 16 at Line %d: Redefined \" %s \".\n",id->row,id->value.type_string);
                        return NULL;
                }
            }
            
            
            //无重定义,创建新结构体类型
            structdeep++;
            structnum++;
            structnode = CreateDTNodeForStruct(id->value.type_string, structnum);
            if(AnalasysForDefList(child3->brother, structnode)){
                AddDTNodeForStruct(structnode);
                structdeep--;
                return &(structnode->type_);
            }
            structdeep--;
            return NULL;
        }
            
    }

}

// for Specifier
/* 
* 如果要考虑结构体嵌套定义下的域名和结构体名冲突，
* 可以在此多加一个 _structnode 从而在创建的时候能否访问
* 该结构体所属的外层结构体的域列表。
*/
Type AnalasysForSpecifier(struct Node* ptr){
    #ifdef DEBUG
        Log("In the Specifier");
    #endif

    Assert(strcmp(ptr->name,"Specifier") == 0,"wrong at AnalasysForSpecifier");
    struct Node* child = ptr->child;
    Type ret = NULL;
    if(strcmp(child->name,"TYPE") == 0){
        ret = GetTypeByName(child->value.type_string);
        Assert(ret != NULL,"Wrong in Specifier");
        return ret;
    }
    else if(strcmp(child->name,"StructSpecifier") == 0){
        ret = AnalasysForStruct(child);
        return ret;
    }
    return NULL;
}

// for Stmt
bool AnalasysForStmt(struct Node* ptr, Type _functype){
    #ifdef DEBUG
    Log("In Stmt");
    #endif
    Assert(strcmp(ptr->name,"Stmt") == 0,"Wrong in Stmt");

    struct Node* child1 = ptr->child;
    if(strcmp(child1->name,"Exp") == 0){
        if(AnalasysForExp(child1) == NULL)
            return false;
    }
    else if(strcmp(child1->name,"CompSt") == 0)
        return AnalasysForCompSt(child1, _functype);
    else if(strcmp(child1->name,"RETURN") == 0){
        struct Node* exp = child1->brother;
        Type rettype = AnalasysForExp(exp);
        if(rettype == NULL || CheckTypes(_functype,rettype) == false){
            fprintf(stderr,"Error type 8 at Line %d: The type of RETURN mismacthed the type of the function.\n",exp->row);
            return false;
        }
        return true;
    }
    else if(strcmp(child1->name,"IF") == 0){
        struct Node* exp = child1->brother->brother;
        struct Node* stmt1 = exp->brother->brother;
        Type exptype = AnalasysForExp(exp);
        if(exptype == NULL || exptype->kind != BASIC || (exptype->kind == BASIC && exptype->u.basic != 0)){
            return false;
        }
        if(stmt1->brother == NULL){
            //没有ELSE
            return AnalasysForStmt(stmt1, _functype);
        }
        else{
            //有ELSE
            struct Node* stmt2 = stmt1->brother->brother;
            if(AnalasysForStmt(stmt1, _functype) == false)
                return false;
            return AnalasysForStmt(stmt2, _functype);
        }
    }
    else if(strcmp(child1->name,"WHILE") == 0){
        struct Node* exp = child1->brother->brother;
        struct Node* stmt = exp->brother->brother;
        Type exptype = AnalasysForExp(exp);
        if(exptype == NULL || exptype->kind != BASIC || (exptype->kind == BASIC && exptype->u.basic != 0)){
            return false;
        }
        return AnalasysForStmt(stmt,_functype);
    }
    else
        Assert(0,"Not such a production");
}

// for StmtList
bool AnalasysForStmtList(struct Node* ptr, Type _functype){
    #ifdef DEBUG
    Log("In StmtList");
    #endif
    if(ptr == NULL)
        return true;
    Assert(strcmp(ptr->name,"StmtList") == 0, "Wrong In StmtList");

    struct Node* stmt = ptr->child;
    struct Node* stmtlist = stmt->brother;
    
    if(AnalasysForStmt(stmt, _functype) == false)
        return false;
    return AnalasysForStmtList(stmtlist, _functype);
}


// for CompSt
bool AnalasysForCompSt(struct Node* ptr, Type _functype){
    #ifdef DEBUG
    Log("In CompSt");
    #endif
    Assert(strcmp(ptr->name,"CompSt") == 0, "Wrong In CompSt");
    basedeep++;

    struct Node* child2 = ptr->child->brother;
    struct Node* child3 = NULL;
    if(strcmp(child2->name,"DefList") == 0){
        if(AnalasysForDefList(child2, NULL) == false){
            basedeep--;
            return false;
        }
        child3 = child2->brother;
        if(strcmp(child3->name,"StmtList") == 0){
            if(AnalasysForStmtList(child3, _functype) == false){
                basedeep--;
                return false;
            }      
        }
    }  
    else if(strcmp(child2->name,"StmtList") == 0){
        if(AnalasysForStmtList(child2, _functype) == false){
            basedeep--;
            return false;
        }     
    }

    basedeep--;
    return true; 
}

// for ExtDecList
void AnalasysForExtDecList(struct Node* ptr, Type this_type){
    Assert(strcmp(ptr->name,"ExtDecList") == 0,"wrong at AnalasysForExtDecList");
    struct Node* vardec = ptr->child;
    AnalasysForVarDec(vardec,this_type,NULL,NULL);

    if(vardec->brother != NULL)
        AnalasysForExtDecList(vardec->brother->brother,this_type);
}

// for ExtDef
void AnalasysForExtDef(struct Node* ptr){
    #ifdef DEBUG
        Log("In the ExtDef");
    #endif

    Assert(strcmp(ptr->name,"ExtDef") == 0,"wrong at AnalasysForExtDef");
    struct Node* specifier = ptr->child;
    struct Node* child2 = specifier->brother;
    struct Node* child3 = child2->brother;

    Type curtype = AnalasysForSpecifier(specifier);
    if(curtype == NULL){
        /*
        * 可能1 struct A; 即 Specifier SEMI 后面处理了
        * 可能2 报错重复定义,如下处理
        */
       struct Node* tmp = specifier->child->child->brother;
       if(strcmp(tmp->name, "Tag") != 0){
            //说明不是struct A x; 其中strcut A未定义，而是是报错。
            return;
       }
       else if(child3 != NULL){
           fprintf(stderr,"Error type 17 at Line %d: Undefined struct \" %s\".\n",specifier->row,tmp->child->value.type_string);
           return;
       }
    }

    //Specifier SEMI
    if(child3 == NULL)
        return;
    //Specifier ExtDecList SEMI
    if(strcmp(child2->name, "ExtDecList") == 0)
        AnalasysForExtDecList(child2, curtype);
    //Specifier FunDec CompSt || Specifier FunDec SEMI
    else if(strcmp(child2->name, "FunDec") == 0){
        if(strcmp(child3->name, "SEMI") == 0){
            //Specifier FunDec SEMI
            Item* funcitem = AnalasysForFunDec(child2, curtype, DECALARE);
            if(funcitem != NULL)
            {
                AddFuncItemInTable(funcitem, basedeep);
            }
                
        }
        else{
            //Specifier FunDec CompSt
            Item* funcitem = AnalasysForFunDec(child2, curtype, NONE);
            if(funcitem != NULL){
                if(AnalasysForCompSt(child3, curtype)){
                    funcitem->funcinfo->status = DEFINE;
                    AddFuncItemInTable(funcitem, basedeep);
                }
            }
        }
    }
     
}

// for ExtDefList
void AnalasysForExtDefList(struct Node* ptr){
    #ifdef DEBUG
        Log("In the ExtDefList");
    #endif

    if(ptr == NULL)
        return;
    Assert(strcmp(ptr->name,"ExtDefList") == 0,"wrong at AnalasysBegins");

    struct Node* extdef = ptr->child;
    struct Node* extdeflist = extdef->brother;

    
    AnalasysForExtDef(extdef);
    AnalasysForExtDefList(extdeflist);
}

// for Program
void AnalasysForProgram(struct Node* ptr){
    #ifdef DEBUG
    Log("In Program");
    #endif
    Assert(strcmp(ptr->name,"Program") == 0, "Wrong in program");

    CreateAndAddDTNodeForBasic(basic_int);
    CreateAndAddDTNodeForBasic(basic_float);
    
    memset(calledfunc,0, HTSIZE*sizeof(bool));
    struct Node* extdeflist = ptr->child;
    AnalasysForExtDefList(extdeflist);
    
    //查看哪些函数声明但未定义
    for(int i = 1; i <= funcnum; ++i){
        Item* funcitem = FuncList[i];
        if(funcitem != NULL && funcitem->funcinfo->status != DEFINE){
            fprintf(stderr,"Error type 18 at Line %d: Function \" %s \" is decalared but not be defined.\n",funcitem->rownum,funcitem->name);
            if(calledfunc[i] == true){
                fprintf(stderr,"Error type 2 at Line %d: Function \" %s \" is called but not be defined.\n",funcitem->rownum,funcitem->name);
            }
        }
    }

}