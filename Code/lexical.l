%option yylineno

%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "syntax.tab.h"

    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;
%}

letter    [_A-Za-z]

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
{wrongoct} {printf("Error tpye A at Line %d: Illegal octal number \'%s\'\n",yylineno,yytext); return INT;}
{wronghex} {printf("Error tpye A at Line %d: Illegal hexadecimal number \'%s\'\n",yylineno,yytext); return INT;}
{dec} {
    yylval.type_int = atoi(yytext);
    return INT;
}
{octal} {
    int value = 0;
    int len = strlen(yytext);
    for(int i = 1; i < len; ++i){
        value =  value*8 + yytext[i] - 48;
    }
    yylval.type_int = value;
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
    yylval.type_int = value;
    return INT;
}

{wrongint} {printf("Error tpye A at Line %d: Illegal int number \'%s\'\n",yylineno,yytext); return INT;}

{wrongfloat} {printf("Error tpye A at Line %d: Illegal float number \'%s\'\n",yylineno,yytext); return FLOAT;}
{float} {
    printf("Float value %f\n", atof(yytext));
    yylval.type_float = (float)atof(yytext);
    return FLOAT;
}

{comment} { return COMMENT;}
{div}{star} {
    printf("Error type A at Line %d: unterminated comment.\n", yylineno);
    char c = input();
    while(c != '\0') c = input();

}


{semi} {return SEMI;}
{comma} {return COMMA;}
{assignop} {return ASSIGNOP;}
{relop} {
    yylval.type_string = yytext;
    return RELOP;
}
{plus} {return PLUS;}
{minus} {return MINUS;}
{star} {return STAR;}
{div} {return DIV;}
{and} {return AND;}
{or} {return OR;}
{dot} {return DOT;}
{not} {return NOT;}
{type} {
    yylval.type_string = yytext;
    return TYPE;
}
{lp} {return LP;}
{rp} {return RP;}
{lb} {return LB;}
{rb} {return RB;}
{lc} {return LC;}
{rc} {return RC;}
{struct} {return STRUCT;}
{return} {return RETURN;}
{if} {return IF;}
{else} {return ELSE;}
{while} {return WHILE;}
{id} {
    yylval.type_string = yytext;
    return ID;
}
\n { yycolumn = 1; }
[ \r]+ {/**/}

. {printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext);}

%%

