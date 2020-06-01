#include "SymTable.h"
#include "InterCode.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern struct InterCodes* ICHead;
extern int var_num;
extern int tvar_num;

static int this_parcnt = 0;


//均从1开始
int *offsettable; //记录(临时)变量到对应函数$fp的offset需乘4.
int *varmap; //将vi映射到offsettable的下标
int *tvarmap; //将ti映射到offsettable的下标

static int offset = 0; //初始化时 $fp = $sp;
static int tableindex = 1;

//记录每个函数最后的offset
struct {
    char* funcname;
    int offs;
} FOtable[HTSIZE];
static int funcnum = 0;

static void SetOffset(Operand op){
    #ifdef L4DEBUG
        LogYellow("In SetOffset");
    #endif

    if(op->kind == Ope_VAR){
        if(varmap[op->u.var_no] != 0)//之前已经出现过
            return;
        offset--;
        offsettable[tableindex] = offset;
        varmap[op->u.var_no] = tableindex;
        tableindex++;
    }
    else if(op->kind == Ope_TVAR){
        if(tvarmap[op->u.tvar_no] != 0)//之前已经出现过
            return;
        offset--;
        offsettable[tableindex] = offset;
        tvarmap[op->u.tvar_no] = tableindex;
        tableindex++;
    }      
}

static void SetEachOffset(struct InterCode* code){
    #ifdef L4DEBUG
        LogYellow("In SetEachOffset");
    #endif
    switch (code->IC_type)
    {
    case IC_LAB:{
        break;
    }
    case IC_FUNC:{
        FOtable[funcnum + 1].funcname = code->u.ic_func.function->u.funcname;
        //保存旧的offset
        FOtable[funcnum].offs = offset;
        //新的函数重置offset
        offset = 0;
        funcnum++;
        break;
    }
    case IC_ASSIGN:{
        Operand left = code->u.ic_assign.left;
        Operand right = code->u.ic_assign.right;     
        SetOffset(left);
        SetOffset(right);
        break;
    }
    case IC_ADD:{
        Operand left = code->u.ic_add.left;
        Operand right1 = code->u.ic_add.right1;
        Operand right2 = code->u.ic_add.right2;
        SetOffset(left);
        SetOffset(right1);
        SetOffset(right2);
        break;
    }
    case IC_SUB:{
        Operand left = code->u.ic_sub.left;
        Operand right1 = code->u.ic_sub.right1;
        Operand right2 = code->u.ic_sub.right2;
        
        SetOffset(left);
        SetOffset(right1);
        SetOffset(right2);
        break;
    }
    case IC_MUL:{
        Operand left = code->u.ic_mul.left;
        Operand right1 = code->u.ic_mul.right1;
        Operand right2 = code->u.ic_mul.right2;
        
        SetOffset(left);
        SetOffset(right1);
        SetOffset(right2);  
        break;
    }
    case IC_DIV:{
        Operand left = code->u.ic_div.left;
        Operand right1 = code->u.ic_div.right1;
        Operand right2 = code->u.ic_div.right2;
        
        SetOffset(left);
        SetOffset(right1);
        SetOffset(right2);
        break;
    }
    case IC_RELOP:{
        #ifdef L4DEBUG
        LogRed("In print IC_RELOP");
        #endif
        Operand left = code->u.ic_relop.left;
        Operand right = code->u.ic_relop.right;

        SetOffset(left);
        SetOffset(right);
        break;
    }
    case IC_GOTO:{
        break;
    }  
    case IC_IFGOTO:{
        struct InterCode* relop = code->u.ic_ifgoto.relop;
        SetEachOffset(relop);
        break;
    }
    case IC_RETURN:{
        Operand ret = code->u.ic_return.ret;
        SetOffset(ret);
        break;
    }
    case IC_DEC:{
        Operand var = code->u.ic_dec.var;
        offset -= (code->u.ic_dec.size/4);
        offsettable[tableindex] = offset;
        varmap[var->u.var_no] = tableindex;
        tableindex++;
        break;
    }
    case IC_ARG:{
        Operand arg = code->u.ic_arg.arg;     
        SetOffset(arg);
        break;
    }
    case IC_CALL:{
        Operand left = code->u.ic_call.left;
        SetOffset(left);
        break;
    }
    case IC_PARAM:{
        Operand param  = code->u.ic_param.param;
        SetOffset(param);
        break;
    }
    case IC_READ:{
        Operand read_var = code->u.ic_read.read_var;
        
        SetOffset(read_var);
        break;
    }
    case IC_WRITE:{
        Operand write_var = code->u.ic_write.write_var;
        SetOffset(write_var);
        break;
    }
    case IC_SPACELINE:{
        break;
    }
    default:
        break;
    }
}

static void SetTheOffsetTable(){
    #ifdef L4DEBUG
        LogYellow("In SetTheOffsetTable");
    #endif

    offsettable = (int*)malloc(sizeof(int)*(var_num+tvar_num));
    memset(offsettable,0,sizeof(int)*(var_num+tvar_num));
    varmap = (int*)malloc(sizeof(int)*var_num);
    memset(varmap,0,sizeof(int)*var_num);
    tvarmap = (int*)malloc(sizeof(int)*tvar_num);
    memset(tvarmap,0,sizeof(int)*tvar_num);

    struct InterCodes* index = ICHead;
    while(index != NULL){
        SetEachOffset(index->code);
        index = index->next;
    }
    //设置最后一个函数的offset
    FOtable[funcnum].offs = offset;

}



static char* PrintInitMipsCode(){
    char *ret = ".data \n\
_prompt: .asciiz \"Enter an integer:\" \n\
_ret: .asciiz \"\\n\" \n\
.globl main \n\
.text \n\
read: \n\
  li $v0, 4\n\
  la $a0, _prompt\n\
  syscall\n\
  li $v0, 5\n\
  syscall\n\
  jr $ra\n\
\n\
write:\n\
  li $v0, 1\n\
  syscall\n\
  li $v0, 4\n\
  la $a0, _ret\n\
  syscall\n\
  move $v0, $0\n\
  jr $ra\n\
\n"
;
    return ret;
}

static char* SaveInStack(Operand left){
    #ifdef L4DEBUG
        LogGreen("In SaveInStack");
    #endif
    char* outstr = (char*)malloc(100);
    memset(outstr,0,100);
    // 默认需要保存的寄存器为t1
    if(left->kind == Ope_VAR){
        if(offsettable[varmap[left->u.var_no]]*4 >= 32767 || offsettable[varmap[left->u.var_no]]*4 <= -32767){
            sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[varmap[left->u.var_no]]*4);
            sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
            sprintf(outstr+strlen(outstr),"  sw $t1, 0($t2)\n");
        }
        else
            sprintf(outstr+strlen(outstr),"  sw $t1, %d($fp)\n",offsettable[varmap[left->u.var_no]]*4);
    }
    else if(left->kind == Ope_TVAR){
        if(offsettable[tvarmap[left->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[left->u.tvar_no]]*4 <= -32767){
            sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[tvarmap[left->u.tvar_no]]*4);
            sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
            sprintf(outstr+strlen(outstr),"  sw $t1, 0($t2)\n");
        }
        else
            sprintf(outstr+strlen(outstr),"  sw $t1, %d($fp)\n",offsettable[tvarmap[left->u.tvar_no]]*4);
    }
    return outstr;
}

// 返回内容
static char* GetReg(Operand op, int option){
    #ifdef L4DEBUG
        LogGreen("In GetReg");
    #endif
    char* ret = (char*)malloc(100);
    memset(ret,0,100);
    if(op->kind == Ope_VAR){
        switch (option)
        {
        case 1:
            if(offsettable[varmap[op->u.var_no]]*4 >= 32767 || offsettable[varmap[op->u.var_no]]*4 <= -32767){
                sprintf(ret+strlen(ret),"  li $t3, %d\n",offsettable[varmap[op->u.var_no]]*4);
                sprintf(ret+strlen(ret),"  add $t2, $fp, $t3\n");
                sprintf(ret+strlen(ret),"  lw $t1, 0($t2)\n");
            }
            else
                sprintf(ret+strlen(ret),"  lw $t1, %d($fp)\n",offsettable[varmap[op->u.var_no]]*4);
            break;
        case 2:
            if(offsettable[varmap[op->u.var_no]]*4 >= 32767 || offsettable[varmap[op->u.var_no]]*4 <= -32767){
                sprintf(ret+strlen(ret),"  li $t4, %d\n",offsettable[varmap[op->u.var_no]]*4);
                sprintf(ret+strlen(ret),"  add $t3, $fp, $t4\n");
                sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
            }
            else
                sprintf(ret+strlen(ret),"  lw $t2, %d($fp)\n",offsettable[varmap[op->u.var_no]]*4);
            break;
        case 3:
            if(offsettable[varmap[op->u.var_no]]*4 >= 32767 || offsettable[varmap[op->u.var_no]]*4 <= -32767){
                sprintf(ret+strlen(ret),"  li $t5, %d\n",offsettable[varmap[op->u.var_no]]*4);
                sprintf(ret+strlen(ret),"  add $t4, $fp, $t5\n");
                sprintf(ret+strlen(ret),"  lw $t3, 0($t4)\n");
            }
            else
                sprintf(ret+strlen(ret),"  lw $t3, %d($fp)\n",offsettable[varmap[op->u.var_no]]*4);
            break;
        default:
            break;
        }      
    }
    else if(op->kind == Ope_TVAR){
        switch (option)
        {
        case 1:
            if(offsettable[tvarmap[op->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[op->u.tvar_no]]*4 <= -32767){
                sprintf(ret+strlen(ret),"  li $t3, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                sprintf(ret+strlen(ret),"  add $t2, $fp, $t3\n");
                sprintf(ret+strlen(ret),"  lw $t1, 0($t2)\n");
            }
            else
                sprintf(ret+strlen(ret),"  lw $t1, %d($fp)\n",offsettable[tvarmap[op->u.tvar_no]]*4);
            break;
        case 2:
            if(offsettable[tvarmap[op->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[op->u.tvar_no]]*4 <= -32767){
                sprintf(ret+strlen(ret),"  li $t4, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                sprintf(ret+strlen(ret),"  add $t3, $fp, $t4\n");
                sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
            }
            else
                sprintf(ret+strlen(ret),"  lw $t2, %d($fp)\n",offsettable[tvarmap[op->u.tvar_no]]*4);
            break;
        case 3:
            if(offsettable[tvarmap[op->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[op->u.tvar_no]]*4 <= -32767){
                sprintf(ret+strlen(ret),"  li $t5, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                sprintf(ret+strlen(ret),"  add $t4, $fp, $t5\n");
                sprintf(ret+strlen(ret),"  lw $t3, 0($t4)\n");
            }
            else
                sprintf(ret+strlen(ret),"  lw $t3, %d($fp)\n",offsettable[tvarmap[op->u.tvar_no]]*4);
            break;
        default:
            break;
        }
        
    }
    else if(op->kind == Ope_ADDR){
        if(op->is_addr){
            if(op->addr == ADDR_VAR){
                switch (option)
                {
                case 1:
                    if(offsettable[varmap[op->u.var_no]]*4 >= 32767 || offsettable[varmap[op->u.var_no]]*4 <= -32767){
                        sprintf(ret+strlen(ret),"  li $t4, %d\n",offsettable[varmap[op->u.var_no]]*4);
                        sprintf(ret+strlen(ret),"  add $t3, $fp, $t4\n");
                        sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
                        sprintf(ret+strlen(ret),"  lw $t1, 0($t2)\n");
                    }
                    else{
                        sprintf(ret+strlen(ret),"  lw $t2, %d($fp)\n",offsettable[varmap[op->u.var_no]]*4);
                        sprintf(ret+strlen(ret),"  lw $t1, 0($t2)\n");
                    } 
                    break;
                case 2:
                    if(offsettable[varmap[op->u.var_no]]*4 >= 32767 || offsettable[varmap[op->u.var_no]]*4 <= -32767){
                        sprintf(ret+strlen(ret),"  li $t5, %d\n",offsettable[varmap[op->u.var_no]]*4);
                        sprintf(ret+strlen(ret),"  add $t4, $fp, $t5\n");
                        sprintf(ret+strlen(ret),"  lw $t3, 0($t4)\n");
                        sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
                    }
                    else{
                        sprintf(ret+strlen(ret),"  lw $t3, %d($fp)\n",offsettable[varmap[op->u.var_no]]*4);
                        sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
                    }
                    break;
                case 3:
                    if(offsettable[varmap[op->u.var_no]]*4 >= 32767 || offsettable[varmap[op->u.var_no]]*4 <= -32767){
                        sprintf(ret+strlen(ret),"  li $t6, %d\n",offsettable[varmap[op->u.var_no]]*4);
                        sprintf(ret+strlen(ret),"  add $t5, $fp, $t6\n");
                        sprintf(ret+strlen(ret),"  lw $t4, 0($t5)\n");
                        sprintf(ret+strlen(ret),"  lw $t3, 0($t4)\n");
                    }
                    else{
                        sprintf(ret+strlen(ret),"  lw $t4, %d($fp)\n",offsettable[varmap[op->u.var_no]]*4);
                        sprintf(ret+strlen(ret),"  lw $t3, 0($t4)\n");
                    }
                    break;
                default:
                    break;
                }
                
            }
            else{
                switch (option)
                {
                case 1:
                    if(offsettable[tvarmap[op->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[op->u.tvar_no]]*4 <= -32767){
                        sprintf(ret+strlen(ret),"  li $t4, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                        sprintf(ret+strlen(ret),"  add $t3, $fp, $t4\n");
                        sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
                        sprintf(ret+strlen(ret),"  lw $t1, 0($t2)\n");
                    }
                    else{
                        sprintf(ret+strlen(ret),"  lw $t2, %d($fp)\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                        sprintf(ret+strlen(ret),"  lw $t1, 0($t2)\n");
                    }  
                    break;
                case 2:
                    if(offsettable[tvarmap[op->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[op->u.tvar_no]]*4 <= -32767){
                        sprintf(ret+strlen(ret),"  li $t5, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                        sprintf(ret+strlen(ret),"  add $t4, $fp, $t5\n");
                        sprintf(ret+strlen(ret),"  lw $t3, 0($t4)\n");
                        sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
                    }
                    else{
                        sprintf(ret+strlen(ret),"  lw $t3, %d($fp)\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                        sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
                    }    
                    break;
                case 3:
                    if(offsettable[tvarmap[op->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[op->u.tvar_no]]*4 <= -32767){
                        sprintf(ret+strlen(ret),"  li $t6, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                        sprintf(ret+strlen(ret),"  add $t5, $fp, $t6\n");
                        sprintf(ret+strlen(ret),"  lw $t4, 0($t5)\n");
                        sprintf(ret+strlen(ret),"  lw $t3, 0($t4)\n");
                    }
                    else{
                        sprintf(ret+strlen(ret),"  lw $t4, %d($fp)\n",offsettable[tvarmap[op->u.tvar_no]]*4);
                        sprintf(ret+strlen(ret),"  lw $t3, 0($t4)\n");
                    }
                    break;
                default:
                    break;
                }
                
            }
        }
        else{
            if(op->addr == ADDR_VAR){
                switch (option)
                {
                case 1:
                    sprintf(ret+strlen(ret),"  li $t2, %d\n",offsettable[varmap[op->u.var_no]]*4); 
                    sprintf(ret+strlen(ret),"  add $t1, $fp, $t2\n"); 
                    break;    
                case 2:
                    sprintf(ret+strlen(ret),"  li $t3, %d\n",offsettable[varmap[op->u.var_no]]*4); 
                    sprintf(ret+strlen(ret),"  add $t2, $fp, $t3\n"); 
                    break;
                case 3:
                    sprintf(ret+strlen(ret),"  li $t2, %d\n",offsettable[varmap[op->u.var_no]]*4); 
                    sprintf(ret+strlen(ret),"  add $t3, $fp, $t2\n"); 
                    break;
                default:
                    break;
                }            
            }
            else{
                switch (option)
                {
                case 1:
                    sprintf(ret+strlen(ret),"  li $t2, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4); 
                    sprintf(ret+strlen(ret),"  add $t1, $fp, $t2\n"); 
                    break;    
                case 2:
                    sprintf(ret+strlen(ret),"  li $t3, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4); 
                    sprintf(ret+strlen(ret),"  add $t2, $fp, $t3\n"); 
                    break;
                case 3:
                    sprintf(ret+strlen(ret),"  li $t2, %d\n",offsettable[tvarmap[op->u.tvar_no]]*4); 
                    sprintf(ret+strlen(ret),"  add $t3, $fp, $t2\n"); 
                    break;
                default:
                    break;
                }            
            }
        }
    }
    else if(op->kind == Ope_INT){
        switch (option)
        {
        case 1:
            sprintf(ret+strlen(ret),"  li $t1, %d\n",op->u.const_int);
            break;
        case 2:
            sprintf(ret+strlen(ret),"  li $t2, %d\n",op->u.const_int);
            break;
        case 3:
            sprintf(ret+strlen(ret),"  li $t3, %d\n",op->u.const_int);
            break;
        default:
            break;
        }
    }
    else 
        TODO();
    return ret;
}

static char* PrintEachMipsCode(struct InterCode* code){
    char* outstr = (char*)malloc(300);
    memset(outstr,0,300);

    switch (code->IC_type)
    {
    case IC_LAB:{
        #ifdef L4DEBUG
        LogGreen("In print IC_LAB");
        #endif
        sprintf(outstr,"label%d:\n",code->u.ic_lab.label->u.lab_no);
        break;
    }
    case IC_FUNC:{
        #ifdef L4DEBUG
        LogGreen("In print IC_FUNC");
        #endif

        this_parcnt = 0;
        
        if(strcmp(code->u.ic_func.function->u.funcname,"main") == 0){
            //初始化fp指针
            //默认有一个不使用的$ra和旧$fp
            sprintf(outstr+strlen(outstr),"%s:\n",code->u.ic_func.function->u.funcname);
            sprintf(outstr+strlen(outstr),"  move $fp, $sp\n");
        }
        else
            sprintf(outstr+strlen(outstr),"myfunc_%s:\n",code->u.ic_func.function->u.funcname);

        int funcoff = 0;
        for(int i = 1; i <= funcnum; ++i){
            if(strcmp(FOtable[i].funcname, code->u.ic_func.function->u.funcname) == 0){
                funcoff = FOtable[i].offs;
                break;
            }
        }
        if(funcoff*4 >= 32767 || funcoff*4 <= -32767){
            sprintf(outstr+strlen(outstr),"  li $t1, %d\n",funcoff*4);
            sprintf(outstr+strlen(outstr),"  add $sp, $sp, $t1\n");
        }
        else
            sprintf(outstr+strlen(outstr),"  addi $sp, $sp, %d\n",funcoff*4);
        break;
    }
    case IC_ASSIGN:{
        #ifdef L4DEBUG
        LogGreen("In print IC_ASSIGN");
        #endif
        Operand left = code->u.ic_assign.left;
        Operand right = code->u.ic_assign.right;     
        if(left->kind == Ope_ADDR && left->is_addr){
            //将左边变量放入寄存器
            if(left->addr == ADDR_VAR){
                if(offsettable[varmap[left->u.var_no]]*4 >= 32767 || offsettable[varmap[left->u.var_no]]*4 <= -32767){
                    sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[varmap[left->u.var_no]]*4);
                    sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
                    sprintf(outstr+strlen(outstr),"  lw $t1, 0($t2)\n");
                }
                else
                    sprintf(outstr+strlen(outstr),"  lw $t1, %d($fp)\n",offsettable[varmap[left->u.var_no]]*4);
            }
            else{
                if(offsettable[tvarmap[left->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[left->u.tvar_no]]*4 <= -32767){
                    sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[tvarmap[left->u.tvar_no]]*4);
                    sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
                    sprintf(outstr+strlen(outstr),"  lw $t1, 0($t2)\n");
                }
                else
                    sprintf(outstr+strlen(outstr),"  lw $t1, %d($fp)\n",offsettable[tvarmap[left->u.tvar_no]]*4);
            }

            switch (right->kind)
            {
            case Ope_INT:{
                sprintf(outstr+strlen(outstr),"  li $t2, %d\n",right->u.const_int);
                sprintf(outstr+strlen(outstr),"  sw $t2, 0($t1)\n");
                //存储到内存
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }
            case Ope_VAR:{
                //将右边的变量的值装入寄存器。
                if(offsettable[varmap[right->u.var_no]]*4 >= 32767 || offsettable[varmap[right->u.var_no]]*4 <= -32767){
                    sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[varmap[right->u.var_no]]*4);
                    sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                    sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                }
                else
                    sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[varmap[right->u.var_no]]*4);
                //赋值操作
                sprintf(outstr+strlen(outstr),"  sw $t2, 0($t1)\n");
                //将左边变量的值写入内存。
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }  
            case Ope_TVAR:{
                //将右边的变量的值装入寄存器。
                 if(offsettable[tvarmap[right->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[right->u.tvar_no]]*4 <= -32767){
                    sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                    sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                    sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                }
                else
                    sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                //赋值操作
                sprintf(outstr+strlen(outstr),"  sw $t2, 0($t1)\n");
                //将左边变量的值写入内存。
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }
            case Ope_ADDR:{
                if(!right->is_addr){
                    /* & */
                    //将右边变量的地址装入寄存器t2
                    if(right->addr == ADDR_VAR){
                        sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[varmap[right->u.var_no]]*4);
                        sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                        sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
                    }
                    //赋值
                    sprintf(outstr+strlen(outstr),"  sw $t2, 0($t1)\n");
                    //将左边变量写入内存
                    char* str = SaveInStack(left);
                    sprintf(outstr+strlen(outstr),"%s",str);
                    free(str); 
                }
                else{
                    /* * */
                    //将右边变量装入寄存器t2
                    if(right->addr == ADDR_VAR){
                        if(offsettable[varmap[right->u.var_no]]*4 >= 32767 || offsettable[varmap[right->u.var_no]]*4 <= -32767){
                            sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[varmap[right->u.var_no]]*4);
                            sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                            sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                        }
                        else
                            sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[varmap[right->u.var_no]]*4);
                    }
                    else{
                        if(offsettable[tvarmap[right->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[right->u.tvar_no]]*4 <= -32767){
                            sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                            sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                            sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                        }
                        else
                            sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                    }
                    //赋值
                    sprintf(outstr+strlen(outstr),"  lw $t3, 0($t2)\n");
                    sprintf(outstr+strlen(outstr),"  sw $t3, 0($t1)\n");
                     //将左边变量写入内存
                    char* str = SaveInStack(left);
                    sprintf(outstr+strlen(outstr),"%s",str);
                    free(str);
                }
                break;
            }          
            default:
                break;
            }
        }
        else if(left->kind == Ope_VAR){
            switch (right->kind)
            {
            case Ope_INT:{
                sprintf(outstr+strlen(outstr),"  li $t1, %d\n",right->u.const_int);
                //存储到内存
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }      
            case Ope_VAR:{
                //将右边的变量的值装入寄存器。
                if(offsettable[varmap[right->u.var_no]]*4 >= 32767 || offsettable[varmap[right->u.var_no]]*4 <= -32767){
                    sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[varmap[right->u.var_no]]*4);
                    sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                    sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                }
                else
                    sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[varmap[right->u.var_no]]*4);
                //赋值操作
                sprintf(outstr+strlen(outstr),"  move $t1, $t2\n");
                //将左边变量的值写入内存。
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }
            case Ope_TVAR:{
                //将右边的变量的值装入寄存器。
                if(offsettable[tvarmap[right->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[right->u.tvar_no]]*4 <= -32767){
                    sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                    sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                    sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                }
                else
                    sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                //赋值操作
                sprintf(outstr+strlen(outstr),"  move $t1, $t2\n");
                //将左边变量的值写入内存。
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }
            case Ope_ADDR:{
                if(!right->is_addr){
                    /* & */
                    //将右边变量的地址装入寄存器t2
                    if(right->addr == ADDR_VAR){
                        sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[varmap[right->u.var_no]]*4);
                        sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                        sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
                    }
                    //赋值
                    sprintf(outstr+strlen(outstr),"  move $t1, $t2\n");
                    //将左边变量写入内存
                    char* str = SaveInStack(left);
                    sprintf(outstr+strlen(outstr),"%s",str);
                    free(str);
                }
                else{
                    /* * */
                    //将右边变量装入寄存器t2
                    if(right->addr == ADDR_VAR){
                        if(offsettable[varmap[right->u.var_no]]*4 >= 32767 || offsettable[varmap[right->u.var_no]]*4 <= -32767){
                            sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[varmap[right->u.var_no]]*4);
                            sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                            sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                        }
                        else
                            sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[varmap[right->u.var_no]]*4);
                    }
                    else{
                        if(offsettable[tvarmap[right->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[right->u.tvar_no]]*4 <= -32767){
                            sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                            sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                            sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                        }
                        else
                            sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                    }
                    //赋值
                    sprintf(outstr+strlen(outstr),"  lw $t1, 0($t2)\n");
                     //将左边变量写入内存
                    char* str = SaveInStack(left);
                    sprintf(outstr+strlen(outstr),"%s",str);
                    free(str);
                }
                break;
            }
            default:
                break;
            }
        }
        else if(left->kind == Ope_TVAR){
            switch (right->kind)
            {
            case Ope_INT:{
                sprintf(outstr+strlen(outstr),"  li $t1, %d\n",right->u.const_int);
                //存储到内存
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }      
            case Ope_VAR:{
                //将右边的变量的值装入寄存器。
                if(offsettable[varmap[right->u.var_no]]*4 >= 32767 || offsettable[varmap[right->u.var_no]]*4 <= -32767){
                    sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[varmap[right->u.var_no]]*4);
                    sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                    sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                }
                else
                    sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[varmap[right->u.var_no]]*4);
                //赋值操作
                sprintf(outstr+strlen(outstr),"  move $t1, $t2\n");
                //将左边变量的值写入内存。
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }
            case Ope_TVAR:{
                //将右边的变量的值装入寄存器。
                if(offsettable[tvarmap[right->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[right->u.tvar_no]]*4 <= -32767){
                    sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                    sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                    sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                }
                else
                    sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                //赋值操作
                sprintf(outstr+strlen(outstr),"  move $t1, $t2\n");
                //将左边变量的值写入内存。
                char* str = SaveInStack(left);
                sprintf(outstr+strlen(outstr),"%s",str);
                free(str);
                break;
            }
            case Ope_ADDR:{
                if(!right->is_addr){
                    /* & */
                    //将右边变量的地址装入寄存器t2
                    if(right->addr == ADDR_VAR){
                        sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[varmap[right->u.var_no]]*4);
                        sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  li $t3, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                        sprintf(outstr+strlen(outstr),"  add $t2, $fp, $t3\n");
                    }
                    //赋值
                    sprintf(outstr+strlen(outstr),"  move $t1, $t2\n");
                    //将左边变量写入内存
                    char* str = SaveInStack(left);
                    sprintf(outstr+strlen(outstr),"%s",str);
                    free(str);  
                }
                else{
                    /* * */
                    //将右边变量装入寄存器t2
                    if(right->addr == ADDR_VAR){
                        if(offsettable[varmap[right->u.var_no]]*4 >= 32767 || offsettable[varmap[right->u.var_no]]*4 <= -32767){
                            sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[varmap[right->u.var_no]]*4);
                            sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                            sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                        }
                        else
                            sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[varmap[right->u.var_no]]*4);
                    }
                    else{
                        if(offsettable[tvarmap[right->u.tvar_no]]*4 >= 32767 || offsettable[tvarmap[right->u.tvar_no]]*4 <= -32767){
                            sprintf(outstr+strlen(outstr),"  li $t4, %d\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                            sprintf(outstr+strlen(outstr),"  add $t3, $fp, $t4\n");
                            sprintf(outstr+strlen(outstr),"  lw $t2, 0($t3)\n");
                        }
                        else
                            sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",offsettable[tvarmap[right->u.tvar_no]]*4);
                    }
                    //赋值
                    sprintf(outstr+strlen(outstr),"  lw $t1, 0($t2)\n");
                     //将左边变量写入内存
                    char* str = SaveInStack(left);
                    sprintf(outstr+strlen(outstr),"%s",str);
                    free(str);  
                }
                break;
            }
            default:
                break;
            }
        }
        else 
            TODO();
        break;
    }
    case IC_ADD:{
        #ifdef L4DEBUG
        LogGreen("In print IC_ADD");
        #endif
        Operand left = code->u.ic_add.left;
        Operand right1 = code->u.ic_add.right1;
        Operand right2 = code->u.ic_add.right2;
        
        if(right1->kind == Ope_INT && right2->kind == Ope_INT){
            int intval = right1->u.const_int + right2->u.const_int;
            sprintf(outstr+strlen(outstr),"  li $t1, %d\n",intval);
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else{
            char* str1 = GetReg(right1, 2);
            char* str2 = GetReg(right2, 3);
            sprintf(outstr+strlen(outstr),"%s",str1);
            sprintf(outstr+strlen(outstr),"%s",str2);
            sprintf(outstr+strlen(outstr),"  add $t1, $t2, $t3\n");
            free(str1);
            free(str2);
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }  
        break;
    }
    case IC_SUB:{
        #ifdef L4DEBUG
        LogGreen("In print IC_SUB");
        #endif
        Operand left = code->u.ic_sub.left;
        Operand right1 = code->u.ic_sub.right1;
        Operand right2 = code->u.ic_sub.right2;
        
        if(right1->kind == Ope_INT && right2->kind == Ope_INT){
            int intval = right1->u.const_int - right2->u.const_int;
            sprintf(outstr+strlen(outstr),"  li $t1, %d\n",intval);
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else{
            char* str1 = GetReg(right1, 2);
            char* str2 = GetReg(right2, 3);
            sprintf(outstr+strlen(outstr),"%s",str1);
            sprintf(outstr+strlen(outstr),"%s",str2);
            sprintf(outstr+strlen(outstr),"  sub $t1, $t2, $t3\n");
            free(str1);
            free(str2);
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }  
        break;
    }
    case IC_MUL:{
        #ifdef L4DEBUG
        LogGreen("In print IC_MUL");
        #endif
        Operand left = code->u.ic_mul.left;
        Operand right1 = code->u.ic_mul.right1;
        Operand right2 = code->u.ic_mul.right2;
        
        if(right1->kind == Ope_INT && right2->kind == Ope_INT){
            int intval = right1->u.const_int * right2->u.const_int;
            sprintf(outstr+strlen(outstr),"  li $t1, %d\n",intval);
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else if(right1->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $t2, %d\n",right1->u.const_int);
            char* str = GetReg(right2,3);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
            sprintf(outstr+strlen(outstr),"  mul $t1, $t2, $t3\n");
            str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else if(right2->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $t2, %d\n",right2->u.const_int);
            char* str = GetReg(right1,3);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
            sprintf(outstr+strlen(outstr),"  mul $t1, $t2, $t3\n");
            str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else{
            char* str1 = GetReg(right1,2);
            char* str2 = GetReg(right2,3);
            sprintf(outstr+strlen(outstr),"%s",str1);
            sprintf(outstr+strlen(outstr),"%s",str2);
            free(str1);
            free(str2);
            sprintf(outstr+strlen(outstr),"  mul $t1, $t2, $t3\n");
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }     
        break;
    }
    case IC_DIV:{
        #ifdef L4DEBUG
        LogGreen("In print IC_DIV");
        #endif
        Operand left = code->u.ic_div.left;
        Operand right1 = code->u.ic_div.right1;
        Operand right2 = code->u.ic_div.right2;
        
        if(right1->kind == Ope_INT && right2->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $t2, %d\n",right1->u.const_int);
            sprintf(outstr+strlen(outstr),"  li $t3, %d\n",right2->u.const_int);
            sprintf(outstr+strlen(outstr),"  div $t2, $t3\n");
            sprintf(outstr+strlen(outstr),"  mflo $t1\n");
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else if(right1->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $t2, %d\n",right1->u.const_int);
            char* str = GetReg(right2,3);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
            sprintf(outstr+strlen(outstr),"  div $t2, $t3\n");
            sprintf(outstr+strlen(outstr),"  mflo $t1\n");
            str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else if(right2->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $t3, %d\n",right2->u.const_int);
            char* str = GetReg(right1,2);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
            sprintf(outstr+strlen(outstr),"  div $t2, $t3\n");
            sprintf(outstr+strlen(outstr),"  mflo $t1\n");
            str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else{
            char* str1 = GetReg(right1,2);
            char* str2 = GetReg(right2,3);
            sprintf(outstr+strlen(outstr),"%s",str1);
            sprintf(outstr+strlen(outstr),"%s",str2);
            free(str1);
            free(str2);
            sprintf(outstr+strlen(outstr),"  div $t2, $t3\n");
            sprintf(outstr+strlen(outstr),"  mflo $t1\n");
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }   
        break;
    }
    case IC_RELOP:{
        break;
    }
    case IC_GOTO:{
        #ifdef L4DEBUG
        LogGreen("In print IC_GOTO");
        #endif
        sprintf(outstr,"  j label%d\n",code->u.ic_goto.label->u.lab_no);
        break;
    }  
    case IC_IFGOTO:{
        #ifdef L4DEBUG
        LogGreen("In print IC_IFGOTO");
        #endif
        struct InterCode* relop = code->u.ic_ifgoto.relop;
        Operand label = code->u.ic_ifgoto.label;
        Operand left = relop->u.ic_relop.left;
        Operand right = relop->u.ic_relop.right;

        //加载relop两操作数到寄存器$t1,$t2上
        if(left->kind == Ope_INT && right->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $t1, %d\n",left->u.const_int);
            sprintf(outstr+strlen(outstr),"  li $t2, %d\n",right->u.const_int);
        }
        else if(left->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $t1, %d\n",left->u.const_int);
            char* str = GetReg(right, 2);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else if(right->kind == Ope_INT){
            char* str = GetReg(left, 1);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
            sprintf(outstr+strlen(outstr),"  li $t2, %d\n",right->u.const_int);          
        }
        else{
            char* str1 = GetReg(left, 1);
            char* str2 = GetReg(right, 2);
            sprintf(outstr+strlen(outstr),"%s",str1);
            sprintf(outstr+strlen(outstr),"%s",str2);
            free(str1);
            free(str2);
        }

        //比较跳转
        if(strcmp(relop->u.ic_relop.relop,"==") == 0){
            sprintf(outstr+strlen(outstr),"  beq $t1, $t2, label%d\n",label->u.lab_no);
        }
        else if(strcmp(relop->u.ic_relop.relop,"!=") == 0){
            sprintf(outstr+strlen(outstr),"  bne $t1, $t2, label%d\n",label->u.lab_no);
        }
        else if(strcmp(relop->u.ic_relop.relop,">") == 0){
            sprintf(outstr+strlen(outstr),"  bgt $t1, $t2, label%d\n",label->u.lab_no);
        }
        else if(strcmp(relop->u.ic_relop.relop,"<") == 0){
            sprintf(outstr+strlen(outstr),"  blt $t1, $t2, label%d\n",label->u.lab_no);
        }
        else if(strcmp(relop->u.ic_relop.relop,">=") == 0){
            sprintf(outstr+strlen(outstr),"  bge $t1, $t2, label%d\n",label->u.lab_no);
        }
        else if(strcmp(relop->u.ic_relop.relop,"<=") == 0){
            sprintf(outstr+strlen(outstr),"  ble $t1, $t2, label%d\n",label->u.lab_no);
        }
        else
            TODO();
        break;
    }
    case IC_RETURN:{
        #ifdef L4DEBUG
        LogGreen("In print IC_RETURN");
        #endif
        Operand ret = code->u.ic_return.ret;
        if(ret->kind == Ope_INT){
            if(ret->u.const_int == 0){
                sprintf(outstr+strlen(outstr),"  move $v0, $0\n");
            }
            else{
                sprintf(outstr+strlen(outstr),"  li $v0, %d\n",ret->u.const_int);
            }
        }
        else if(ret->kind == Ope_VAR || ret->kind == Ope_TVAR){
            char* str = GetReg(ret, 2);
            sprintf(outstr+strlen(outstr),"%s",str);
            sprintf(outstr+strlen(outstr),"  move $v0, $t2\n");
            free(str);
        }
        else if(ret->kind == Ope_ADDR){
            char* str = GetReg(ret, 2);
            sprintf(outstr+strlen(outstr),"%s",str);
            sprintf(outstr+strlen(outstr),"  move $v0, $t2\n");
            free(str);
        }
        else 
            TODO();

        sprintf(outstr+strlen(outstr),"  jr $ra\n");
        break;
    }
    case IC_DEC:{
        break;
    }
    case IC_ARG:{
        #ifdef L4DEBUG
        LogGreen("In print IC_ARG");
        #endif
        Operand arg = code->u.ic_arg.arg;
        
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
        if(arg->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $t1, %d\n",arg->u.const_int);
        }
        else{
            char* str = GetReg(arg, 1);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }

        sprintf(outstr+strlen(outstr),"  sw $t1, 0($sp)\n");

        break;
    }
    case IC_CALL:{
        #ifdef L4DEBUG
        LogGreen("In print IC_CALL");
        #endif
        Operand left = code->u.ic_call.left;
    
        //返回值及$fp压栈
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
        sprintf(outstr+strlen(outstr),"  sw $ra, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
        sprintf(outstr+strlen(outstr),"  sw $fp, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  move $fp, $sp\n");
        //跳转执行
        if(strcmp(code->u.ic_call.function->u.funcname,"main") == 0)
            sprintf(outstr+strlen(outstr),"  jal %s\n",code->u.ic_call.function->u.funcname);
        else
            sprintf(outstr+strlen(outstr),"  jal myfunc_%s\n",code->u.ic_call.function->u.funcname);
        //恢复现场
        sprintf(outstr+strlen(outstr),"  move $sp, $fp\n");
        sprintf(outstr+strlen(outstr),"  lw $fp, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, 4\n");
        sprintf(outstr+strlen(outstr),"  lw $ra, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, 4\n");
        //删除实参
        Item* funcitem = GetItemByName(code->u.ic_call.function->u.funcname,0);
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, %d\n",funcitem->paramnums*4); 
        //保存返回值
        sprintf(outstr+strlen(outstr),"  move $t1, $v0\n");
        char* str = SaveInStack(left);
        sprintf(outstr+strlen(outstr),"%s",str);
        free(str);
        break;
    }
    case IC_PARAM:{
        #ifdef L4DEBUG
        LogGreen("In print IC_PARAM");
        #endif
        Operand param  = code->u.ic_param.param;
        //取实参
        int val = 8 + 4*this_parcnt;
        sprintf(outstr+strlen(outstr),"  lw $t1, %d($fp)\n",val);
        this_parcnt++;
        char* str = SaveInStack(param);
        sprintf(outstr+strlen(outstr),"%s",str);
        free(str);   
        break;
    }
    case IC_READ:{
        #ifdef L4DEBUG
        LogGreen("In print IC_READ");
        #endif
        Operand read_var = code->u.ic_read.read_var;
        
        //返回值及$fp压栈
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
        sprintf(outstr+strlen(outstr),"  sw $ra, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
        sprintf(outstr+strlen(outstr),"  sw $fp, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  move $fp, $sp\n");
        //跳转执行
        sprintf(outstr+strlen(outstr),"  jal read\n");
        //恢复现场
        sprintf(outstr+strlen(outstr),"  move $sp, $fp\n");
        sprintf(outstr+strlen(outstr),"  lw $fp, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, 4\n");
        sprintf(outstr+strlen(outstr),"  lw $ra, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, 4\n");
        //保存返回值
        sprintf(outstr+strlen(outstr),"  move $t1, $v0\n");
        char* str = SaveInStack(read_var);
        sprintf(outstr+strlen(outstr),"%s",str);
        free(str);
        break;
    }
    case IC_WRITE:{
        #ifdef L4DEBUG
        LogGreen("In print IC_WRITE");
        #endif
        Operand write_var = code->u.ic_write.write_var;
        //传递参数
        if(write_var->kind == Ope_INT){
            sprintf(outstr+strlen(outstr),"  li $a0, %d\n",write_var->u.const_int);
        }
        else{
            char* str = GetReg(write_var, 2);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
            sprintf(outstr+strlen(outstr),"  move $a0, $t2\n");
        }
        //返回值及$fp压栈
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
        sprintf(outstr+strlen(outstr),"  sw $ra, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
        sprintf(outstr+strlen(outstr),"  sw $fp, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  move $fp, $sp\n");
        //跳转执行
        sprintf(outstr+strlen(outstr),"  jal write\n");
        //恢复现场
        sprintf(outstr+strlen(outstr),"  move $sp, $fp\n");
        sprintf(outstr+strlen(outstr),"  lw $fp, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, 4\n");
        sprintf(outstr+strlen(outstr),"  lw $ra, 0($sp)\n");
        sprintf(outstr+strlen(outstr),"  addi $sp, $sp, 4\n");
        //删除实参
        // sprintf(outstr+strlen(outstr),"  addi $sp, $sp, 4\n");
        //保存返回值
        // sprintf(outstr+strlen(outstr),"  move $t1, $v0\n");
        // char* str = SaveInStack(write_var);
        // sprintf(outstr+strlen(outstr),"%s",str);
        // free(str);
        break;
    }
    case IC_SPACELINE:{
        #ifdef L4DEBUG
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

void PrintMipsCodes(char* filename){
    #ifdef L4DEBUG
        LogYellow("In PrintMipsrCodes");
    #endif

    //预先设置好每个变量和临时变量的偏移量
    SetTheOffsetTable();

    FILE* outfile = fopen(filename,"w+");
    
    //初始信息输入
    char* initout = PrintInitMipsCode();
    fprintf(outfile,"%s",initout);

    //逐条翻译
    struct InterCodes* index = ICHead;
    while(index != NULL){
        char* mipsout = PrintEachMipsCode(index->code);
        fprintf(outfile,"%s",mipsout);
        index = index->next;
    }

    fclose(outfile);
}
