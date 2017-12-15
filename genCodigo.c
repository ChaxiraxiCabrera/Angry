#include "genCodigo.h"
#include "tablaSimbolos.h"
#include "Qlib.h"
#include "Q.h"
#include <string.h>
#include <stdio.h>

int isMain = 1;

//inicializacion maquina
void qMachineInit( qMachine *Q ){
	int i;

	Q->Ztop = Z;
	Q->Htop = H;

	for(i=0;i<6;i++){
		Q->R[i] = 0;
	}

	Q->R[6] = 1;
	Q->R[7] = 1;

	for(i=0;i<4;i++){
		Q->RR[i] = 0;
	}

	Q->lastRstack = 0;
	Q->lastRRstack = 0;

	Q->nextLabel  = 2;
	Q->nextCodeNumber = 0;

	strcpy(Q->formatPutString, "%s \\n");
	strcpy(Q->formatPutInt,    "%i \\n");
	strcpy(Q->formatPutChar,   "%c \\n");
	strcpy(Q->formatPutFloat,  "%f \\n");
	strcpy(Q->formatGetChar,   "%c \\n");
	strcpy(Q->formatNewLine,   "   \\n");

	Q->Ztop = Q->Ztop - strlen(Q->formatPutString)-1;
	Q->formatPutStringAddress  = Q->Ztop;
	Q->Ztop = Q->Ztop - strlen(Q->formatPutInt)-1;
	Q->formatPutIntAddress     = Q->Ztop; 
	Q->Ztop = Q->Ztop - strlen(Q->formatPutChar)-1;
	Q->formatPutCharAddress    = Q->Ztop; 
	Q->Ztop = Q->Ztop - strlen(Q->formatPutFloat)-1;
	Q->formatPutFloatAddress     = Q->Ztop; 
	Q->Ztop = Q->Ztop - strlen(Q->formatGetChar)-1;
	Q->formatGetCharAddress     = Q->Ztop; 
	Q->Ztop = Q->Ztop - strlen(Q->formatNewLine)-1;
	Q->formatNewLineAddress     = Q->Ztop; 

	
	Q->typeExp = -1;
	Q->ZR6 = 0;
}


void resetZR6(qMachine *Q){
	Q->ZR6 = 0;
}

//imprime codigo inicio
void generateCodeStart(FILE* fout, qMachine *Q){
	qMachineInit(Q);

	fprintf(fout,"#include \"Q.h\"\n\n");
	fprintf(fout,"BEGIN\t\t\t\t//Start\n");

	fprintf(fout,"STAT(%i)\t\t\t\n", Q->nextCodeNumber);
	fprintf(fout,"\tSTR(0x%x,\"%s\");\t//Format Put string \n", 
		  Q->formatPutStringAddress, Q->formatPutString);
	fprintf(fout,"\tSTR(0x%x,\"%s\");\t//Format Put integer\n",
		  Q->formatPutIntAddress, Q->formatPutInt);
	fprintf(fout,"\tSTR(0x%x,\"%s\");\t//Format Put char\n",
		  Q->formatPutCharAddress, Q->formatPutChar);
	fprintf(fout,"\tSTR(0x%x,\"%s\");\t//Format Get integer\n",
		  Q->formatPutFloatAddress, Q->formatPutFloat);
	fprintf(fout,"\tSTR(0x%x,\"%s\");\t//Format Get char\n",
		  Q->formatGetCharAddress, Q->formatGetChar);
	fprintf(fout,"\tSTR(0x%x,\"%s\");\t//Format New_Line\n",
		  Q->formatNewLineAddress, Q->formatNewLine);
	fprintf(fout,"CODE(%i)\n", Q->nextCodeNumber++);
	fprintf(fout,"L %d:\t\t\t\t\n", 0);
}

//codigo finalizacion
void generateCodeEnd(FILE* fout){
	fprintf(fout,"\tR0=0;\t\t\t//Succesful state\n");
	fprintf(fout,"\tGT(-2);\t\t\t//Finish\n");
	fprintf(fout,"END\n");
}

//codigo main
void generateCodeMain(FILE* fout, qMachine *Q, int nFunction){
	isMain = 1;
	fprintf(fout,"L 1:\t\t\t//Start Main\n");
	for(int i = 0; i < nFunction; i++){
		fprintf(fout,"\tR7 = R7 - 8;\t\t\t//reserve space function\n");
	}
	
	releaseR(fout, Q);
}

//imprime un entero
void generateCodePrintInt( FILE* fout , qMachine *Q, int num){
	pushRstack(fout, Q, 0, 0);
	pushRstack(fout, Q, 1, 0);
	pushRstack(fout, Q, 2, 0);
	
	fprintf(fout,"\t// Start of Print variable\n");
	fprintf(fout,"\tR0=%d;\t\t\t\t//Return label\n", Q->nextLabel);
	fprintf(fout,"\tR1=0x%x;\t\t\t//Format int address\n", Q->formatPutIntAddress );
	fprintf(fout,"\tR2=%i;\t\t//Static variable value\n",num);
	fprintf(fout,"\tGT(putf_);\t\t\t//Print variable\n" );
	fprintf(fout,"L %d:\t\t\t\t\n", Q->nextLabel++);	
	fprintf(fout,"\t// End of Print variable\n");

	popRstack(fout, Q, 2, 0);
	popRstack(fout, Q, 1, 0);
	popRstack(fout, Q, 0, 0);
}

//imprime un float
void generateCodePrintFloat( FILE* fout , qMachine *Q, float num){
	pushRstack(fout, Q, 0, 0);
	pushRstack(fout, Q, 1, 0);
	pushRstack(fout, Q, 2, 0);
	
	fprintf(fout,"\t// Start of Print variable\n");
	fprintf(fout,"\tR0=%d;\t\t\t\t//Return label\n", Q->nextLabel);
	fprintf(fout,"\tR1=0x%x;\t\t\t//Format int address\n", Q->formatPutFloatAddress);
	fprintf(fout,"\tRR2=%f;\t\t//Static variable value\n", num);
	fprintf(fout,"\tGT(putfd_);\t\t\t//Print variable\n");
	fprintf(fout,"L %d:\t\t\t\t\n", Q->nextLabel++);	
	fprintf(fout,"\t// End of Print variable\n");


	popRstack(fout, Q, 2, 0);
	popRstack(fout, Q, 1, 0);
	popRstack(fout, Q, 0, 0);
}

//imprime una string
void generateCodePrintStr( FILE* fout , qMachine *Q, char* str){
	Q->Ztop = Q->Ztop - (strlen(str)-1)*8;

	pushRstack(fout, Q, 0, 0);
	pushRstack(fout, Q, 1, 0);

	fprintf(fout,"STAT(%i)\t\t\t\n", Q->nextCodeNumber);
	fprintf(fout,"\tSTR(0x%x,%s);\t//Format Put string \n", Q->Ztop, str);
	fprintf(fout,"CODE(%i)\n", Q->nextCodeNumber++);

	fprintf(fout,"\t// Start of Print variable\n");
	fprintf(fout,"\tR0=%d;\t\t\t\t//Return label\n", Q->nextLabel);
	fprintf(fout,"\tR1=0x%x;\t\t\t//Format Put string\n", Q->Ztop);
	fprintf(fout,"\tGT(putf_);\t\t\t//Print variable\n" );
	fprintf(fout,"L %d:\t\t\t\t\n", Q->nextLabel++);	
	fprintf(fout,"\t// End of Print variable\n");

	popRstack(fout, Q, 1, 0);
	popRstack(fout, Q, 0, 0);

	Q->Ztop = Q->Ztop + (strlen(str)-1)*8;
}

//imprime una variable
void generateCodePrintVar( FILE* fout , qMachine *Q, symrec *sym){

	pushRstack(fout, Q, 0, 0);
	pushRstack(fout, Q, 1, 0);
	pushRstack(fout, Q, 2, 0);

	fprintf(fout,"\t// Start of Print variable\n");
	fprintf(fout,"\tR0 = %d;\t\t\t//Return label\n", Q->nextLabel);
	if(sym->typeVar == 0){
		fprintf(fout,"\tR1 = 0x%x;\t\t\t//Format int address\n", Q->formatPutIntAddress );
		if (isMain)
			fprintf(fout,"\tR2 = I(0x%x);\t\t\t//Static variable value\n",sym->memory);
		else
			fprintf(fout,"\tR2 = I(R6-%i);\t\t\t//Static variable value\n",sym->memory);
		fprintf(fout,"\tGT(putf_);\t\t\t//Print variable\n" );
	}else if(sym->typeVar == 1){
		fprintf(fout,"\tR1 = 0x%x;\t\t\t//Format int address\n", Q->formatPutFloatAddress );
		if (isMain)
			fprintf(fout,"\tRR2 = F(0x%x);\t\t\t//Static variable value\n",sym->memory);
		else
			fprintf(fout,"\tRR2 = F(R6-%i);\t\t\t//Static variable value\n",sym->memory);
		fprintf(fout,"\tGT(putfd_);\t\t\t//Print variable\n" );
	}
	fprintf(fout,"L %d:\t\t\t\t\n", Q->nextLabel++);	
	fprintf(fout,"\t// End of Print variable\n");

	popRstack(fout, Q, 2, 0);
	popRstack(fout, Q, 1, 0);
	popRstack(fout, Q, 0, 0);
}

//codigo return 
void generateCodeReturn(FILE* fout, qMachine *Q, int addressReturn, char* typeFunction){
	if(typeFunction[0] == 'I'){
		fprintf(fout,"\tI(0x%x) = R%d;\t\t\t//Save return\n", addressReturn, Q->lastRstack-1);
		popRegister(fout, Q, 0);
		fprintf(fout,"\tGT(R5);\t\t\t//End Function\n");
	}else if(typeFunction[0] == 'F'){
		fprintf(fout,"\tF(0x%x) = RR%d;\t\t\t//Save return\n", addressReturn, Q->lastRRstack-1);
		popRegister(fout, Q, 1);
		fprintf(fout,"\tGT(R5);\t\t\t//End Function\n");
	}
	Q->lastRstack = 0;
	Q->lastRRstack = 0;
}

//codigo de funcion
int *generateCodeFunction(FILE* fout , qMachine *Q, int nParam){
	isMain = 0;
	Q->Ztop = Q->Ztop  - 8;
	static int result[2];
	result[0] = Q->Ztop;
	result[1] = Q->nextLabel++;;
	fprintf(fout,"L %d:\t\t\t//New Function\n", result[1]);
	Q->ZR6 = Q->ZR6 + (nParam*4);
	return result;
}

//codigo de llamada funcion
void generateCodeCallFunction(FILE* fout , qMachine *Q, symrec *sym){
	pushRstack(fout, Q, 5, 0);
	pushRstack(fout, Q, 6, 0);
	fprintf(fout,"\tR5 = %d;\t\t\t//Return to main\n", Q->nextLabel);
	
	fprintf(fout,"\tR6 = R7;\t\t\t//Return to main\n");
	int nParam = sym->nParam;
	//fprintf(fout, " //nPARAM =  %i\n", sym->nParam);
	if(sym-> typeVar == 0){
		for(int i = 1; i <= nParam; i++){
			fprintf(fout,"\tR7 = R7 - 4;\t\t\t//Reserve space\n");
			fprintf(fout,"\tI(R7) = R%i;\t\t\t//Save param\n", Q->lastRstack-1 -(nParam-i));
		}
	}else if (sym->typeVar == 1){
		for(int i = 1; i <= nParam; i++){
			fprintf(fout,"\tR7 = R7 - 4;\t\t\t//Reserve space\n");
			fprintf(fout,"\tI(R7) = RR%i;\t\t\t//Save param\n", Q->lastRRstack-1 -(nParam-i));
		}
	}	
	
	fprintf(fout,"\tGT(%d);\t\t\t//Jump to function\n", sym->label);
	fprintf(fout,"L %d:\t\t\t//Continue execution\n", Q->nextLabel++);

	fprintf(fout,"\tR7 = R6;\t\t\t//Return to main\n");
	
	popRstack(fout, Q, 6, 0);	
	popRstack(fout, Q, 5, 0);
}

//codigo argumentos
int generateCodeArgs(FILE* fout , qMachine *Q, char* type){
	int mem = assignMemoryVar(fout, Q, type);
	switch(type[0]){
		case 'I': fprintf(fout,"\tI(R6-%i) = R%d;\t\t\t//Save args\n", mem, newRegister(fout, Q, 0));
				  break;
		case 'F': fprintf(fout,"\tF(R6-%i) = RR%d;\t\t\t//Save args\n", mem, newRegister(fout, Q, 1));
			      break;
	}
	return mem;
}

//codigo constante
void generateCodeConst(FILE* fout , qMachine *Q, char* value, int typeValue){
	if(typeValue == 0){
		fprintf(fout,"\tR%d = %d;\n",newRegister(fout, Q, 0), atoi(value));
	}else if(typeValue == 1){
		fprintf(fout,"\tRR%d = %f;\n",newRegister(fout, Q, 1), atof(value));
	}
}

//codigo variable
void generateCodeVar(FILE* fout , qMachine *Q, symrec *sym){
	if (isMain){	
		if(sym->typeVar == 0){
			fprintf(fout,"\tR%d = I(0x%x);\n",newRegister(fout, Q, 0), sym->memory);
		}else if(sym->typeVar == 1){
			fprintf(fout,"\tRR%d = F(0x%x);\n",newRegister(fout, Q, 1), sym->memory);
		}
	}else{
		if (sym->typesim){
			if(sym->typeVar == 0){
				fprintf(fout,"\tR%d = I(0x%x);\n",newRegister(fout, Q, 0), sym->memory);
			}else if(sym->typeVar == 1){
				fprintf(fout,"\tRR%d = F(0x%x);\n",newRegister(fout, Q, 1), sym->memory);
			}
		}else{
			if(sym->typeVar == 0){
				fprintf(fout,"\tR%d = I(R6-%i);\n",newRegister(fout, Q, 0), sym->memory);
			}else if(sym->typeVar == 1){
				fprintf(fout,"\tRR%d = F(R6-%i);\n",newRegister(fout, Q, 1), sym->memory);
			}
		}
	}
}

//codigo expression
void generateCodeExpression(FILE* fout , qMachine *Q, char op[], int typeExpresion, int typeConst){
	if(op [0] == '\''){
		op[0] = '!';
	}else if (op[0] == '?'){
		op[0] = '|';
		op[1] = '|';
	}

	if(typeExpresion == 0){
		if(typeConst == 0){
			fprintf(fout,"\tR%d = R%d %s R%d;\n", Q->lastRstack-2, Q->lastRstack-2, op,  Q->lastRstack-1);
			popRegister(fout, Q, 0);
		}else if(typeConst == 1){
			fprintf(fout,"\tRR%d = RR%d %s RR%d;\n", Q->lastRRstack-2, Q->lastRRstack-2, op,  Q->lastRRstack-1);
			popRegister(fout, Q, 1);
		}	
	}else if (typeExpresion == 1){
		if(typeConst == 0){
			fprintf(fout,"\tR%d = R%d %s R%d;\n", Q->lastRstack-2, Q->lastRstack-2, op,  Q->lastRstack-1);
			popRegister(fout, Q, 0);
		}else if(typeConst == 1){
			fprintf(fout,"\tR%d = RR%d %s RR%d;\n", newRegister(fout, Q, 0), Q->lastRRstack-2, op,  Q->lastRRstack-1);
			popRegister(fout, Q, 1);
			popRegister(fout, Q, 1);
		}
	}
}

//codigo guarda valor
void generateCodeSave(FILE* fout , qMachine *Q, symrec *sym){
	if (isMain){	
		if(sym->typeVar == 0){
			fprintf(fout,"\tI(0x%x) = R%d;\t\t\t//Saved\n", sym->memory, Q->lastRstack-1);
		 	popRegister(fout, Q, 0);
		}else if(sym->typeVar == 1){
			fprintf(fout,"\tF(0x%x) = RR%d;\t\t\t//Saved\n", sym->memory, Q->lastRRstack-1);
		 	popRegister(fout, Q, 1);
		}
	}else{
		if(sym->typeVar == 0){
			fprintf(fout,"\tI(R6-%i) = R%d;\t\t\t//Saved\n", sym->memory, Q->lastRstack-1);
		 	popRegister(fout, Q, 0);
		}else if(sym->typeVar == 1){
			fprintf(fout,"\tF(R6-%i) = RR%d;\t\t\t//Saved\n", sym->memory, Q->lastRRstack-1);
		 	popRegister(fout, Q, 1);
		}
	}
}

//codigo bucle(for y while)
int generatedCodeLoop(FILE* fout , qMachine *Q){
	fprintf(fout,"L %d:\t\t\t\t\n", Q->nextLabel++);
	int label = Q->nextLabel++;
	return label;
}

//codigo evalua bucle(for y while)
void generatedCodeEvaluateLoop(FILE* fout , qMachine *Q, int jump){
	fprintf(fout,"\tIF(R%d==0) GT(%d);\t//Jump if 0\n", Q->lastRstack-1, jump);	
	popRegister(fout, Q, 0);
}

//codigo cierre (for y while)
void generatedCodeCloseLoop(FILE* fout , qMachine *Q, int ini, int end){
	fprintf(fout,"\tGT(%d);\t//Jump if 0\n", ini);
	fprintf(fout,"L %d:\t\t\t\t\n", end);
}

//codigo if
int generatedCodeIf(FILE* fout , qMachine *Q){
	fprintf(fout,"\tIF(R%d==0) GT(%d);\t//Jump if 0\n", Q->lastRstack-1, Q->nextLabel++);
	popRegister(fout, Q, 0);
	int label = Q->nextLabel++;
	return label;
}

//cierre if
void generatedCodeCloseIf(FILE* fout , qMachine *Q, int end){
	fprintf(fout,"\tGT(%d);\t//Jump if 0\n", end);
}

//codigo else
void generatedCodeElse(FILE* fout , qMachine *Q, int ini){
	fprintf(fout,"L %d:\t\t\t\t\n", ini);
}

//cierre else
void generatedCodeCloseElse(FILE* fout , qMachine *Q, int end){
	fprintf(fout,"L %d:\t\t\t\t\n", end);
}

//push en la pila 
int pushRstack(FILE* fout, qMachine *Q, int r, int typeReg){
		
	if(typeReg == 0){
		Q->Ztop = Q->Ztop - 4;
		fprintf(fout,"\tR7 = R7 - 4;\t\t\t//Save space for register R%d\n", r);
  		fprintf(fout,"\tI(R7) = R%d;\t\t\t//R%d saved\n", r, r);
	}else{
		Q->Ztop = Q->Ztop - 8;
		fprintf(fout,"\tR7 = R7 - 8;\t\t\t//Save space for register R%d\n", r);
  		fprintf(fout,"\tF(R7) = RR%d;\t\t\t//R%d saved\n", r, r);
	}
  	return 0;
	
}

//pop en la pila 
int popRstack(FILE* fout, qMachine *Q, int r, int typeReg){
		if(typeReg == 0){
			Q->Ztop = Q->Ztop + 4;
			fprintf(fout,"\tR%d = I(R7);\t\t\t//R%d recovered\n", r, r);
	  		fprintf(fout,"\tR7 = R7 + 4;\t\t\t//Free space for register R%d\n", r);
		}else{
			Q->Ztop = Q->Ztop + 8;
			fprintf(fout,"\tRR%d = F(R7);\t\t\t//R%d recovered\n", r, r);
	  		fprintf(fout,"\tR7 = R7 + 8;\t\t\t//Free space for register R%d\n", r);
		}
	  	return 0;
}

//genera nuevo registro actual
int newRegister(FILE* fout, qMachine *Q, int typeReg){
	int r = 0;
	if(typeReg == 0){
		r = Q->lastRstack++;
  		fprintf(fout,"\t//Get R%d\n", r);
  		Q->lastRstack=Q->lastRstack%6;
		if(Q->R[r] > 0){ 
			pushRstack(fout, Q, r, 0);
		}
		Q->R[r]++;
	}else{
		r = Q->lastRRstack++;
  		fprintf(fout,"\t//Get RR%d\n", r);
  		Q->lastRRstack=Q->lastRRstack%4;
		if(Q->RR[r] > 0){ 
			pushRstack(fout, Q, r, 1);
		}
		Q->R[r]++;
	}
  	return r;
}

//libera registro actual
int popRegister(FILE* fout, qMachine *Q, int typeReg){
	int r = 0;
	if(typeReg == 0){
		r =--Q->lastRstack;
		if(r<0){
			r = 5;
			Q->lastRstack = 5;
		}
		fprintf(fout,"\t//Free R%d\n", r);
		if(Q->R[r] > 1){ 
			popRstack(fout, Q, r, 0);
		}
		Q->R[r]--;
	}else{
		r =--Q->lastRRstack;
		if(r<0){
			r = 4;
			Q->lastRRstack = 4;
		}
		fprintf(fout,"\t//Free RR%d\n", r);
		if(Q->RR[r] > 1){ 
			popRstack(fout, Q, r, 1);
		}
		Q->RR[r]--;
	}
  	return r;
}

//libera todos los registros
void releaseR(FILE* fout, qMachine *Q){
	fprintf(fout,"\t//Free Register\n");
	Q->lastRstack = 0;
	Q->lastRRstack = 0;
	int i;
	for(i=0;i<6;i++){
		Q->R[i] = 0;
	}
	for(i=0;i<4;i++){
		Q->RR[i] = 0;
	}
}

//asigna memoria para una variable
int assignMemoryVar(FILE* fout, qMachine *Q, char* type){
	int sizeType = 0;
	if(isMain){
		switch(type[0]){
			case 'I': sizeType = 4;
					  break;
			case 'F': sizeType = 8;
					  break;
		}
		Q->Ztop = Q->Ztop - sizeType;
		fprintf(fout,"\tR7 = R7 - %d; // Assign memory\n", sizeType);
		return Q->Ztop;
	}else{
		switch(type[0]){
			case 'I': sizeType = 4;
					  break;
			case 'F': sizeType = 8;
					  break;
		}
		Q->ZR6 += sizeType;
		fprintf(fout,"\tR7 = R7 - %d; // Assign memory\n", sizeType);
		return Q->ZR6;
	}
}

//salva todos lso registros
void saveAllR(FILE* fout, qMachine *Q){
	pushRstack(fout, Q, 0, 0);
	pushRstack(fout, Q, 1, 0);
	pushRstack(fout, Q, 2, 0);
	pushRstack(fout, Q, 3, 0);
	pushRstack(fout, Q, 4, 0);
	pushRstack(fout, Q, 0, 1);
	pushRstack(fout, Q, 1, 1);
	pushRstack(fout, Q, 2, 1);
	pushRstack(fout, Q, 3, 1);
}

//restaura registros
void restoreAllR(FILE* fout, qMachine *Q){
	popRstack(fout, Q, 3, 1);
	popRstack(fout, Q, 2, 1);
	popRstack(fout, Q, 1, 1);
	popRstack(fout, Q, 0, 1);
	popRstack(fout, Q, 4, 0);
	popRstack(fout, Q, 3, 0);
	popRstack(fout, Q, 2, 0);
	popRstack(fout, Q, 1, 0);
	popRstack(fout, Q, 0, 0);
}

//comprueba expression(si son del mismo tipo)
void checkExpression(qMachine *Q, int type, int line){
	if(Q->typeExp == -1){
		Q->typeExp = type;
	}else if(Q->typeExp != type){
		printf("COMPILATION ERROR: Line %i Ilegal Expression\n", line);
		exit(1);
	}
}

void resetCheckExpression(qMachine *Q){
	Q->typeExp = -1;
}

//comprueba inicializacion
void checkInit(qMachine *Q, char* varType, int line){
	
	int type = -1;
	switch(varType[0]){
		case 'I': type = 0;
				  break;
		case 'F': type = 1;
			      break;
		case 'S': type = 2;
				  break;
	}
	if(Q->typeExp != type && Q->typeExp != -1){
		printf("COMPILATION ERROR: Line %i Ilegal Initialization\n", line);
		exit(1);
	}
}

//comprueba el id de la variable
void checkID(qMachine *Q, symrec* sym, int line){
	if(sym == NULL){
		printf("COMPILATION ERROR: Line %i The variable or function not exist\n", line);
		exit(1);
	}
}