#include "SymTable.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*----------------------------functions declaration------------------------*/
Type AnalasysForSpecifier(struct Node* ptr);


/*----------------------------static variables------------------------*/
static int basedeep = 0;//函数
static int structdeep = 0;//防止结构体嵌套定义
//当进入一个函数Compst时需要structdeep = basedeep
static int structnum = 0;//第几个结构体




/*----------------------------functions definition------------------------*/

// for VarDec
void AnalasysForVarDec(struct Node* ptr,Type this_type, int _structnum){
#ifdef DEBUG
    Log("In the VarDec with type %d, structnum %d",this_type->kind,_structnum);
#endif

    Assert(strcmp(ptr->name,"VarDec") == 0,"wrong at AnalasysForVarDec");
    struct Node* child1 = ptr->child;
    if(strcmp(child1->name,"ID") == 0){
        //在定义结构体中
        if(structdeep != basedeep){
            if(!AddFieldInStruct(_structnum, child1->value.type_string, this_type)){
                fprintf(stderr,"Error type 15 at Line %d: Redefined field \" %s \".\n",child1->row,child1->value.type_string);
                return;
            }
        }
        else{
            TODO();
        }
        
    }
    else {
        //数组定义
        struct Node* intnode = child1->brother->brother;
        Type array = CreateArrayType(this_type, intnode->value.type_int);
        AnalasysForVarDec(child1, array, _structnum);
    }
}


// for Dec
void AnalasysForDec(struct Node* ptr, Type this_type, int _structnum){
#ifdef DEBUG
    Log("In the Dec with type %d, structnum %d",this_type->kind,_structnum);
#endif

    Assert(strcmp(ptr->name,"Dec") == 0,"wrong at AnalasysForDec");
    struct Node* vardec = ptr->child;
    struct Node* assign = NULL;
    struct Node* exp = NULL;

    AnalasysForVarDec(vardec,this_type, _structnum);
    if(vardec->brother == NULL)
        return;
    assign = vardec->brother;
    exp = assign->brother;
    if(structdeep != basedeep){
        fprintf(stderr,"Error type 15 at Line %d: Assigned variable whlie defining a struct.\n",exp->row);
        return;
    }
    TODO();
}


// for DecList
void AnalasysForDecList(struct Node* ptr, Type this_type, int _structnum){
#ifdef DEBUG
    Log("In the DecList with type %d, structnum %d",this_type->kind,_structnum);
#endif

    Assert(strcmp(ptr->name,"DecList") == 0,"wrong at AnalasysForDecList");
    struct Node* dec = ptr->child;
    
    AnalasysForDec(dec,this_type,_structnum);
    if(dec->brother != NULL)
        AnalasysForDecList(dec->brother->brother,this_type,_structnum);
}

// for Def
void AnalasysForDef(struct Node* ptr, int _structnum){
#ifdef DEBUG
    Log("In the Def with structnum %d",_structnum);
#endif

    Assert(strcmp(ptr->name,"Def") == 0,"wrong at AnalasysForDef");
    struct Node* specifier  = ptr->child;
    struct Node* declist = specifier->brother;
    // struct Node* semi = declist->brother;

    Type curtype = AnalasysForSpecifier(specifier);
    if(curtype == NULL)
        return;
    AnalasysForDecList(declist,curtype,_structnum);
}

// for DefList
void AnalasysForDefList(struct Node* ptr, int _structnum){
#ifdef DEBUG
    Log("In the DefList with structnum %d",_structnum);
#endif

    if(ptr == NULL)
        return;
    Assert(strcmp(ptr->name,"DefList") == 0,"wrong at AnalasysForDefList");
    struct Node* def = ptr->child;
    struct Node* deflist = def->brother;

    AnalasysForDef(def, _structnum);
#ifdef DEBUG
    Log("After Def");
#endif
    AnalasysForDefList(deflist, _structnum);
}


// for Struct
Type AnalasysForStruct(struct Node* ptr){
#ifdef DEBUG
    Log("In the Struct");
#endif

    Assert(strcmp(ptr->name,"StructSpecifier") == 0,"wrong at AnalasysForStruct");
    struct Node* child1 = ptr->child;
    struct Node* child2 = child1->brother;
    struct Node* child3 = child2->brother;
    Type ret = NULL;

    if(child3 == NULL){
        /*
        * STRUCT Tag
        * 定义该结构体类型的变量
        */
        ret = GetTypeByName(child2->value.type_string);
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
            CreateAndAddDTNodeForStruct(defualt_name, structnum, basedeep);
            AnalasysForDefList(child3, structnum);
            //建完结构体
            structdeep--;
            ret = GetTypeByName(defualt_name);
            Assert(ret,"build struct error.");
            return ret;
        }
        else{
            struct Node* id = child2->child;
            if(GetTypeByName(id->value.type_string)){
                fprintf(stderr,"Error type 16 at Line %d: Redefined struct \" %s \".\n",id->row,id->value.type_string);
                return NULL;
            }
            //检查是否和Item的名字相同
            if(GetItemByName(id->value.type_string,basedeep)){
                fprintf(stderr,"Error type 16 at Line %d: Redefined struct \" %s \".\n",id->row,id->value.type_string);
                return NULL;
            }
            
            //无重定义,创建新结构体类型
            structdeep++;
            structnum++;
            CreateAndAddDTNodeForStruct(id->value.type_string, structnum, basedeep);
#ifdef DEBUG
            Log("After Create Struct Node");
#endif
            AnalasysForDefList(child3->brother, structnum);
#ifdef DEBUG
            Log("After Analasys From DefList");
#endif
            //建完结构体
            structdeep--;
            ret = GetTypeByName(id->value.type_string);
            Assert(ret,"build struct error.");
#ifdef DEBUG
            Log("Get First Struct type");
#endif
            return ret;
        }
            
    }

}

// for Specifier
Type AnalasysForSpecifier(struct Node* ptr){
#ifdef DEBUG
    Log("In the Specifier");
#endif

    Assert(strcmp(ptr->name,"Specifier") == 0,"wrong at AnalasysForSpecifier");
    struct Node* child = ptr->child;
    Type ret = NULL;
    if(strcmp(child->name,"TYPE") == 0){
        ret = GetTypeByName(child->value.type_string);
        if(ret == NULL)
            ret = CreateAndAddDTNodeForBasic(child->value.type_string);
        return ret;
    }
    else if(strcmp(child->name,"StructSpecifier") == 0){
        ret = AnalasysForStruct(child);
        return ret;
    }
    return NULL;
}

// for ExtDecList
void AnalasysForExtDecList(struct Node* ptr, Type this_type){
    Assert(strcmp(ptr->name,"ExtDecList") == 0,"wrong at AnalasysForExtDecList");
    struct Node* vardec = ptr->child;
    AnalasysForVarDec(vardec,this_type,0);//0 means is not a struct

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
    //Specifier FunDec CompSt
    else if(strcmp(child2->name, "FunDec") == 0)
        TODO();
}

// for ExtDefList
void AnalasysBegins(struct Node* ptr){
#ifdef DEBUG
    Log("In the Begins");
#endif

    if(ptr == NULL)
        return;
    Assert(strcmp(ptr->name,"ExtDefList") == 0,"wrong at AnalasysBegins");

    struct Node* extdef = ptr->child;
    struct Node* extdeflist = extdef->brother;

    
    AnalasysForExtDef(extdef);
    AnalasysBegins(extdeflist);
}