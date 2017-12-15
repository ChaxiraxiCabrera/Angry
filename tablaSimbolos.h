#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <string>
#include <list>
using namespace std;

#define SYMTBLSIZE 1000
#define D_BISON
#define DEBUGGING false

//tipos de simbolos 
enum symtype{ VAR,FUN };

//tipos de variables
enum vartype{ _INT , _FLOAT, _STR};

//estructura de un simbolo(puede ser Variable o Funcion)
struct symrec {
    string name;   
    symtype typesim;                    
    vartype typeVar; 
	int memory;
	int label;
	int nParam;
    int scope; 
};

//tabla de simbolos
class symtable{
    list<symrec> table[SYMTBLSIZE];    
    int currentScope;    
    
//funciones
public:
    //genera un codigo hash para un simbolo
    int getHash(string);
    //inicializa la tabla	
    symtable();    
    //genera el nombre de variable
    string generanameVar(); 
    //inserta una variable
    symrec * insertVar(string name, vartype typeVar, int amb, int mem);    
    //inserta una funcion
    symrec * insertFun(string name, vartype typeVar, int mem, int label, int nParam);    
    //crea un nuevo ambito
    void newScope();
    //cierra un ambito
    void endScope(); 
    //devuelve si existe el simbolo en la tabla
    bool existSymbol(string name);
    //obtiene un simbolo de la tabla
	symrec * getSymbol(string name);
    //devuelve ambito actual
	int scope() { return currentScope; }; 
    //devuelve el ambito de un simbolo
	int scopeSymbol(string name); 
    //imprime la tabla por consola
	void printState();
    //imprime los simbolos de la tabla 
	void printSymbol(symrec * s);
};


#endif
