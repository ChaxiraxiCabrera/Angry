#!/bin/sh

flex lexico.l
bison -yd sintactico.y
g++ -o compilador lex.yy.c y.tab.c tablaSimbolos.cpp genCodigo.c -lfl
