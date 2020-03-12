%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "lex.yy.c"
    
    int yylex();
    void yyerror(const char * msg);
    struct Node * root;

    // #define YYDEBUG 1
    // int yydebug = 1;
%}

%locations
%error-verbose 

/*declared types*/
%union {
        struct Node *ptr;
}

%type <ptr> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier
%type <ptr> OptTag Tag VarDec FunDec VarList ParamDec CompSt StmtList Stmt
%type <ptr> DefList Def DecList Dec Exp Args 

/*declared tokens*/
%token <ptr> INT
%token <ptr> FLOAT
%token <ptr> SEMI COMMA ASSIGNOP
%token <ptr> RELOP 
%token <ptr> PLUS MINUS STAR DIV AND OR DOT NOT
%token <ptr> TYPE
%token <ptr> LP RP LB RB LC RC
%token <ptr> STRUCT RETURN IF ELSE WHILE
%token <ptr> ID


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%nonassoc LOWER_THAN_RP

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
Program :   ExtDefList {
                $$ = Create("Program",@1.first_line);
                AddNode($$,$1);
                root = $$;
            }
    ;
ExtDefList :    ExtDef ExtDefList {
                    $$ = Create("ExtDefList",@1.first_line);
                    AddNode($$,$1);
                    AddNode($$,$2);
                    root = $$;
                }
    |   /* empty*/ {/**/}
    ;
ExtDef :    Specifier ExtDecList SEMI {
                $$ = Create("ExtDef",@1.first_line);
                AddNode($$,$1);
                AddNode($$,$2);
                AddNode($$,$3);
                root = $$;
            }
    |   Specifier ExtDecList error { print_flag = 0;}
    |   Specifier SEMI {
            $$ = Create("ExtDef",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            root = $$;
        }
    |   Specifier FunDec CompSt {
            $$ = Create("ExtDef",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   error SEMI { print_flag = 0; }
    |   Specifier error  { print_flag = 0; }
    |   Specifier ID LP error CompSt { print_flag = 0; }
    ;
ExtDecList :    VarDec {
                    $$ = Create("ExtDecList",@1.first_line);
                    AddNode($$,$1);
                    root = $$;
                }   
    |   VarDec COMMA ExtDecList {
            $$ = Create("ExtDecList",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    ;

/* Specifiers */
Specifier : TYPE {
                $$ = Create("Specifier",@1.first_line);
                AddNode($$,$1);
                root = $$;
            }
    |   StructSpecifier {
            $$ = Create("Specifier",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    ;
StructSpecifier :   STRUCT OptTag LC DefList RC {
                        $$ = Create("StructSpecifier",@1.first_line);
                        AddNode($$,$1);
                        AddNode($$,$2);
                        AddNode($$,$3);
                        AddNode($$,$4);
                        AddNode($$,$5);
                        root = $$;
                    }
    |   STRUCT Tag {
            $$ = Create("StructSpecifier",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            root = $$;
        }
    |   STRUCT OptTag LC error RC { print_flag = 0; }
    ;
OptTag :    ID {
                $$ = Create("OptTag",@1.first_line);
                AddNode($$,$1);
                root = $$;
            }
    |   /*empty*/ {/**/}
    ;
Tag :   ID {
            $$ = Create("Tag",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    ;

/* Declarators */
VarDec :    ID {
                $$ = Create("VarDec",@1.first_line);
                AddNode($$,$1);
                root = $$;
            }
    |   VarDec LB INT RB {
            $$ = Create("VarDec",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            AddNode($$,$4);
            root = $$;
        }
    ;
FunDec :    ID LP VarList RP {
                $$ = Create("FunDec",@1.first_line);
                AddNode($$,$1);
                AddNode($$,$2);
                AddNode($$,$3);
                AddNode($$,$4);
                root = $$;
            }
    |   ID LP RP {
            $$ = Create("FunDec",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   ID LP error RP { print_flag = 0; }
    ;
VarList :   ParamDec COMMA VarList {
                $$ = Create("VarList",@1.first_line);
                AddNode($$,$1);
                AddNode($$,$2);
                AddNode($$,$3);
                root = $$;
            }
    |   ParamDec {
            $$ = Create("VarList",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    ;
ParamDec :  Specifier VarDec {
                $$ = Create("ParamDec",@1.first_line);
                AddNode($$,$1);
                AddNode($$,$2);
                root = $$;
            }
    ;

/* Statements */
CompSt :    LC DefList StmtList RC {
                $$ = Create("CompSt",@1.first_line);
                AddNode($$,$1);
                AddNode($$,$2);
                AddNode($$,$3);
                AddNode($$,$4);
                root = $$;
            }
    ;

StmtList :  Stmt StmtList {
                $$ = Create("StmtList",@1.first_line);
                AddNode($$,$1);
                AddNode($$,$2);
                root = $$;
            }
    |   /*empty*/ {/**/}
    ;
Stmt :  Exp SEMI {
            $$ = Create("Stmt",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            root = $$;
        }
    |   Exp error { print_flag = 0; }
    |   Exp LB error SEMI { print_flag = 0; }
    |   ID LP error SEMI { print_flag = 0; }
    |   LP error SEMI { print_flag = 0; }
    |   CompSt {
            $$ = Create("Stmt",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    |   RETURN Exp SEMI {
            $$ = Create("Stmt",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   RETURN  Exp error { print_flag = 0; }
    |   RETURN Exp LB error SEMI { print_flag = 0; }
    |   RETURN ID LP error SEMI { print_flag = 0; }
    |   RETURN LP error SEMI { print_flag = 0; }
    |   IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
            $$ = Create("Stmt",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            AddNode($$,$4);
            AddNode($$,$5);
            root = $$;
        }
    |   IF LP Exp RP Stmt ELSE Stmt {
            $$ = Create("Stmt",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            AddNode($$,$4);
            AddNode($$,$5);
            AddNode($$,$6);
            AddNode($$,$7);
            root = $$;
        }
    |   WHILE LP Exp RP Stmt {
            $$ = Create("Stmt",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            AddNode($$,$4);
            AddNode($$,$5);
            root = $$;
        }
    |   IF LP error RP Stmt %prec LOWER_THAN_ELSE { print_flag = 0; }
    |   IF LP error RP Stmt ELSE Stmt { print_flag = 0; }
    |   WHILE LP error RP Stmt { print_flag = 0; }
    |   IF LP error Stmt %prec LOWER_THAN_ELSE { print_flag = 0; }
    |   IF LP error Stmt ELSE Stmt { print_flag = 0; }
    |   WHILE LP error Stmt { print_flag = 0; }
    |   IF error RP Stmt %prec LOWER_THAN_ELSE { print_flag = 0; }
    |   IF error RP Stmt ELSE Stmt { print_flag = 0; }
    |   WHILE error RP Stmt { print_flag = 0; }
    ;

/* Local Definitions */
DefList :   Def DefList {
                $$ = Create("DefList",@1.first_line);
                AddNode($$,$1);
                AddNode($$,$2);
                root = $$;
            }
    |   /*empty*/ {/**/}
    ;
Def :   Specifier DecList SEMI {
            $$ = Create("Def",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Specifier DecList error { print_flag = 0; }
    |   error SEMI  { print_flag = 0; }
    ;
DecList :   Dec {
                $$ = Create("DecList",@1.first_line);
                AddNode($$,$1);
                root = $$;
            }
    |   Dec COMMA DecList {
                $$ = Create("DecList",@1.first_line);
                AddNode($$,$1);
                AddNode($$,$2);
                AddNode($$,$3);
                root = $$;
        }
    ;
Dec :   VarDec {
            $$ = Create("Dec",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    |   VarDec ASSIGNOP Exp {
            $$ = Create("Dec",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    ;

/* Expressions */
Exp :   Exp ASSIGNOP Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Exp AND Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Exp OR Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Exp RELOP Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Exp PLUS Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Exp MINUS Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Exp STAR Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Exp DIV Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   LP Exp RP {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   MINUS Exp %prec HIGHER_THAN_MINUS {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            root = $$;
        }
    |   NOT Exp {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            root = $$;
        }
    |   ID LP Args RP {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            AddNode($$,$4);
            root = $$;
        }
    |   ID LP RP {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   Exp LB Exp RB {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            AddNode($$,$4);
            root = $$;
        }
    |   Exp DOT ID {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root = $$;
        }
    |   ID {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    |   INT {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    |   FLOAT {
            $$ = Create("Exp",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    |   Exp LB error RB { print_flag = 0; }
    |   LP error RP { print_flag = 0; }
    |   ID LP error RP { print_flag = 0; }
    ;
Args :  Exp COMMA Args {
            $$ = Create("Args",@1.first_line);
            AddNode($$,$1);
            AddNode($$,$2);
            AddNode($$,$3);
            root =$$;
        }
    |   Exp {
            $$ = Create("Args",@1.first_line);
            AddNode($$,$1);
            root = $$;
        }
    ;

%%

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


