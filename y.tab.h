/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PARL = 258,
     PARR = 259,
     CORL = 260,
     CORR = 261,
     KEYL = 262,
     KEYR = 263,
     INT = 264,
     FLOAT = 265,
     STR = 266,
     CHAR = 267,
     BOOL = 268,
     IF = 269,
     ELSE = 270,
     FUNC = 271,
     FOR = 272,
     WHILE = 273,
     MAIN = 274,
     RETURN = 275,
     PRINT = 276,
     TRUE = 277,
     FALSE = 278,
     PLUS = 279,
     MINUS = 280,
     TIMES = 281,
     OVER = 282,
     EQ = 283,
     NEQ = 284,
     GE = 285,
     GT = 286,
     LE = 287,
     LT = 288,
     AND = 289,
     OR = 290,
     NOT = 291,
     EQUAL = 292,
     FLOATNUM = 293,
     INTNUM = 294,
     STRING = 295,
     POINTCOMMA = 296,
     FUNTYPE = 297,
     FUNID = 298,
     VARID = 299,
     COMMA = 300
   };
#endif
/* Tokens.  */
#define PARL 258
#define PARR 259
#define CORL 260
#define CORR 261
#define KEYL 262
#define KEYR 263
#define INT 264
#define FLOAT 265
#define STR 266
#define CHAR 267
#define BOOL 268
#define IF 269
#define ELSE 270
#define FUNC 271
#define FOR 272
#define WHILE 273
#define MAIN 274
#define RETURN 275
#define PRINT 276
#define TRUE 277
#define FALSE 278
#define PLUS 279
#define MINUS 280
#define TIMES 281
#define OVER 282
#define EQ 283
#define NEQ 284
#define GE 285
#define GT 286
#define LE 287
#define LT 288
#define AND 289
#define OR 290
#define NOT 291
#define EQUAL 292
#define FLOATNUM 293
#define INTNUM 294
#define STRING 295
#define POINTCOMMA 296
#define FUNTYPE 297
#define FUNID 298
#define VARID 299
#define COMMA 300




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 49 "sintactico.y"

	int integer; 
	char op;
	char string[50];



/* Line 2068 of yacc.c  */
#line 148 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


