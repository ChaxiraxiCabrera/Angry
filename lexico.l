
%{
#include "y.tab.h"
#include "tablaSimbolos.h"
#include "stdio.h"
int numlin = 1;


%}
str	[^\"]
letter	[a-zA-Z]
alphanum [a-zA-Z0-9_]
lettermin [a-z]
lettermax [A-Z]

%%
"...".*
\t  {}
" " {}
"¡" {return PARL;}
"!" {return PARR;}
"[" {return CORL;}
"]" {return CORR;}
":" {return KEYL;}
"." {return KEYR;}
\n {numlin++;}
";" {return POINTCOMMA;}
"," {return COMMA;}
"+" {strcpy(yylval.string, yytext); return PLUS;}
"-" {strcpy(yylval.string, yytext); return MINUS;}
"*" {strcpy(yylval.string, yytext); return TIMES;}
"/" {strcpy(yylval.string, yytext); return OVER;}
">=" {strcpy(yylval.string, yytext); return GE;}
"<=" {strcpy(yylval.string, yytext); return LE;}
"<" {strcpy(yylval.string, yytext); return LT;}
">" {strcpy(yylval.string, yytext); return GT;}
"==" {strcpy(yylval.string, yytext); return EQ;}
"'=" {strcpy(yylval.string, yytext); return NEQ;}
"=" {strcpy(yylval.string, yytext); return EQUAL;}
"&&" {strcpy(yylval.string, yytext); return AND;}
"??" {strcpy(yylval.string, yytext); return OR;}
"'" {strcpy(yylval.string, yytext); return NOT;}

"INT"	{strcpy(yylval.string, yytext); return INT;}
"FLOAT"	{strcpy(yylval.string, yytext); return FLOAT;}
"STRING" {strcpy(yylval.string, yytext); return STR;}
"IF"    {return IF;}
"ELSE" {return ELSE;}
"FUNCTION" {return FUNC;}
"FOR" {return FOR;}
"WHILE" {return WHILE;}
"MAIN" {return MAIN;}
"RETURN" {return RETURN;}
"PRINT"    {return PRINT;}
"TRUE" {strcpy(yylval.string, yytext); return BOOL;}
"FALSE" {strcpy(yylval.string, yytext); return BOOL;}

([0-9])+"."([0-9])* {strcpy(yylval.string, yytext); return FLOATNUM;}
([0-9])* {strcpy(yylval.string, yytext); return INTNUM;}
{lettermin}{alphanum}* {strcpy(yylval.string, yytext); return VARID;}
{lettermax}{alphanum}* {strcpy(yylval.string, yytext); return FUNID;}
"\""{str}+"\"" {strcpy(yylval.string, yytext); return STRING;}
%%





