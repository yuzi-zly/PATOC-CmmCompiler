%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    void yyerror(char * msg);
    // #define YYDEBUG 1
    // int yydebug = 1;
%}
%locations

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

/* Operators */
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right HIGHER_THAN_MINUS NOT
%left DOT LB RB LP RP 


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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
    ;
OptTag : ID
    |   /*empty*/
    ;
Tag : ID
    ;

/* Declarators */
VarDec : ID
    |   VarDec LB INT RB
    ;
FunDec : ID LP VarList RP
    |   ID LP RP
    ;
VarList : ParamDec COMMA VarList
    |   ParamDec
    ;
ParamDec : Specifier VarDec
    ;

/* Statements */
CompSt : LC DefList StmtList RC
    |   error RC
    ;
StmtList : Stmt StmtList
    |   /*empty*/
    ;
Stmt : Exp SEMI
    |   CompSt
    |   RETURN Exp SEMI
    |   IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
    |   IF LP Exp RP Stmt ELSE Stmt
    |   WHILE LP Exp RP Stmt
    |   error SEMI
    ;

/* Local Definitions */
DefList : Def DefList
    |   /*empty*/
    ;
Def : Specifier DecList SEMI
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
    |   MINUS Exp
    |   NOT Exp
    |   ID LP Args RP
    |   ID LP RP
    |   Exp LB Exp RB
    |   Exp DOT ID
    |   ID
    |   INT
    |   FLOAT
    |   error RB 
    |   Exp LB error
    ;
Args : Exp COMMA Args
    |   Exp
    ;

%%

#include "lex.yy.c"

void yyerror(char* msg){
    fprintf(stderr, "Error type B at Line %d: %s\n",yylineno,msg);
}