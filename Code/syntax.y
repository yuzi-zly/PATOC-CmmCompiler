%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    void yyerror(const char * msg);

    // #define YYDEBUG 1
    // int yydebug = 1;
%}
%locations
%error-verbose 

/*declared types*/
%union {
    int type_int;
    float type_float;
    char* type_string;
}

/*declared tokens*/
%token <type_int> INT
%token <type_float> FLOAT
%token SEMI COMMA ASSIGNOP
%token <type_string> RELOP 
%token PLUS MINUS STAR DIV AND OR DOT NOT
%token <type_string> TYPE
%token LP RP LB RB LC RC
%token STRUCT RETURN IF ELSE WHILE
%token <type_string> ID


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


/* Operators */
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right HIGHER_THAN_MINUS NOT
%left DOT LB RB LP RP 




%%
/* High-level Definitions */
Program : ExtDefList
    ;
ExtDefList : ExtDef ExtDefList
    |   /* empty*/
    ;
ExtDef : Specifier ExtDecList SEMI
    |   Specifier SEMI
    |   Specifier FunDec CompSt
    |   error SEMI
    |   Specifier ExtDecList error
    |   Specifier error 
    ;
ExtDecList : VarDec
    |   VarDec COMMA ExtDecList
    ;

/* Specifiers */
Specifier : TYPE
    |   StructSpecifier
    ;
StructSpecifier : STRUCT OptTag LC DefList RC
    |   STRUCT Tag 
    |   STRUCT OptTag LC error RC
    |   STRUCT OptTag LC error
    ;
OptTag : ID
    |   /*empty*/
    ;
Tag : ID
    ;

/* Declarators */
VarDec : ID
    |   VarDec LB INT RB
    |   VarDec LB error RB
    ;
FunDec : ID LP VarList RP
    |   ID LP RP
    |   ID LP error RP
    |   ID LP error
    ;
VarList : ParamDec COMMA VarList
    |   ParamDec
    ;
ParamDec : Specifier VarDec
    ;

/* Statements */
CompSt : LC DefList StmtList RC
    ;

StmtList : Stmt StmtList
    |   /*empty*/
    ;
Stmt : Exp SEMI
    |   Exp error
    |   CompSt
    |   RETURN Exp SEMI
    |   RETURN  Exp error
    |   error SEMI
    |   IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
    |   IF LP Exp RP Stmt ELSE Stmt
    |   WHILE LP Exp RP Stmt
    |   IF LP error RP Stmt %prec LOWER_THAN_ELSE
    |   IF LP error RP Stmt ELSE Stmt
    |   WHILE LP error RP Stmt
    |   IF LP error Stmt %prec LOWER_THAN_ELSE
    |   IF LP error Stmt ELSE Stmt
    |   WHILE LP error Stmt
    |   IF error RP Stmt %prec LOWER_THAN_ELSE
    |   IF error RP Stmt ELSE Stmt
    |   WHILE error RP Stmt
    ;

/* Local Definitions */
DefList : Def DefList
    |   /*empty*/
    ;
Def : Specifier DecList SEMI
    |   Specifier DefList error
    ;
DecList : Dec
    |   Dec COMMA DecList
    ;
Dec : VarDec
    |   VarDec ASSIGNOP Exp
    ;

/* Expressions */
Exp : Exp ASSIGNOP Exp
    |   Exp AND Exp
    |   Exp OR Exp
    |   Exp RELOP Exp
    |   Exp PLUS Exp
    |   Exp MINUS Exp
    |   Exp STAR Exp
    |   Exp DIV Exp
    |   LP Exp RP
    |   MINUS Exp %prec HIGHER_THAN_MINUS
    |   NOT Exp
    |   ID LP Args RP
    |   ID LP RP
    |   Exp LB Exp RB
    |   Exp DOT ID
    |   ID
    |   INT
    |   FLOAT
    |   Exp LB error RB
    |   LP error RP
    |   ID LP error RP
    ;
Args : Exp COMMA Args
    |   Exp
    ;

%%

#include "lex.yy.c"

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

void yyerror(const char* msg){
    fprintf(stderr, "Error type B at Line %d: %s\n",yylineno,msg);
}