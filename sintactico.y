%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tablaSimbolos.h"
#include "genCodigo.h"

#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>

extern FILE *yyin;
extern int numlin;
int yydebug=1;
void yyerror(const char* mens);

extern "C++" {int yylex(void);}
vartype type;
 
qMachine Q;
FILE* fout;

int trace = 0;
symtable table;
void yyerror (char *s);

int typeConst = -1;
int typeExp = -1;

int nFunction = 0;
int addressReturn = 0;
char *typeFunction;

symrec *currentCall = NULL;

int loopStart[100];
int loopEnd[100];
int loopIndex=0;

int ifStart[100];
int ifEnd[100];
int ifIndex=0;

int nParam = 0;

%}

%union {
	int integer; 
	char op;
	char string[50];
}

%error-verbose
%token PARL
%token PARR
%token CORL
%token CORR
%token KEYL
%token KEYR
%token INT
%token FLOAT
%token STR
%token CHAR
%token BOOL
%token IF 
%token ELSE 
%token FUNC 
%token FOR 
%token WHILE
%token MAIN 
%token RETURN 
%token PRINT
%token TRUE 
%token FALSE 
%left PLUS
%left MINUS
%left TIMES
%left OVER 
%left EQ
%left NEQ
%left GE
%left GT
%left LE
%left LT
%left AND
%left OR
%left NOT
%left EQUAL
%token FLOATNUM
%token INTNUM
%token STRING
%token POINTCOMMA
%token FUNTYPE
%token FUNID
%token VARID
%token COMMA
%%

program : {generateCodeStart(fout, &Q);} var_declaration {fprintf(fout,"\tGT(1);\t\t\t//jmp to main\n");} fun_declaration main_function {generateCodeEnd(fout);};

fun_declaration : fun_declaration function {if (trace) printf("%d :: <fun_declaration> fun_declaration function \n",numlin);} 
			| ;

var_declaration : declaration POINTCOMMA var_declaration 
			| ;

main_function : FUNC MAIN {generateCodeMain(fout, &Q, nFunction); table.insertFun("MAIN", type, 0, 0, 0);} PARL PARR  {if (trace) printf("%d :: <main_function>  FUN MAIN PARL PARR block \n",numlin);} {table.newScope();} block {table.endScope();};

function : FUNC type_specifier FUNID {nFunction++; typeFunction = $<string>2;} PARL param_list PARR {int *r = generateCodeFunction(fout, &Q, nParam); addressReturn = r[0];  table.insertFun($<string>3, type, r[0], r[1], nParam); nParam = 0; releaseR(fout, &Q); if (trace) printf("%d :: <function>  FUNC type_specifier FUNID PARL param PARR block \n",numlin);} {table.newScope();} block {table.endScope();fprintf(fout,"\tGT(R5);\t\t\t//End Function\n");resetZR6(&Q);};

block : KEYL { if (trace) printf("%d :: <block>  KEYL statement_list KEYR \n",numlin);} statement_list KEYR  
		| error;

statement_list : statement_list statement 
			| statement;

param_list: param_list COMMA param {if (trace) printf("%d :: <args>  type_specifier VARID COMMA param \n",numlin);}  | param;

param : {if (trace) printf("%d :: <args>  empty \n",numlin);} 
		| type_specifier VARID {nParam++;  table.insertVar($<string>2, type, 1, (nParam*4));};

statement : declaration POINTCOMMA 
		| assign POINTCOMMA 
		| if_stmt 
		| for_stmt 
		| while_stmt
		| return_stmt 
		| print_stmt 
		| call POINTCOMMA ;

declaration : type_specifier VARID {table.insertVar($<string>2, type, 0, assignMemoryVar(fout, &Q, $<string>1));} EQUAL expression {checkInit(&Q, $<string>1, numlin); generateCodeSave(fout,&Q, table.getSymbol($<string>2)); if (trace) printf("%d :: <init>  type_specifier VARID POINTCOMMA  \n",numlin); resetCheckExpression(&Q);} 
		| type_specifier VARID {table.insertVar($<string>2, type, 0, assignMemoryVar(fout, &Q, $<string>1));}
		| error; 

assign : VARID EQUAL expression {generateCodeSave(fout,&Q, table.getSymbol($<string>1)); if (trace) printf("%d :: <assign> VARID EQUAL expression  \n",numlin); resetCheckExpression(&Q);} ;

if_stmt : 
IF PARL expression PARR{int label = generatedCodeIf(fout, &Q); ifStart[ifIndex]=label-1; ifEnd[ifIndex]=label; ifIndex++;} {if (trace) printf("%d :: <if>  IF PARL expression PARR block else  \n",numlin);} {table.newScope();} block {generatedCodeCloseIf(fout , &Q, ifEnd[ifIndex-1]);} {table.endScope();} else;

else : {generatedCodeElse(fout , &Q, ifStart[ifIndex-1]);} {generatedCodeCloseElse(fout , &Q, ifEnd[ifIndex-1]); ifIndex--;}
		| ELSE {generatedCodeElse(fout , &Q, ifStart[ifIndex-1]);} {if (trace) printf("%d :: <else>  ELSE block  	\n",numlin);} {table.newScope();} block {table.endScope();} {generatedCodeCloseElse(fout , &Q, ifEnd[ifIndex-1]); ifIndex--;};

for_stmt : FOR PARL declaration {int label = generatedCodeLoop(fout, &Q); loopStart[loopIndex]=label-1; loopEnd[loopIndex]=label; loopIndex++;} COMMA expression { generatedCodeEvaluateLoop(fout , &Q, loopEnd[loopIndex-1] );} COMMA assign PARR {if (trace) printf("%d :: <for>  FOR PARL assign COMMA expression COMMA increment PARR block_for  \n",numlin); table.newScope();} block {table.endScope(); generatedCodeCloseLoop(fout , &Q, loopStart[loopIndex-1],loopEnd[loopIndex-1] ); loopIndex--;};


while_stmt: WHILE {int label = generatedCodeLoop(fout, &Q); loopStart[loopIndex]=label-1; loopEnd[loopIndex]=label; loopIndex++;} PARL expression  { generatedCodeEvaluateLoop(fout , &Q, loopEnd[loopIndex-1] );} PARR {if (trace) printf("%d :: <while>  WHILE PARL expression PARR block  \n",numlin); table.newScope();} block {table.endScope(); generatedCodeCloseLoop(fout , &Q, loopStart[loopIndex-1],loopEnd[loopIndex-1] ); loopIndex--;};

return_stmt : RETURN expression {generateCodeReturn(fout, &Q, addressReturn, typeFunction);} POINTCOMMA {if (trace) printf("%d :: <return_stmt> \n",numlin); resetCheckExpression(&Q);}; 

print_stmt : PRINT const POINTCOMMA {
								if(typeConst == 0){
									generateCodePrintInt(fout,&Q, atoi($<string>2));
								}else if(typeConst == 1){
									generateCodePrintFloat(fout,&Q, atof($<string>2));
								}else if(typeConst == 2){
									generateCodePrintStr(fout,&Q, $<string>2);
								}
								
								if (trace) printf("%d :: <print> \n",numlin);
							}
		| PRINT VARID POINTCOMMA {symrec *a = table.getSymbol($<string>2); checkID(&Q, a, numlin); generateCodePrintVar(fout,&Q, a);};

expression: assign | simple_expression |comp_expression;

comp_expression: simple_expression logop simple_expression {generateCodeExpression(fout, &Q, $<string>2, typeExp,typeConst);};

logop: AND| OR;

simple_expression: add_expression relop add_expression {generateCodeExpression(fout, &Q, $<string>2, typeExp,typeConst);}  | add_expression;

relop: LE {typeExp = 1;}| LT {typeExp = 1;} | GT {typeExp = 1;} | GE {typeExp = 1;} | EQ {typeExp = 1;} | NEQ{typeExp = 1;};

add_expression: add_expression addop term {generateCodeExpression(fout, &Q, $<string>2, typeExp,typeConst);} | term;

addop: PLUS {typeExp = 0;}| MINUS {typeExp = 0;};

term: term mulop factor {generateCodeExpression(fout, &Q, $<string>2, typeExp,typeConst);}| factor;

mulop: TIMES {typeExp = 0;}| OVER {typeExp = 0;};

factor: PARL expression PARR 
		| VARID {checkID(&Q, table.getSymbol($<string>1), numlin); checkExpression(&Q, table.getSymbol($<string>1)->typeVar, numlin); typeConst = table.getSymbol($<string>1)->typeVar; generateCodeVar(fout, &Q, table.getSymbol($<string>1));}
		| call{generateCodeVar(fout, &Q, currentCall);}
		| booleana {generateCodeConst(fout, &Q, $<string>1,typeConst);}
		| numeric{generateCodeConst(fout, &Q, $<string>1, typeConst);} ; 

const : numeric 
		| STRING {typeConst = 2;} 
		| booleana;

booleana: TRUE{typeConst = 3;} | FALSE {typeConst = 3;};

numeric : INTNUM {checkExpression(&Q, 0, numlin); typeConst = 0;} 
		| FLOATNUM {checkExpression(&Q, 1, numlin); typeConst = 1;};

call : FUNID PARL args PARR {
							currentCall = table.getSymbol($<string>1);
							checkID(&Q, currentCall, numlin);
							generateCodeCallFunction(fout, &Q, currentCall);
						 	if (trace) printf("%d :: <callFunction> \n",numlin);};

args: arg_list | {if (trace) printf("%d :: <args> empty\n",numlin);} ;

arg_list: arg_list COMMA expression {if (trace) printf("%d :: <args> arg_list COMMA expression \n",numlin);} 
			| expression {if (trace) printf("%d :: <param> expression \n",numlin);};

type_specifier : INT {type = _INT; if (trace) printf("%d :: <type_specifier> INT \n",numlin);}
		| FLOAT {type = _FLOAT; if (trace) printf("%d :: <type_specifier> FLOAT \n",numlin);}
		| STR {type = _STR; if (trace) printf("%d :: <type_specifier> STRING \n",numlin);};

%%

int main(int argc, char** argv) {
	fout = fopen("./codigoGenerado.q.c", "w");
	if (argc>1) yyin=fopen(argv[1],"r");
	yyparse();
}
void yyerror(const char* mens) {
	printf("Error en linea %i: %s \n",numlin,mens);
}
