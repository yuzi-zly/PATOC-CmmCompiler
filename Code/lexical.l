%option yylineno

%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "syntax.tab.h"
    #include "SynTree.h"
    
    int print_flag = 1;// 1-ok ,0-error
    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;
%}

letter    [_A-Za-z]
delim   [ \t\r]
ws  {delim}+

wrongoct    0([0-7])*([89])+([0-9])*
wronghex    0[xX][0-9A-Fa-f]*[G-Zg-z]+[0-9A-Za-z]*
dec    [1-9]([0-9])*|0
octal    0([0-7])+
hex    0[xX]([0-9A-Fa-f])+
wrongint    [0-9][0-9]*{letter}+[0-9]*

wrongfloat \.[0-9]+|[0-9]+\.|[0-9]+\.[0-9]*[eE][+-]?|[0-9]*\.[0-9]+[eE][+-]?
float    [0-9]+\.[0-9]+|[0-9]+\.[0-9]*[eE][+-]?[0-9]+|[0-9]*\.[0-9]+[eE][+-]?[0-9]+

comment    "//".*(\n)?|"/\*"[^*]*("\*")+([^/*][^*]*("\*")+)*"/"
semi    ";"
comma   ","
assignop    "="
relop    ">"|"<"|">="|"<="|"=="|"!="
plus    "\+"
minus   "\-"
star    "\*"
div    "/"
and    "&&"
or    "||"
dot    "."
not    "!"
type    "int"|"float"
lp    "("
rp    ")"
lb    "["
rb    "]"
lc    "{"
rc    "}"
struct    "struct"
return    "return"
if    "if"
else    "else"
while    "while"
id    ({letter}({letter}|[0-9])*){1,31}


%%
{wrongoct} {
    printf("Error tpye A at Line %d: Illegal octal number \'%s\'\n",yylineno,yytext);
    print_flag = 0;
    return INT;
}
{wronghex} {
    printf("Error tpye A at Line %d: Illegal hexadecimal number \'%s\'\n",yylineno,yytext);
    print_flag = 0;    
    return INT;
}
{dec} {
    yylval.ptr = Create("INT",yylineno);
    yylval.ptr->value.type_int = atoi(yytext);
    return INT;
}
{octal} {
    int value = 0;
    int len = strlen(yytext);
    for(int i = 1; i < len; ++i){
        value =  value*8 + yytext[i] - 48;
    }
    yylval.ptr = Create("INT",yylineno);
    yylval.ptr->value.type_int = value;
    return INT;
}
{hex} {
    int value = 0;
    int len = strlen(yytext);
    for(int i = 2; i < len; ++i){
        value = value*16;
        if(yytext[i] >= '0' && yytext[i] <= '9'){
            value = value + yytext[i] - 48; 
        }
        else if(yytext[i] >= 'A' && yytext[i] <= 'F'){
            value = value + yytext[i] - 55;
        }
        else if(yytext[i] >= 'a' && yytext[i] <= 'f'){
            value = value + yytext[i] - 87;
        }
    }
    yylval.ptr = Create("INT",yylineno);
    yylval.ptr->value.type_int = value;
    return INT;
}

{wrongint} {
    printf("Error tpye A at Line %d: Illegal int number \'%s\'\n",yylineno,yytext);
    print_flag = 0;
    return INT;
}

{wrongfloat} {
    printf("Error tpye A at Line %d: Illegal float number \'%s\'\n",yylineno,yytext);
    print_flag = 0;
    return FLOAT;
}
{float} {
    yylval.ptr = Create("FLOAT",yylineno);
    yylval.ptr->value.type_float = (float)atof(yytext);
    return FLOAT;
}

{comment} { /**/ }
{div}{star} {
    printf("Error type A at Line %d: unterminated comment.\n", yylineno);
    print_flag = 0;
    char c = input();
    while(c != '\0') c = input();

}


{semi} {
    yylval.ptr = Create("SEMI",yylineno);
    return SEMI;
}
{comma} {
    yylval.ptr = Create("COMMA",yylineno);    
    return COMMA;
}
{assignop} {
    yylval.ptr = Create("ASSIGNOP",yylineno);
    return ASSIGNOP;
}
{relop} {
    yylval.ptr = Create("RELOP",yylineno);
    strncpy(yylval.ptr->value.type_string,yytext,strlen(yytext));
    return RELOP;
}
{plus} {
    yylval.ptr = Create("PLUS",yylineno);
    return PLUS;
}
{minus} {
    yylval.ptr = Create("MINUS",yylineno);
    return MINUS;
}
{star} {
    yylval.ptr = Create("STAR",yylineno);
    return STAR;
}
{div} {
    yylval.ptr = Create("DIV",yylineno);
    return DIV;
}
{and} {
    yylval.ptr = Create("AND",yylineno);
    return AND;
}
{or} {
    yylval.ptr = Create("OR",yylineno);
    return OR;
}
{dot} {
    yylval.ptr = Create("DOT",yylineno);
    return DOT;
}
{not} {
    yylval.ptr = Create("NOT",yylineno);
    return NOT;
}
{type} {
    yylval.ptr = Create("TYPE",yylineno);
    strncpy(yylval.ptr->value.type_string,yytext,strlen(yytext));
    return TYPE;
}
{lp} {
    yylval.ptr = Create("LP",yylineno);
    return LP;
}
{rp} {
    yylval.ptr = Create("RP",yylineno);
    return RP;
}
{lb} {
    yylval.ptr = Create("LB",yylineno);
    return LB;
}
{rb} {
    yylval.ptr = Create("RB",yylineno);
    return RB;
}
{lc} {
    yylval.ptr = Create("LC",yylineno);
    return LC;
}
{rc} {
    yylval.ptr = Create("RC",yylineno);
    return RC;
}
{struct} {
    yylval.ptr = Create("STRUCT",yylineno);
    return STRUCT;
}
{return} {
    yylval.ptr = Create("RETURN",yylineno);
    return RETURN;
}
{if} {
    yylval.ptr = Create("IF",yylineno);
    return IF;
}
{else} {
    yylval.ptr = Create("ELSE",yylineno);
    return ELSE;
}
{while} {
    yylval.ptr = Create("WHILE",yylineno);
    return WHILE;
}
{id} {
    yylval.ptr = Create("ID",yylineno);
    strncpy(yylval.ptr->value.type_string,yytext,strlen(yytext));
    return ID;
}
{ws} {/* */}
\n  {yycolumn = 1;}


. {
    printf("Error type A at Line %d: Mysterious characters \'%s\' \n",yylineno, yytext);
    print_flag = 0;    
}

%%

