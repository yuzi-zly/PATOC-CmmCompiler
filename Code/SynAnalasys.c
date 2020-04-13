#include "SymTable.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*----------------------------functions declaration------------------------*/
Type AnalasysForSpecifier(struct Node* ptr);
Type AnalasysForExp(struct Node* ptr, Item* _funcitem);
bool AnalasysForCompSt(struct Node* ptr, Item* _funcitem);

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
static bool need_add_func = true;

extern Item* FuncList[HTSIZE];

/*----------------------------functions definition------------------------*/

// for VarDec
//_structnode 用于添加结构体域名，默认为NULL
//_funcitem 用于添加函数参数，默认为NULL
//如果需要防止局部变量和参数名冲突，_infuncitem 表示在该函数中定义局部变量，默认为NULL
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
                AddParamInFunc(_funcitem, child1->value.type_string, this_type, child1->row);
                return true;
            }
            else{
                return CheckParamInFunc(_funcitem, child1->value.type_string, this_type, paramsnum, child1->row);
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
    bool retflag = true;
    paramsnum++;

    if(!AnalasysForParamDec(paramdec, _funcitem))
        retflag = false;
    if(comma != NULL){
        varlist = comma->brother;
        if(retflag == true)
            retflag = AnalasysForVarList(varlist, _funcitem);
        else 
            AnalasysForVarList(varlist, _funcitem);
    }
    return retflag;
}


// for FunDec
Item* AnalasysForFunDec(struct Node* ptr, Type this_type, int mode){
    #ifdef DEBUG
        Log("In the FunDec with type %d",this_type->kind);
    #endif
    Assert(strcmp(ptr->name,"FunDec") == 0, "wrong at AnalasysForFunDec");

    struct Node* id = ptr->child;
    struct Node* child3 = id->brother->brother;
    bool first = false;

    Item *funcitem  = GetItemByName(id->value.type_string, basedeep);
    if(funcitem == NULL){
        //表示当前为第一次申明或定义
        #ifdef DEBUG
        LogPurple("Fisrt times");
        #endif
        first = true;
        funcnum++;
        funcitem = CreateFunctionItem(funcnum, id->value.type_string, this_type, NONE, basedeep, id->row);
        Assert(funcitem!=NULL,"Wrong while create funcitem");
    }
    if(funcitem->symkind != FUNCTION) 
        Assert(0,"The name of Function cannot be the same as Variable.");

    
    if(mode == DECALARE){
        //声明
        //返回类型不一致
        if(funcitem->type != this_type){
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
                if(funcitem->funcinfo->status != DEFINE) 
			funcitem->funcinfo->status = mode;
                return funcitem;
            }
            else {
                if(first == false){
                     fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
                    ,id->row,id->value.type_string);
                    return NULL;
                }
                else
                    return NULL;  
            }
        }
        else{
             #ifdef DEBUG
            LogYellow("FunDec with no VarList");
            #endif
            if(funcitem->paramnums != 0){
                //参数数量不一致
                fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
                    ,id->row,id->value.type_string);
                return NULL;
            }
	    if(funcitem->funcinfo->status != DEFINE)    
            	funcitem->funcinfo->status = mode;
            return funcitem;
        }
    }
    else if(mode == NONE){
        //定义
        Item* this_item = NULL;
        if(first == false){
            funcnum++;
            this_item = CreateFunctionItem(funcnum, id->value.type_string, this_type, NONE, basedeep,id->row);
            Assert(this_item!=NULL,"Wrong while create funcitem");
        }
            
        //多次定义,一定不是第一次,以第一次为准
        if(funcitem->funcinfo->status == DEFINE){
            fprintf(stderr,"Error type 4 at Line %d: Redefined Function \" %s \".\n"
                ,id->row,id->value.type_string);
            need_add_func = false;
            if(strcmp(child3->name,"VarList") == 0){
                #ifdef DEBUG
                LogYellow("FunDec with VarList");
                #endif
                paramsnum = 0;//开始标记参数
                AnalasysForVarList(child3, this_item);
            }
            return this_item;
        }

         //返回类型不一致,一定不是第一次，以定义为准
        if(funcitem->type != this_type){
            fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
                    ,id->row,id->value.type_string);
            need_add_func = false;
            if(strcmp(child3->name,"VarList") == 0){
                #ifdef DEBUG
                LogYellow("FunDec with VarList");
                #endif
                paramsnum = 0;//开始标记参数
                AnalasysForVarList(child3, this_item);
            }
            ExchangeFuncItem(funcitem,this_item);
            return this_item;
        }

        //正常，此时funcitem->funcinfo->status == DECALARE
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
                //定义与声明参数不一致，以定义为准
                if(first == false){
                    fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
                        ,id->row,id->value.type_string);
                    AnalasysForVarList(child3,this_item);
                    ExchangeFuncItem(funcitem,this_item);
                    need_add_func = false;//因为在exchange里面已经存了
                    return this_item;
                }
                else
                    return funcitem;  
            }    
        }
        else{
            #ifdef DEBUG
            LogYellow("FunDec with no VarList");
            #endif
            if(funcitem->paramnums != 0){
                //参数数量不一致
                fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
                    ,id->row,id->value.type_string);
                ExchangeFuncItem(funcitem,this_item);
                need_add_func = false;
                return this_item;
            }    
            funcitem->funcinfo->status = mode;
            return funcitem;
        }
    }

    
   
   

    // //返回类型不一致
    // if(funcitem->type != this_type){
    //     fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
    //             ,id->row,id->value.type_string);
    //     return NULL;
    // }
 
    // if(strcmp(child3->name,"VarList") == 0){
    //     #ifdef DEBUG
    //     LogYellow("FunDec with VarList");
    //     #endif

    //     paramsnum = 0;//开始标记参数
    //     if(AnalasysForVarList(child3, funcitem)){
    //         funcitem->funcinfo->status = mode;
    //         return funcitem;
    //     }
    //     else {
    //         if(first == false){
    //              fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
    //             ,id->row,id->value.type_string);
    //             return NULL;
    //         }
    //         else
    //             return NULL;  
    //     }
            
    // }
    // else{
    //     #ifdef DEBUG
    //     LogYellow("FunDec with no VarList");
    //     #endif
    //     if(funcitem->paramnums != 0){
    //         //参数数量不一致
    //         fprintf(stderr,"Error type 19 at Line %d: Conflict between declarations and definitions with Function \" %s \".\n"
    //                 ,id->row,id->value.type_string);
    //         return NULL;
    //     }    
    //     funcitem->funcinfo->status = mode;
    //     return funcitem;
    // }
}

// for Args
bool AnalasysForArgs(struct Node* ptr,Item* _calleditem, Item* _funcitem){
    #ifdef DEBUG
    Log("In Args with called function %d and in function %d",_calleditem->func_num,_funcitem->func_num);
    #endif
    Assert(strcmp(ptr->name,"Args") == 0, "Wrong in Args");

    struct Node* exp = ptr->child;
    struct Node* comma = exp->brother;

    Type curtype = AnalasysForExp(exp, _funcitem);
    if(curtype == NULL)
        return false;
    paramsnum++;
    if(CheckArgInFunc(_calleditem, curtype, paramsnum) == false)
        return false;
    //参数过少,过多已经包含在Check调用中
    if(comma == NULL){
        if(paramsnum < _calleditem->paramnums)
            return false;
        else
            return true;
    }

    return AnalasysForArgs(comma->brother,_calleditem, _funcitem); 
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
// _funcitem 用于读取函数参数
Type AnalasysForExp(struct Node* ptr, Item* _funcitem){
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
        return AnalasysForExp(child1->brother,_funcitem);
    }
    else if(strcmp(child1->name,"NOT") == 0){
        //NOT Exp,逻辑运算
        Type rettype = AnalasysForExp(child1->brother,_funcitem);
        if(rettype == NULL)
            return NULL;
        if(rettype->kind == BASIC && rettype->u.basic == 0)
            return rettype;
        fprintf(stderr,"Error type 7 at Line %d: Type mismatch for NOT.\n",child1->brother->row);
        return NULL;
    }
    else if(strcmp(child1->name,"ID") == 0){
        //ID || ID LP Args RP || ID LP RP
        #ifdef DEBUG
        LogYellow("ID name %s.",child1->value.type_string);
        #endif
        child2 = child1->brother;
        Item* tmpitem = NULL;
        Type paramtype = NULL;
        //内部变量
        for(int tmpdeep = basedeep; tmpdeep > 0; --tmpdeep){
            tmpitem = GetItemByName(child1->value.type_string,tmpdeep);
            if(tmpitem != NULL)
                break;
        }
        if(tmpitem == NULL && _funcitem != NULL){
            if(strcmp(child1->value.type_string,_funcitem->name) == 0)
                tmpitem = _funcitem;
        }
        //函数参数
        if(tmpitem == NULL){
            paramtype = GetParamInFunction(child1->value.type_string, _funcitem);
        }
        if(tmpitem == NULL && paramtype == NULL)
            tmpitem = GetItemByName(child1->value.type_string, 0);

        if(child2 == NULL){
            //ID,变量
            if((tmpitem == NULL || tmpitem->symkind != VARIABLE) && paramtype == NULL){
                fprintf(stderr,"Error type 1 at Line %d: Undefined variable \" %s \".\n",child1->row,child1->value.type_string);
                return NULL;
            }
            if(tmpitem != NULL)
                return tmpitem->type;
            else
                return paramtype;
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
            if(AnalasysForArgs(child3,tmpitem,_funcitem) == false){
                fprintf(stderr,"Error type 9 at Line %d: The number or type of the arguments is wrong in called function \" %s \".\n",child3->row,child1->value.type_string);
                return NULL;
            }
            if(tmpitem->funcinfo->status == DECALARE)
                calledfunc[tmpitem->func_num] = true;
            return tmpitem->type;
        }
    }
    else if(strcmp(child1->name,"Exp") == 0){
        child2 = child1->brother;
        child3 = child2->brother;
        Type type1 = AnalasysForExp(child1,_funcitem);
        if(type1 == NULL)
            return NULL;
        if(strcmp(child2->name,"ASSIGNOP") == 0){
            if(strcmp(child1->child->name,"INT") == 0 || strcmp(child1->child->name,"FLOAT") == 0){
                fprintf(stderr,"Error type 6 at Line %d: The left of ASIIGNOP is Rvalue.\n",child1->row);
                return NULL;
            }
            //函数
            if(strcmp(child1->child->name,"ID") == 0 && (child1->child->brother != NULL && strcmp(child1->child->brother->name,"LP") == 0)){
                fprintf(stderr,"Error type 6 at Line %d: The left of ASIIGNOP is Rvalue.\n",child1->row);
                return NULL;
            }
            Type type2 = AnalasysForExp(child3,_funcitem);
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
            Type type2 = AnalasysForExp(child3,_funcitem);
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
            Type type2 = AnalasysForExp(child3,_funcitem);
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
            Type type2 = AnalasysForExp(child3,_funcitem);
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
bool AnalasysForDec(struct Node* ptr, Type this_type, struct DTNode* _structnode, Item* _infuncitem){
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
        Type exptype = AnalasysForExp(exp, _infuncitem);
        if(exptype == NULL)
            return false;
        else{
            while(strcmp(vardec->child->name,"ID") != 0){
                vardec = vardec->child;
            }
            Item* vardecitem = GetItemByName(vardec->child->value.type_string,basedeep);
            if(CheckTypes(vardecitem->type,exptype))
                return true;
            fprintf(stderr,"Error type 5 at Line %d: The type of the Exp on both sides of the ASSIGNOP does not match.\n",assign->row);
            return false;
        }        
    }
}


// for DecList
bool AnalasysForDecList(struct Node* ptr, Type this_type, struct DTNode* _structnode, Item* _infuncitem){
    #ifdef DEBUG
    if(_structnode != NULL)
        Log("In the DecList with type %d, structnum %d",this_type->kind,_structnode->struct_num);
    else
        Log("In the DecList with type %d",this_type->kind);
    #endif

    Assert(strcmp(ptr->name,"DecList") == 0,"wrong at AnalasysForDecList");
    struct Node* dec = ptr->child;
    bool retflag = true;

    if(AnalasysForDec(dec,this_type,_structnode,_infuncitem) == false)
        retflag = false;
    if(dec->brother != NULL){
        if(retflag == true)
            retflag = AnalasysForDecList(dec->brother->brother,this_type,_structnode,_infuncitem);
        else
            AnalasysForDecList(dec->brother->brother,this_type,_structnode,_infuncitem);
    }
    return retflag;
}

// for Def
/* 
* 如果要考虑结构体嵌套定义下的域名和结构体名冲突，
* 需要在其中调用AnalasysForSpecifier中加入参数_structnode
*/
bool AnalasysForDef(struct Node* ptr, struct DTNode* _structnode, Item* _infuncitem){
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
        
    return AnalasysForDecList(declist,curtype, _structnode, _infuncitem);
}

// for DefList
bool AnalasysForDefList(struct Node* ptr, struct DTNode* _structnode, Item* _infuncitem){
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
    bool retflag = true;

    if(AnalasysForDef(def, _structnode, _infuncitem) == false)
        retflag = false;
    #ifdef DEBUG
        Log("After Def");
    #endif
    if(retflag == true)
        retflag = AnalasysForDefList(deflist, _structnode, _infuncitem);
    else   
        AnalasysForDefList(deflist, _structnode, _infuncitem);
    return retflag;
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
        if(ret == NULL || ret->struct_status == DEFINED)
            return ret;
        else
            return NULL;
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
            structnode->type_.struct_status = BUILDING;
            if(strcmp(child3->name,"DefList") == 0){
                AnalasysForDefList(child3, structnode, NULL);
            }
            structnode->type_.struct_status = DEFINED;      
            AddDTNodeForStruct(structnode);
            structdeep--;
            return &(structnode->type_);
        }
        else{
            struct Node* id = child2->child;
            bool retflag = true;
            //检查是否重名结构体
            if(GetTypeByName(id->value.type_string) != NULL){
                fprintf(stderr,"Error type 16 at Line %d: Redefined struct \" %s \".\n",id->row,id->value.type_string);
                retflag = false;
            }
            //检查是否和Item的名字相同，注意此时要考虑的Item的deep <= basedeep.
            for(int tmpdeep = basedeep; tmpdeep >= 0; --tmpdeep){
                    if(GetItemByName(id->value.type_string, tmpdeep) != NULL){
                        fprintf(stderr,"Error type 16 at Line %d: Redefined \" %s \".\n",id->row,id->value.type_string);
                        retflag = false;
                }
            }
            
            
            //无重定义,创建新结构体类型
            structdeep++;
            structnum++;
            structnode = CreateDTNodeForStruct(id->value.type_string, structnum);
            structnode->type_.struct_status = BUILDING;
            if(retflag == true){
                AddDTNodeForStruct(structnode);
            }      
            if(strcmp(child3->brother->name,"DefList") == 0){
                AnalasysForDefList(child3->brother, structnode, NULL);
            }          
            structnode->type_.struct_status = DEFINED;
            if(retflag == true){        
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
bool AnalasysForStmt(struct Node* ptr, Item* _funcitem){
    #ifdef DEBUG
    Log("In Stmt");
    #endif
    Assert(strcmp(ptr->name,"Stmt") == 0,"Wrong in Stmt");

    struct Node* child1 = ptr->child;
    if(strcmp(child1->name,"Exp") == 0){
        if(AnalasysForExp(child1, _funcitem) == NULL){
            return false;
        }        
    }
    else if(strcmp(child1->name,"CompSt") == 0)
        return AnalasysForCompSt(child1, _funcitem);
    else if(strcmp(child1->name,"RETURN") == 0){
        struct Node* exp = child1->brother;
        Type rettype = AnalasysForExp(exp, _funcitem);
        if(rettype == NULL || (_funcitem != NULL && CheckTypes(_funcitem->type,rettype) == false)){
            fprintf(stderr,"Error type 8 at Line %d: The type of RETURN mismacthed the type of the function.\n",exp->row);
            return false;
        }
        return true;
    }
    else if(strcmp(child1->name,"IF") == 0){
        struct Node* exp = child1->brother->brother;
        struct Node* stmt1 = exp->brother->brother;
        Type exptype = AnalasysForExp(exp,_funcitem);
        bool retflag = true;
        if(exptype == NULL || exptype->kind != BASIC || (exptype->kind == BASIC && exptype->u.basic != 0)){
            retflag = false;
        }
        if(stmt1->brother == NULL){
            //没有ELSE
            if(retflag == true)
                return AnalasysForStmt(stmt1, _funcitem);
            else
            {
                AnalasysForStmt(stmt1, _funcitem);
                return false;
            }         
        }
        else{
            //有ELSE
            struct Node* stmt2 = stmt1->brother->brother;
            if(AnalasysForStmt(stmt1, _funcitem) == false)
                retflag = false;
            if(retflag == true)
                return AnalasysForStmt(stmt2, _funcitem);
            else
            {
                AnalasysForStmt(stmt2, _funcitem);
                return false;
            }            
        }
    }
    else if(strcmp(child1->name,"WHILE") == 0){
        struct Node* exp = child1->brother->brother;
        struct Node* stmt = exp->brother->brother;
        bool retflag = true;
        Type exptype = AnalasysForExp(exp,_funcitem);
        if(exptype == NULL || exptype->kind != BASIC || (exptype->kind == BASIC && exptype->u.basic != 0)){
            retflag = false;
        }
        if(retflag == true)
            return AnalasysForStmt(stmt,_funcitem);
        else
        {
            AnalasysForStmt(stmt,_funcitem);
            return false;
        }
        
    }
    else
        Assert(0,"Not such a production");
    return true;
}

// for StmtList
bool AnalasysForStmtList(struct Node* ptr, Item* _funcitem){
    #ifdef DEBUG
    Log("In StmtList");
    #endif
    if(ptr == NULL)
        return true;
    Assert(strcmp(ptr->name,"StmtList") == 0, "Wrong In StmtList");

    struct Node* stmt = ptr->child;
    struct Node* stmtlist = stmt->brother;
    bool retflag = true;
    
    if(AnalasysForStmt(stmt, _funcitem) == false){
        retflag = false;
    }
    if(retflag == true)
        retflag = AnalasysForStmtList(stmtlist, _funcitem);
    else
        AnalasysForStmtList(stmtlist, _funcitem);
    return retflag;
}


// for CompSt
bool AnalasysForCompSt(struct Node* ptr, Item* _funcitem){
    #ifdef DEBUG
    LogRed("In CompSt");
    #endif
    Assert(strcmp(ptr->name,"CompSt") == 0, "Wrong In CompSt");
    basedeep++;
    structdeep = basedeep;

    struct Node* child2 = ptr->child->brother;
    struct Node* child3 = NULL;
    bool retflag = true;
    if(strcmp(child2->name,"DefList") == 0){
        if(AnalasysForDefList(child2, NULL, _funcitem) == false){
            retflag = false;
        }
        child3 = child2->brother;
        if(strcmp(child3->name,"StmtList") == 0){
            if(AnalasysForStmtList(child3, _funcitem) == false){
                retflag = false;
            }      
        }
    }  
    else if(strcmp(child2->name,"StmtList") == 0){
        if(AnalasysForStmtList(child2, _funcitem) == false){
            retflag = false;
        }     
    }
    DeleteItemInDeep(basedeep);
    basedeep--;
    structdeep = basedeep;
    #ifdef DEBUG
    LogRed("CompSt return %d",retflag);
    #endif
    return retflag; 
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
        need_add_func = true;
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
            AnalasysForCompSt(child3, funcitem);
            funcitem->funcinfo->status = DEFINE;
            if(need_add_func == true)
                AddFuncItemInTable(funcitem, basedeep);
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
        else if(funcitem == NULL){
            if(calledfunc[i] == true){
                fprintf(stderr,"Error type 2 at Line %d: Function \" %s \" is called but not be defined.\n",funcitem->rownum,funcitem->name);
            }
        }
    }

}
