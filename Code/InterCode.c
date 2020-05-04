#include "SymTable.h"
#include "InterCode.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct InterCodes* ICHead = NULL;
extern int var_num;
extern int lab_num;
extern int tvar_num;
char* myitoa(int num, char* str);


/*----------------- Operand -----------------*/
Operand CreateOperand(int kind){
    #ifdef L3DEBUG
        LogYellow("In CreateOperand with kind %d",kind);
    #endif

    Operand ret = (Operand)malloc(sizeof(struct Operand_));
    memset(ret,0,sizeof(struct Operand_));
    ret->kind = kind;

    return ret;
}




/*----------------- InterCode -----------------*/
static void AddInterCode(struct InterCode* intercode){
    #ifdef L3DEBUG
        LogPurple("In AddInterCode");
    #endif

    struct InterCodes* newnode = (struct InterCodes*)malloc(sizeof(struct InterCodes));
    memset(newnode,0,sizeof(struct InterCodes));
    newnode->code = intercode;
    if(ICHead == NULL)
        ICHead = newnode;
    else{
        struct InterCodes* index = ICHead;
        while(index->next != NULL){
            index = index->next;
        }
        index->next = newnode;
        newnode->prev = index;
    }
}

int CalculateSize(Type type){
    #ifdef L3DEBUG
        LogPurple("In CalculateSize");
    #endif

    int ret = 0;
    if(type->kind == ARRAY){
        ret = type->u.array.size * CalculateSize(type->u.array.elem);
    }
    else if(type->kind == STRUCTURE){
        FieldList sptr = type->u.structure;
        while(sptr != NULL){
            ret += CalculateSize(sptr->type);
            sptr = sptr->tail;
        }
    }
    else if(type->kind == BASIC){
        ret = 4;
    }
    return ret;
}

void CreateAndAddFunctionIC(char* funcname){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddFunctionIC with funcname: %s",funcname);
    #endif

    struct InterCode* funccode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(funccode,0,sizeof(struct InterCode));
    funccode->IC_type = IC_FUNC;

    Operand function = CreateOperand(Ope_FUNC);
    function->u.funcname = funcname;
    funccode->u.ic_func.function = function;

    AddInterCode(funccode);
}

void CreateAndAddParamIC(Item* funcitem){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddParamIC with funcname: %s",funcitem->name);
    #endif

    FieldList params = funcitem->funcinfo->params;
    for(FieldList index = params; index != NULL; index = index->tail){
        struct InterCode* paramcode = (struct InterCode*)malloc(sizeof(struct InterCode));
        memset(paramcode,0,sizeof(struct InterCode));
        paramcode->IC_type = IC_PARAM;
        index->var_no = var_num++;

        if(index->type->kind == BASIC){
            Operand param = CreateOperand(Ope_VAR);
            param->u.var_no = index->var_no;
            paramcode->u.ic_param.param = param;
        }
        else{
            Operand param = CreateOperand(Ope_VAR);
            param->u.var_no = index->var_no;
            paramcode->u.ic_param.param = param;
        }
        
        AddInterCode(paramcode);
    }

}

void CreateAndAddDecIC(int var_no, Type this_type){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddDecIC with var_no: %d",var_no);
    #endif

    int size = CalculateSize(this_type);

    struct InterCode* deccode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(deccode,0,sizeof(struct InterCode));
    deccode->IC_type = IC_DEC;

    Operand var = CreateOperand(Ope_VAR);
    var->u.var_no = var_no;
    deccode->u.ic_dec.var = var;
    deccode->u.ic_dec.size = size;

    AddInterCode(deccode);
}

void CreateAndAddAssignIC(Operand left, Operand right){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddAssignIC with rightkind: %d, leftkind: %d",right->kind,left->kind);
    #endif

    struct InterCode* asscode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(asscode,0,sizeof(struct InterCode));
    asscode->IC_type = IC_ASSIGN;

    asscode->u.ic_assign.left = left;
    asscode->u.ic_assign.right = right;

    AddInterCode(asscode);
}

void CreateAndAddAddIC(Operand left,Operand right1, Operand right2){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddAddIC with leftkind: %d, right1kind: %d, right2kind: %d",left->kind,right1->kind,right2->kind);
    #endif

    struct InterCode* addcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(addcode,0,sizeof(struct InterCode));
    addcode->IC_type = IC_ADD;

    addcode->u.ic_add.left = left;
    addcode->u.ic_add.right1 = right1;
    addcode->u.ic_add.right2 = right2;
    
    AddInterCode(addcode);
}

void CreateAndAddSubIC(Operand left,Operand right1, Operand right2){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddSubIC with leftkind: %d, right1kind: %d, right2kind: %d",left->kind,right1->kind,right2->kind);
    #endif

    struct InterCode* subcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(subcode,0,sizeof(struct InterCode));
    subcode->IC_type = IC_SUB;

    subcode->u.ic_sub.left = left;
    subcode->u.ic_sub.right1 = right1;
    subcode->u.ic_sub.right2 = right2;
    
    AddInterCode(subcode);
}

void CreateAndAddMulIC(Operand left,Operand right1, Operand right2){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddMulIC with leftkind: %d, right1kind: %d, right2kind: %d",left->kind,right1->kind,right2->kind);
    #endif

    struct InterCode* mulcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(mulcode,0,sizeof(struct InterCode));
    mulcode->IC_type = IC_MUL;

    mulcode->u.ic_mul.left = left;
    mulcode->u.ic_mul.right1 = right1;
    mulcode->u.ic_mul.right2 = right2;
    
    AddInterCode(mulcode);
}

void CreateAndAddDivIC(Operand left,Operand right1, Operand right2){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddDivIC with leftkind: %d, right1kind: %d, right2kind: %d",left->kind,right1->kind,right2->kind);
    #endif

    struct InterCode* divcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(divcode,0,sizeof(struct InterCode));
    divcode->IC_type = IC_DIV;

    divcode->u.ic_div.left = left;
    divcode->u.ic_div.right1 = right1;
    divcode->u.ic_div.right2 = right2;
    
    AddInterCode(divcode);
}

void CreateAndAddLabelIC(int label){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddLabelIC with label: %d",label);
    #endif

    Operand lab = CreateOperand(Ope_LAB);
    lab->u.lab_no = label;

    struct InterCode* labcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(labcode,0,sizeof(struct InterCode));
    labcode->IC_type = IC_LAB;
    labcode->u.ic_lab.label = lab;

    AddInterCode(labcode);
}

struct InterCode* CreateRelopIC(Operand left, Operand right, char* op){
    #ifdef L3DEBUG
        LogPurple("In CreateRelopIC with leftkind: %d, rightkind: %d, op: %s",left->kind,right->kind,op);
    #endif

    struct InterCode* relopcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(relopcode,0,sizeof(struct InterCode));
    relopcode->IC_type = IC_RELOP;

    relopcode->u.ic_relop.left = left;
    relopcode->u.ic_relop.right = right;
    relopcode->u.ic_relop.relop = op;
    
    return relopcode;
}

void CreateAndAddIfIC(struct InterCode* relop, int label){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddIfIC with label: %d",label);
    #endif

    Operand lab = CreateOperand(Ope_LAB);
    lab->u.lab_no = label;

    struct InterCode* ifcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(ifcode,0,sizeof(struct InterCode));
    ifcode->IC_type = IC_IFGOTO;

    ifcode->u.ic_ifgoto.relop = relop;
    ifcode->u.ic_ifgoto.label = lab;

    AddInterCode(ifcode);
}

void CreateAndAddGotoIC(int label){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddGotoIC with label: %d",label);
    #endif

    Operand lab = CreateOperand(Ope_LAB);
    lab->u.lab_no = label;

    struct InterCode* gotocode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(gotocode,0,sizeof(struct InterCode));
    gotocode->IC_type = IC_GOTO;

    gotocode->u.ic_goto.label = lab;
    AddInterCode(gotocode);
}

void CreateAndAddReadIC(Operand read_var){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddReadIC with tvarno: %d",read_var->u.tvar_no);
    #endif

    read_var->kind = Ope_TVAR;

    struct InterCode* readcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(readcode,0,sizeof(struct InterCode));
    readcode->IC_type = IC_READ;

    readcode->u.ic_read.read_var = read_var;
    AddInterCode(readcode);
}

void CreateAndAddCallIC(Operand left, char* funcname){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddCallIC with funcname: %s",funcname);
    #endif

    Operand function = CreateOperand(Ope_FUNC);
    function->u.funcname = funcname;

    struct InterCode* callcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(callcode,0,sizeof(struct InterCode));
    callcode->IC_type = IC_CALL;

    callcode->u.ic_call.left = left;
    callcode->u.ic_call.function = function;

    AddInterCode(callcode);
}

void CreateAndAddWriteIC(Operand write_var){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddWriteIC with tvarno: %d",write_var->u.tvar_no);
    #endif

    struct InterCode* writecode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(writecode,0,sizeof(struct InterCode));
    writecode->IC_type = IC_WRITE;


    if(write_var->kind == Ope_ADDR){
        //一定是is_addr = true 且 addr = tvar
        Operand newwrite_var = CreateOperand(Ope_TVAR);
        newwrite_var->u.tvar_no = tvar_num++;
        CreateAndAddAssignIC(newwrite_var,write_var);
        writecode->u.ic_write.write_var = newwrite_var;
    }
    else{
        writecode->u.ic_write.write_var = write_var;
    }
  
    AddInterCode(writecode);
}

void CreateAndAddArgIC(Operand arg_var){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddArgIC with tvarno: %d",arg_var->u.tvar_no);
    #endif

    struct InterCode* argcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(argcode,0,sizeof(struct InterCode));
    argcode->IC_type = IC_ARG;

    if(arg_var->kind == Ope_ADDR && arg_var->is_addr == true){
        //可能是 arg a[1][2] 需要转化
        Operand newarg_var = CreateOperand(Ope_TVAR);
        newarg_var->u.tvar_no = tvar_num++;
        CreateAndAddAssignIC(newarg_var,arg_var);
        argcode->u.ic_arg.arg = newarg_var;
    }
    else{
        argcode->u.ic_arg.arg = arg_var;
    }

    AddInterCode(argcode);
}

void CreateAndAddReturnIC(Operand ret_var){
    #ifdef L3DEBUG
        LogPurple("In CreateAndAddReturnIC with tvarno: %d",ret_var->u.tvar_no);
    #endif

    struct InterCode* retcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(retcode,0,sizeof(struct InterCode));
    retcode->IC_type = IC_RETURN;

    retcode->u.ic_return.ret = ret_var;
    AddInterCode(retcode);
}

void CreateAndAddSpacelineIC(){
    struct InterCode* splcode = (struct InterCode*)malloc(sizeof(struct InterCode));
    memset(splcode,0,sizeof(struct InterCode));
    splcode->IC_type = IC_SPACELINE;

    AddInterCode(splcode);
}

/*--------------------------print Intercode-------------------------------*/

static char* getTvar(Operand op){
    #ifdef L3DEBUG
    LogYellow("in getTvar");
    #endif

    char *ret = (char*)malloc(20);
    memset(ret,0,20);
    char* nums = (char*)malloc(20);
    memset(nums,0,20);

    strncat(ret,"t",strlen("t"));
    nums = myitoa(op->u.tvar_no,nums);
    strncat(ret,nums,strlen(nums));

    return ret;
}

static char* getVar(Operand op){
    #ifdef L3DEBUG
    LogYellow("in getVar");
    #endif

    char *ret = (char*)malloc(20);
    memset(ret,0,20);
    char* nums = (char*)malloc(20);
    memset(nums,0,20);

    strncat(ret,"v",strlen("v"));
    nums = myitoa(op->u.var_no,nums);
    strncat(ret,nums,strlen(nums));

    return ret;
}

static char* getConstint(Operand op){
     #ifdef L3DEBUG
    LogYellow("in getConstint");
    #endif

    char *ret = (char*)malloc(20);
    memset(ret,0,20);
    char* nums = (char*)malloc(20);
    memset(nums,0,20);

    strncat(ret,"#",strlen("#"));
    nums = myitoa(op->u.const_int,nums);
    strncat(ret,nums,strlen(nums));

    return ret;
}

static char* getleftcode(Operand left){
    #ifdef L3DEBUG
    LogYellow("in getleftcode");
    #endif

    char* ret = (char*)malloc(30);
    memset(ret,0,30);
    if(left->kind == Ope_VAR){
        strcat(ret,getVar(left));
    }
    else if(left->kind == Ope_TVAR){
        strcat(ret,getTvar(left));
    }
    else if(left->kind == Ope_ADDR){
        if(left->is_addr){
            strcat(ret,"*");
        }
        else{
            strcat(ret,"&");
        }
        if(left->addr == ADDR_VAR)
            strcat(ret,getVar(left));
        else if(left->addr == ADDR_TVAR)
            strcat(ret,getTvar(left));
    }
    else{
        LogRed("%d",left->kind);
        Assert(0,"wrong in print assign");
    }
        

    return ret;
}

static char* getrightcode(Operand right){
    #ifdef L3DEBUG
    LogYellow("in getrightcode");
    #endif

    char* ret = (char*)malloc(60);
    memset(ret,0,60);
    switch (right->kind){
    case Ope_VAR:
        strcat(ret,getVar(right));
        break;
    case Ope_TVAR:
        strcat(ret,getTvar(right));
        break;  
    case Ope_INT:
        strcat(ret,getConstint(right));
        break;
    case Ope_ADDR:
        if(right->is_addr){
            strcat(ret,"*");
        }
        else{
            strcat(ret,"&");
        }
        if(right->addr == ADDR_VAR)
            strcat(ret,getVar(right));
        else if(right->addr == ADDR_TVAR)
            strcat(ret,getTvar(right));
        break;
    default:
        break;
    }

    return ret;
}

static char* PrintEachInterCode(struct InterCode* code){
    #ifdef L3DEBUG
        LogYellow("In PrintEachInterCode");
    #endif

    char* outstr = (char*)malloc(50);
    memset(outstr,0,50);
    switch (code->IC_type)
    {
    case IC_LAB:{
        #ifdef L3DEBUG
        LogGreen("In print IC_LAB");
        #endif
        sprintf(outstr,"LABEL label%d :\n",code->u.ic_lab.label->u.lab_no);
        break;
    }
    case IC_FUNC:{
        #ifdef L3DEBUG
        LogGreen("In print IC_FUNC");
        #endif
        sprintf(outstr,"FUNCTION %s :\n",code->u.ic_func.function->u.funcname);
        break;
    }
    case IC_ASSIGN:{
        #ifdef L3DEBUG
        LogGreen("In print IC_FUNC");
        #endif
        Operand left = code->u.ic_assign.left;
        Operand right = code->u.ic_assign.right;     
        char *leftcode = getleftcode(left);
        char *rightcode = getrightcode(right);

        sprintf(outstr,"%s := %s\n",leftcode,rightcode);
        break;
    }
    case IC_ADD:{
        #ifdef L3DEBUG
        LogGreen("In print IC_ADD");
        #endif
        Operand left = code->u.ic_add.left;
        Operand right1 = code->u.ic_add.right1;
        Operand right2 = code->u.ic_add.right2;
        
        char* leftcode = getleftcode(left);
        char* right1code = getrightcode(right1);
        char* right2code = getrightcode(right2);

        sprintf(outstr,"%s := %s + %s\n",leftcode,right1code,right2code);
        break;
    }
    case IC_SUB:{
        #ifdef L3DEBUG
        LogGreen("In print IC_SUB");
        #endif
        Operand left = code->u.ic_sub.left;
        Operand right1 = code->u.ic_sub.right1;
        Operand right2 = code->u.ic_sub.right2;
        
        char* leftcode = getleftcode(left);
        char* right1code = getrightcode(right1);
        char* right2code = getrightcode(right2);

        sprintf(outstr,"%s := %s - %s\n",leftcode,right1code,right2code);
        break;
    }
    case IC_MUL:{
        #ifdef L3DEBUG
        LogGreen("In print IC_MUL");
        #endif
        Operand left = code->u.ic_mul.left;
        Operand right1 = code->u.ic_mul.right1;
        Operand right2 = code->u.ic_mul.right2;
        
        char* leftcode = getleftcode(left);
        char* right1code = getrightcode(right1);
        char* right2code = getrightcode(right2);

        sprintf(outstr,"%s := %s * %s\n",leftcode,right1code,right2code);
        break;
    }
    case IC_DIV:{
        #ifdef L3DEBUG
        LogGreen("In print IC_DIV");
        #endif
        Operand left = code->u.ic_div.left;
        Operand right1 = code->u.ic_div.right1;
        Operand right2 = code->u.ic_div.right2;
        
        char* leftcode = getleftcode(left);
        char* right1code = getrightcode(right1);
        char* right2code = getrightcode(right2);

        sprintf(outstr,"%s := %s / %s\n",leftcode,right1code,right2code);
        break;
    }
    case IC_RELOP:{
        #ifdef L3DEBUG
        LogGreen("In print IC_RELOP");
        #endif
        Operand left = code->u.ic_relop.left;
        Operand right = code->u.ic_relop.right;

        char* leftcode = getleftcode(left);
        char* rightcode = getrightcode(right);

        sprintf(outstr,"%s %s %s",leftcode,code->u.ic_relop.relop,rightcode);
        break;
    }
    case IC_GOTO:{
        #ifdef L3DEBUG
        LogGreen("In print IC_GOTO");
        #endif
        sprintf(outstr,"GOTO label%d\n",code->u.ic_goto.label->u.lab_no);
        break;
    }  
    case IC_IFGOTO:{
        #ifdef L3DEBUG
        LogGreen("In print IC_IFGOTO");
        #endif
        sprintf(outstr,"IF %s GOTO label%d\n",
            PrintEachInterCode(code->u.ic_ifgoto.relop),code->u.ic_ifgoto.label->u.lab_no);
        break;
    }
    case IC_RETURN:{
        #ifdef L3DEBUG
        LogGreen("In print IC_RETURN");
        #endif
        Operand ret = code->u.ic_return.ret;
        char* tmpcode = getrightcode(ret);
        sprintf(outstr,"RETURN %s\n",tmpcode);
        break;
    }
    case IC_DEC:{
        #ifdef L3DEBUG
        LogGreen("In print IC_DEC");
        #endif
        Operand var = code->u.ic_dec.var;
        char* tmpcode = getrightcode(var);
        sprintf(outstr,"DEC %s %d\n",tmpcode,code->u.ic_dec.size);
        break;
    }
    case IC_ARG:{
        #ifdef L3DEBUG
        LogGreen("In print IC_ARG");
        #endif
        Operand arg = code->u.ic_arg.arg;
        char* tmpcode = getrightcode(arg);
        sprintf(outstr,"ARG %s\n",tmpcode);
        break;
    }
    case IC_CALL:{
        #ifdef L3DEBUG
        LogGreen("In print IC_CALL");
        #endif
        Operand left = code->u.ic_call.left;
        char* leftcode = getleftcode(left);
        sprintf(outstr,"%s := CALL %s\n",
            leftcode,code->u.ic_call.function->u.funcname);
        break;
    }
    case IC_PARAM:{
        #ifdef L3DEBUG
        LogGreen("In print IC_PARAM");
        #endif
        Operand param  = code->u.ic_param.param;
        char* tmpcode = getrightcode(param);
        sprintf(outstr,"PARAM %s\n",tmpcode);
        break;
    }
    case IC_READ:{
        #ifdef L3DEBUG
        LogGreen("In print IC_READ");
        #endif
        Operand read_var = code->u.ic_read.read_var;
        char* tmpcode = getrightcode(read_var);
        sprintf(outstr,"READ %s\n",tmpcode);
        break;
    }
    case IC_WRITE:{
        #ifdef L3DEBUG
        LogGreen("In print IC_WRITE");
        #endif
        Operand write_var = code->u.ic_write.write_var;
        char* tmpcode = getrightcode(write_var);
        sprintf(outstr,"WRITE %s\n",tmpcode);
        break;
    }
    case IC_SPACELINE:{
        #ifdef L3DEBUG
        LogGreen("In print IC_SPACELINE");
        #endif
        sprintf(outstr,"\n");
        break;
    }
    default:
        break;
    }

    return outstr;
}

void PrintInterCodes(char* filename){
    #ifdef L3DEBUG
        LogYellow("In PrintInterCodes");
    #endif

    FILE* outfile = fopen(filename,"w+");

    struct InterCodes* index = ICHead;
    while(index != NULL){
        char* outstr = PrintEachInterCode(index->code);
        fprintf(outfile,"%s",outstr);
        index = index->next;
    }

    fclose(outfile);
}