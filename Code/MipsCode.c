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

struct S{
    int offset; //相对于$fp的偏移，需要*4。
    bool already; //是否是第一次溢出，true不是，false是。
};

static int offset = -2; //初始化时 $fp = $sp - 8;

struct S* varstore;
struct S* tvarstore; 


static char* PrintInitMipsCode(){
    char *ret = ".data \n\
_prompt: .asciiz \"Enter an integer:\" \n\
_ret: .asciiz \"\\n\" \n\
.globl main \n\
.text \n\
read: \n\
  li $v0, 4 \n\
  la $a0, _prompt \n\
  syscall \n\
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
        if(varstore[left->u.var_no].already){
             //之前已经溢出到栈中，已经有了位置。
            sprintf(outstr+strlen(outstr),"  sw $t1, %d($fp)\n",varstore[left->u.var_no].offset*4);
        }
        else{
            //第一次溢出
            sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
            sprintf(outstr+strlen(outstr),"  sw $t1, 0($sp)\n");
            varstore[left->u.var_no].already = true;
            offset--;
            varstore[left->u.var_no].offset = offset;
        }
    }
    else if(left->kind == Ope_TVAR){
        if(tvarstore[left->u.tvar_no].already){
            //之前已经溢出到栈中，已经有了位置。
            sprintf(outstr+strlen(outstr),"  sw $t1, %d($fp)\n",tvarstore[left->u.tvar_no].offset*4);
        }
        else{
            //第一次溢出
            sprintf(outstr+strlen(outstr),"  addi $sp, $sp, -4\n");
            sprintf(outstr+strlen(outstr),"  sw $t1, 0($sp)\n");
            tvarstore[left->u.tvar_no].already = true;
            offset--;
            tvarstore[left->u.tvar_no].offset = offset;
        }
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
        case 2:
            sprintf(ret+strlen(ret),"  lw $t2, %d($fp)\n",varstore[op->u.var_no].offset*4);
            break;
        case 3:
            sprintf(ret+strlen(ret),"  lw $t3, %d($fp)\n",varstore[op->u.var_no].offset*4);
            break;
        default:
            break;
        }      
    }
    else if(op->kind == Ope_TVAR){
        switch (option)
        {
        case 2:
            sprintf(ret+strlen(ret),"  lw $t2, %d($fp)\n",tvarstore[op->u.tvar_no].offset*4);
            break;
        case 3:
            sprintf(ret+strlen(ret),"  lw $t3, %d($fp)\n",tvarstore[op->u.tvar_no].offset*4);
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
                case 2:
                    sprintf(ret+strlen(ret),"  lw $t3, %d($fp)\n",varstore[op->u.var_no].offset*4);
                    sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
                    break;
                case 3:
                    sprintf(ret+strlen(ret),"  lw $t4, %d($fp)\n",varstore[op->u.var_no].offset*4);
                    sprintf(ret+strlen(ret),"  lw $t3, 0($t3)\n");
                    break;
                default:
                    break;
                }
                
            }
            else{
                switch (option)
                {
                case 2:
                    sprintf(ret+strlen(ret),"  lw $t3, %d($fp)\n",tvarstore[op->u.tvar_no].offset*4);
                    sprintf(ret+strlen(ret),"  lw $t2, 0($t3)\n");
                    break;
                case 3:
                    sprintf(ret+strlen(ret),"  lw $t4, %d($fp)\n",tvarstore[op->u.tvar_no].offset*4);
                    sprintf(ret+strlen(ret),"  lw $t3, 0($t3)\n");
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
                case 2:
                    sprintf(ret+strlen(ret),"  addi $t2, $fp, %d\n",varstore[op->u.var_no].offset*4); 
                    break;
                case 3:
                    sprintf(ret+strlen(ret),"  addi $t3, $fp, %d\n",varstore[op->u.var_no].offset*4); 
                    break;
                default:
                    break;
                }            
            }
            else{
                switch (option)
                {
                case 2:
                    sprintf(ret+strlen(ret),"  addi $t2, $fp, %d\n",tvarstore[op->u.tvar_no].offset*4);
                    break;
                case 3:
                    sprintf(ret+strlen(ret),"  addi $t3, $fp, %d\n",tvarstore[op->u.tvar_no].offset*4);
                    break;
                default:
                    break;
                }             
            }
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
        sprintf(outstr+strlen(outstr),"%s:\n",code->u.ic_func.function->u.funcname);
        if(strcmp(code->u.ic_func.function->u.funcname,"main") == 0){
            //初始化fp指针
            //默认有一个不使用的$ra和旧$fp
            sprintf(outstr+strlen(outstr),"  addi $fp, $sp, 8\n");
        }
        else{
            TODO();
        }
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
                sprintf(outstr+strlen(outstr),"  lw $t1, %d($fp)\n",varstore[left->u.var_no].offset*4);
            }
            else{
                sprintf(outstr+strlen(outstr),"  lw $t1, %d($fp)\n",tvarstore[left->u.tvar_no].offset*4);
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
                sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",varstore[right->u.var_no].offset*4);
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
                sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",tvarstore[right->u.tvar_no].offset*4);
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
                        sprintf(outstr+strlen(outstr),"  addi $t2, $fp, %d\n",varstore[right->u.var_no].offset*4);
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  addi $t2, $fp, %d\n",tvarstore[right->u.tvar_no].offset*4);
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
                        sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",varstore[right->u.var_no].offset*4);
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",tvarstore[right->u.tvar_no].offset*4);
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
                sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",varstore[right->u.var_no].offset*4);
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
                sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",tvarstore[right->u.tvar_no].offset*4);
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
                        sprintf(outstr+strlen(outstr),"  addi $t2, $fp, %d\n",varstore[right->u.var_no].offset*4);
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  addi $t2, $fp, %d\n",tvarstore[right->u.tvar_no].offset*4);
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
                        sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",varstore[right->u.var_no].offset*4);
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",tvarstore[right->u.tvar_no].offset*4);
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
                sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",varstore[right->u.var_no].offset*4);
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
                sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",tvarstore[right->u.tvar_no].offset*4);
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
                        sprintf(outstr+strlen(outstr),"  addi $t2, $fp, %d\n",varstore[right->u.var_no].offset*4);
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  addi $t2, $fp, %d\n",tvarstore[right->u.tvar_no].offset*4);
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
                        sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",varstore[right->u.var_no].offset*4);
                    }
                    else{
                        sprintf(outstr+strlen(outstr),"  lw $t2, %d($fp)\n",tvarstore[right->u.tvar_no].offset*4);
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
        else if(right1->kind == Ope_INT){
            char* str = GetReg(right2, 2);
            sprintf(outstr+strlen(outstr),"%s",str);
            sprintf(outstr+strlen(outstr),"  addi $t1, $t2, %d\n",right1->u.const_int);
            free(str);
            str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else if(right2->kind == Ope_INT){
            char* str = GetReg(right1, 2);
            sprintf(outstr+strlen(outstr),"%s",str);
            sprintf(outstr+strlen(outstr),"  addi $t1, $t2, %d\n",right2->u.const_int);
            free(str);
            str = SaveInStack(left);
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
            int intval = right1->u.const_int + right2->u.const_int;
            sprintf(outstr+strlen(outstr),"  li $t1, -%d\n",intval);
            char* str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else if(right1->kind == Ope_INT){  
            // a = 1 - b
            char* str = GetReg(right2, 2);
            sprintf(outstr+strlen(outstr),"%s",str);
            sprintf(outstr+strlen(outstr),"  li $t3, %d\n",right1->u.const_int);
            sprintf(outstr+strlen(outstr),"  sub $t1, $t3, $t2\n");
            free(str);
            str = SaveInStack(left);
            sprintf(outstr+strlen(outstr),"%s",str);
            free(str);
        }
        else if(right2->kind == Ope_INT){
            char* str = GetReg(right1, 2);
            sprintf(outstr+strlen(outstr),"%s",str);
            sprintf(outstr+strlen(outstr),"  addi $t1, $t2, -%d\n",right2->u.const_int);
            free(str);
            str = SaveInStack(left);
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
        
        TODO();
        break;
    }
    case IC_DIV:{
        #ifdef L4DEBUG
        LogGreen("In print IC_DIV");
        #endif
        Operand left = code->u.ic_div.left;
        Operand right1 = code->u.ic_div.right1;
        Operand right2 = code->u.ic_div.right2;
        
        char* leftcode = getcode(left);
        char* right1code = getcode(right1);
        char* right2code = getcode(right2);

        sprintf(outstr,"%s := %s / %s\n",leftcode,right1code,right2code);
        break;
    }
    case IC_RELOP:{
        #ifdef L4DEBUG
        LogGreen("In print IC_RELOP");
        #endif
        Operand left = code->u.ic_relop.left;
        Operand right = code->u.ic_relop.right;

        char* leftcode = getcode(left);
        char* rightcode = getcode(right);


        sprintf(outstr,"%s %s %s",leftcode,code->u.ic_relop.relop,rightcode);
        break;
    }
    case IC_GOTO:{
        #ifdef L4DEBUG
        LogGreen("In print IC_GOTO");
        #endif
        sprintf(outstr,"GOTO label%d\n",code->u.ic_goto.label->u.lab_no);
        break;
    }  
    case IC_IFGOTO:{
        #ifdef L4DEBUG
        LogGreen("In print IC_IFGOTO");
        #endif
        sprintf(outstr,"IF %s GOTO label%d\n",
            PrintEachInterCode(code->u.ic_ifgoto.relop),code->u.ic_ifgoto.label->u.lab_no);
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
        else 
            TODO();

        sprintf(outstr+strlen(outstr),"  jr $ra\n");
        break;
    }
    case IC_DEC:{
        #ifdef L4DEBUG
        LogGreen("In print IC_DEC");
        #endif
        Operand var = code->u.ic_dec.var;
        char* tmpcode = getcode(var);
        sprintf(outstr,"DEC %s %d\n",tmpcode,code->u.ic_dec.size);
        break;
    }
    case IC_ARG:{
        #ifdef L4DEBUG
        LogGreen("In print IC_ARG");
        #endif
        Operand arg = code->u.ic_arg.arg;
        char* tmpcode = getcode(arg);
        sprintf(outstr,"ARG %s\n",tmpcode);
        break;
    }
    case IC_CALL:{
        #ifdef L4DEBUG
        LogGreen("In print IC_CALL");
        #endif
        Operand left = code->u.ic_call.left;
        char* leftcode = getcode(left);
        sprintf(outstr,"%s := CALL %s\n",
            leftcode,code->u.ic_call.function->u.funcname);   
        break;
    }
    case IC_PARAM:{
        #ifdef L4DEBUG
        LogGreen("In print IC_PARAM");
        #endif
        Operand param  = code->u.ic_param.param;
        char* tmpcode = getcode(param);
        sprintf(outstr,"PARAM %s\n",tmpcode);
        break;
    }
    case IC_READ:{
        #ifdef L4DEBUG
        LogGreen("In print IC_READ");
        #endif
        Operand read_var = code->u.ic_read.read_var;
        char* tmpcode = getcode(read_var);
        sprintf(outstr,"READ %s\n",tmpcode);
        break;
    }
    case IC_WRITE:{
        #ifdef L4DEBUG
        LogGreen("In print IC_WRITE");
        #endif
        Operand write_var = code->u.ic_write.write_var;
        char* tmpcode = getcode(write_var);
        sprintf(outstr,"WRITE %s\n",tmpcode);
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

    //初始化记录变量存储位置信息的结构体
    varstore = (struct S*)malloc(var_num*sizeof(struct S));
    memset(varstore,0,sizeof(struct S) * var_num);
    tvarstore = (struct S*)malloc(tvar_num * sizeof(struct S));
    memset(tvarstore,0,sizeof(struct S) *  tvar_num);

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