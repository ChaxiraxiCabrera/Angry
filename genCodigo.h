
#include <stdio.h>
#include "tablaSimbolos.h"

struct qMachine{
  int Ztop;
  int Htop;


  int R[6]; 
  int RR[4]; 

  int lastRstack;
  int lastRRstack; 

  int nextLabel; 
  int nextCodeNumber;

  char formatPutString[15];
  char formatPutInt[15];
  char formatPutChar[15];
  char formatPutFloat[15];
  char formatGetChar[15];
  char formatNewLine[15];

  unsigned int formatPutStringAddress;
  unsigned int formatPutIntAddress;
  unsigned int formatPutCharAddress;
  unsigned int formatPutFloatAddress;
  unsigned int formatGetCharAddress;
  unsigned int formatNewLineAddress;

  

  int typeExp;
  int ZR6;
};


void generateCodeStart( FILE* fout, qMachine *Q );
void resetZR6(qMachine *Q);
void generateCodeEnd( FILE* fout );
void generateCodeMain(FILE* fout, qMachine *Q, int nFunction);

void generateCodePrintInt( FILE* fout ,qMachine *Q,int num);
void generateCodePrintFloat( FILE* fout , qMachine *Q, float num);
void generateCodePrintStr( FILE* fout ,qMachine *Q, char* str);
void generateCodePrintVar( FILE* fout , qMachine *Q, symrec *sym);

void generateCodeReturn(FILE* fout, qMachine *Q, int addressReturn, char* typeFunction);
int *generateCodeFunction(FILE* fout , qMachine *Q, int nParam);
void generateCodeCallFunction(FILE* fout , qMachine *Q, symrec *sym);
int generateCodeArgs(FILE* fout , qMachine *Q, char* type);
void generateCodeConst(FILE* fout , qMachine *Q, char* value, int typeValue);
void generateCodeVar(FILE* fout , qMachine *Q, symrec *sym);
void generateCodeBool(FILE* fout , qMachine *Q, int value);

void generateCodeExpression(FILE* fout , qMachine *Q, char* op, int type, int type2);

void generateCodeSave(FILE* fout , qMachine *Q, symrec *sym);

int generatedCodeLoop(FILE* fout , qMachine *Q);
void generatedCodeEvaluateLoop(FILE* fout , qMachine *Q, int jump);
void generatedCodeCloseLoop(FILE* fout , qMachine *Q, int ini, int end);

int generatedCodeIf(FILE* fout , qMachine *Q);
void generatedCodeCloseIf(FILE* fout , qMachine *Q, int end);
void generatedCodeElse(FILE* fout , qMachine *Q, int ini);
void generatedCodeCloseElse(FILE* fout , qMachine *Q, int ini);

int pushRstack(FILE* fout, qMachine *Q, int r, int typeReg);
int popRstack(FILE* fout, qMachine *Q, int r, int typeReg);
int newRegister(FILE* fout, qMachine *Q, int typeReg);
int popRegister(FILE* fout, qMachine *Q, int typeReg);
void releaseR(FILE* fout, qMachine *Q);
int assignMemoryVar(FILE* fout, qMachine *Q, char* type);
void saveAllR(FILE* fout, qMachine *Q);
void restoreAllR(FILE* fout, qMachine *Q);
void checkExpression(qMachine *Q, int type, int line);
void resetCheckExpression(qMachine *Q);
void checkInit(qMachine *Q, char* varType, int line);
void checkID(qMachine *Q, symrec* sym, int line);

