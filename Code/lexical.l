%option yylineno
letter    [_A-Za-z]
ws ([ \r\n])+

wrongoct    0([0-7])*([89])+([0-9])*
wronghex    0[xX][0-9A-Fa-f]*[G-Zg-z]+[0-9A-Za-z]*
int    [1-9]([0-9])*|0([0-7])*|0[xX]([0-9A-Fa-f])+
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
{wrongoct} {printf("Error tpye A at Line %d: Illegal octal number \'%s\'\n",yylineno,yytext);}
{wronghex} {printf("Error tpye A at Line %d: Illegal hexadecimal number \'%s\'\n",yylineno,yytext);}
{int} {printf("Integer value %d\n",atoi(yytext));}
{wrongint} {printf("Error tpye A at Line %d: Illegal int number \'%s\'\n",yylineno,yytext);}

{wrongfloat} {printf("Error tpye A at Line %d: Illegal float number \'%s\'\n",yylineno,yytext);}
{float} {printf("Float value %f\n", atof(yytext));}

{comment} {printf("COMMENT BLOCK %s\n", yytext);}
{div}{star} {
    printf("Error type A at Line %d: unterminated comment.\n", yylineno);
    char c = input();
    while(c != '\0') c = input();
}
{semi} {printf("SEMI\n");}
{comma} {printf("COMMA\n");}
{assignop} {printf("ASSIGNOP\n");}
{relop} {printf("RELOP value %s\n",yytext);}
{plus} {printf("PLUS\n");}
{minus} {printf("MINUS\n");}
{star} {printf("STAR\n");}
{div} {printf("DIV\n");}
{and} {printf("AND\n");}
{or} {printf("OR\n");}
{dot} {printf("DOT\n");}
{not} {printf("NOT\n");}
{type} {printf("TYPE value %s\n",yytext);}
{lp} {printf("LP\n");}
{rp} {printf("RP\n");}
{lb} {printf("LB\n");}
{rb} {printf("RB\n");}
{lc} {printf("LC\n");}
{rc} {printf("RC\n");}
{struct} {printf("STRUCT\n");}
{return} {printf("RETURN\n");}
{if} {printf("IF\n");}
{else} {printf("ELSE\n");}
{while} {printf("WHILE\n");}
{id} {printf("ID value %s\n",yytext);}
{ws} {/**/}
. {printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext);}

%%

