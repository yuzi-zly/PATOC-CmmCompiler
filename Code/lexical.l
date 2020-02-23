%option yylineno
LETTER    [_A-Za-z]
WS ([ \r\n])+

WRONGOCT    0([0-7])*([89])+([0-9])*
WRONGHEX    0[xX][0-9A-Fa-f]*[G-Zg-z]+[0-9A-Za-z]*
WRONGINT    [0-9][0-9]*({LETTER})+[0-9]*
INT    [1-9]([0-9])*|0([0-7])*|0[xX][0-9A-Fa-f]+

WRONGFLOAT \.[0-9]+|[0-9]+\.
FLOAT    [0-9]+\.[0-9]+|[0-9]+\.[0-9]*[eE][+-]?[0-9]+|[0-9]*\.[0-9]+[eE][+-]?[0-9]+

COMMENT    "//".*(\n)?|"/\*"[^*]*("\*")+([^/*][^*]*("\*")+)*"/"
SEMI    ";"
COMMA   ","
ASSIGNOP    "="
RELOP    ">"|"<"|">="|"<="|"=="|"!="
PLUS    "\+"
MINUS   "\-"
STAR    "\*"
DIV    "/"
AND    "&&"
OR    "||"
DOT    "."
NOT    "!"
TYPE    "int"|"float"
LP    "("
RP    ")"
LB    "["
RB    "]"
LC    "{"
RC    "}"
STRUCT    "struct"
RETURN    "return"
IF    "if"
ELSE    "else"
WHILE    "while"
ID    ({LETTER}({LETTER}|[0-9])*){1,31}


%%
{WRONGOCT} {printf("Error tpye A at Line %d: Illegal octal number \'%s\'\n",yylineno,yytext);}
{WRONGHEX} {printf("Error tpye A at Line %d: Illegal hexadecimal number \'%s\'\n",yylineno,yytext);}
{WRONGINT} {printf("Error tpye A at Line %d: Illegal int number \'%s\'\n",yylineno,yytext);}
{INT} {printf("Integer value %d\n",atoi(yytext));}

{WRONGFLOAT} {printf("Error tpye A at Line %d: Illegal float number \'%s\'\n",yylineno,yytext);}
{FLOAT} {printf("Float value %f\n", atof(yytext));}

{COMMENT} {printf("COMMENT BLOCK %s\n", yytext);}
{DIV}{STAR} {
    printf("Error type A at Line %d: unterminated comment.\n", yylineno);
    char c = input();
    while(c != '\0') c = input();
}
{SEMI} {printf("SEMI\n");}
{COMMA} {printf("COMMA\n");}
{ASSIGNOP} {printf("ASSIGNOP\n");}
{RELOP} {printf("RELOP value %s\n",yytext);}
{PLUS} {printf("PLUS\n");}
{MINUS} {printf("MINUS\n");}
{STAR} {printf("STAR\n");}
{DIV} {printf("DIV\n");}
{AND} {printf("AND\n");}
{OR} {printf("OR\n");}
{DOT} {printf("DOT\n");}
{NOT} {printf("NOT\n");}
{TYPE} {printf("TYPE value %s\n",yytext);}
{LP} {printf("LP\n");}
{RP} {printf("RP\n");}
{LB} {printf("LB\n");}
{RB} {printf("RB\n");}
{LC} {printf("LC\n");}
{RC} {printf("RC\n");}
{STRUCT} {printf("STRUCT\n");}
{RETURN} {printf("RETURN\n");}
{IF} {printf("IF\n");}
{ELSE} {printf("ELSE\n");}
{WHILE} {printf("WHILE\n");}
{ID} {printf("ID value %s\n",yytext);}
{WS} {/**/}
. {printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext);}

%%

