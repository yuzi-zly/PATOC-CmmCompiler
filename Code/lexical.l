%option yylineno

%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "syntax.tab.h"
    #include "SynTree.h"

    
    int print_flag = 1;// 1-ok ,0-error
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno;
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
    yylval.ptr = Create("INT",yylineno,0);
    yylval.ptr->value.type_int = atoi(yytext);
    return INT;
}
{octal} {
    int value = 0;
    int len = strlen(yytext);
    for(int i = 1; i < len; ++i){
        value =  value*8 + yytext[i] - 48;
    }
    yylval.ptr = Create("INT",yylineno,0);
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
    yylval.ptr = Create("INT",yylineno,0);
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
    yylval.ptr = Create("FLOAT",yylineno,0);
    yylval.ptr->value.type_float = atof(yytext);
    return FLOAT;
}

{comment} { /**/ }
{div}{star} {
    print_flag = 0;
    int line = yylineno;
    char c = input();
    while(c != '\0') {
        if(c == '\n')
            line++;
         c = input();
    }
    printf("Error type A at Line %d: unterminated comment.\n", line);

}


{semi} {
    yylval.ptr = Create("SEMI",yylineno,0);
    return SEMI;
}
{comma} {
    yylval.ptr = Create("COMMA",yylineno,0);    
    return COMMA;
}
{assignop} {
    yylval.ptr = Create("ASSIGNOP",yylineno,0);
    return ASSIGNOP;
}
{relop} {
    yylval.ptr = Create("RELOP",yylineno,0);
    strncpy(yylval.ptr->value.type_string,yytext,strlen(yytext));
    return RELOP;
}
{plus} {
    yylval.ptr = Create("PLUS",yylineno,0);
    return PLUS;
}
{minus} {
    yylval.ptr = Create("MINUS",yylineno,0);
    return MINUS;
}
{star} {
    yylval.ptr = Create("STAR",yylineno,0);
    return STAR;
}
{div} {
    yylval.ptr = Create("DIV",yylineno,0);
    return DIV;
}
{and} {
    yylval.ptr = Create("AND",yylineno,0);
    return AND;
}
{or} {
    yylval.ptr = Create("OR",yylineno,0);
    return OR;
}
{dot} {
    yylval.ptr = Create("DOT",yylineno,0);
    return DOT;
}
{not} {
    yylval.ptr = Create("NOT",yylineno,0);
    return NOT;
}
{type} {
    yylval.ptr = Create("TYPE",yylineno,0);
    strncpy(yylval.ptr->value.type_string,yytext,strlen(yytext));
    return TYPE;
}
{lp} {
    yylval.ptr = Create("LP",yylineno,0);
    return LP;
}
{rp} {
    yylval.ptr = Create("RP",yylineno,0);
    return RP;
}
{lb} {
    yylval.ptr = Create("LB",yylineno,0);
    return LB;
}
{rb} {
    yylval.ptr = Create("RB",yylineno,0);
    return RB;
}
{lc} {
    yylval.ptr = Create("LC",yylineno,0);
    return LC;
}
{rc} {
    yylval.ptr = Create("RC",yylineno,0);
    return RC;
}
{struct} {
    yylval.ptr = Create("STRUCT",yylineno,0);
    return STRUCT;
}
{return} {
    yylval.ptr = Create("RETURN",yylineno,0);
    return RETURN;
}
{if} {
    yylval.ptr = Create("IF",yylineno,0);
    return IF;
}
{else} {
    yylval.ptr = Create("ELSE",yylineno,0);
    return ELSE;
}
{while} {
    yylval.ptr = Create("WHILE",yylineno,0);
    return WHILE;
}
{id} {
    yylval.ptr = Create("ID",yylineno,0);
    strncpy(yylval.ptr->value.type_string,yytext,strlen(yytext));
    return ID;
}
{ws} {/* */}
\n  {/**/}


. {
    printf("Error type A at Line %d: Mysterious characters \'%s\' \n",yylineno, yytext);
    print_flag = 0;    
}

%%

