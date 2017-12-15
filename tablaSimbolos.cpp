#include "tablaSimbolos.h"

#include <iostream>

int letter = -1;

symtable::symtable() {
    currentScope = 0;
}

//obtiene el valor hash
int symtable::getHash(string name) {
    int hash = 0;
    for (unsigned int i = 0; i < name.size(); i++)
		hash = hash + name[i];
    return hash % SYMTBLSIZE;
}

//inserta una variable en la tabla
symrec * symtable::insertVar(string name, vartype typeVar, int amb, int mem){
    symrec *returnValue = NULL;
    //si el nombre de la variable ya existe en la tabla imprime mensje de error
    if (existSymbol(name) && (scope() == scopeSymbol(name)) ) {							       
        string msg = "The symbol \"" + name + "\" already exist";
        cout << msg << endl;
    }else{
        //crea el nuevo registro
        symrec symbol;
        symbol.name = name;
        symbol.typesim = VAR;
        symbol.typeVar = typeVar;
        symbol.scope = currentScope + amb;
		symbol.memory = mem;
        //inserta en la posicion hash el simbolo en la tabla
        table[getHash(name)].push_back(symbol);
        returnValue = &table[getHash(name)].back();
    }
    //imprime 
    if (DEBUGGING) printState();
    return returnValue;
}

//inserta una funcion
symrec * symtable::insertFun(string name, vartype typeVar, int mem, int label, int nParam){
    symrec * returnValue = NULL;
    //si el simbolo ya esta en la tabla, imprime mensaje 
	if (existSymbol(name)) {								       
		    string msg = "The symbol \"" + name + "\" already exist";
		    cout << msg << endl;
	}else{
        //crea el nuevo registro
		symrec symbol;
		symbol.name = name;
		symbol.typesim = FUN;
		symbol.typeVar = typeVar;
		symbol.scope = currentScope;
		symbol.memory = mem;
		symbol.label = label;
		symbol.nParam = nParam;
        //inserta en la posicion hash el simbolo en la tabla
		table[getHash(name)].push_back(symbol);
		returnValue = &table[getHash(name)].back(); 
	}

    if (DEBUGGING) printState();
    return returnValue;
}

//aumenta el ambito
void symtable::newScope() {
    currentScope++;
}

//finaliza un ambito
void symtable::endScope() {

	list<symrec>::reverse_iterator s;
	for (int i=0; i < SYMTBLSIZE; i++){
		for (s = table[i].rbegin(); s != table[i].rend(); ++s) {
            //si el ambito de s es actual y no es cero
		   if ( s->scope == currentScope && s->scope != 0){
			table[i].pop_back();
			s--;
		    }
		}
	}
    //decrementamos ambito 
    currentScope--;
    if (DEBUGGING) printState();
}

//comprueba si el simbolo ya existe en la tabla
bool symtable::existSymbol(string name) {
    //obtenemos el hash
    int i = getHash(name);
    //si la posicion esta vacia --> No esta el simbolo
    if ( table[i].empty() )
        return false;
    //en el caso de que no este vacia 
    list<symrec>::reverse_iterator s;
    for (s = table[i].rbegin(); s != table[i].rend(); ++s) {
        //iteramos comprobando si el nombre coincide --> Esta el simbolo
        if (s->name == name)
            return true;
    }
    return false;
}

//Obtiene un simbolo 
symrec * symtable::getSymbol(string name) {
    //obtenemos el hash
    int i = getHash(name);

    symrec *returnValue = NULL;
    //si la posicion de la tabla no esta vacía --> el valor a devolver sera el de dicha posicion
    if(!table[i].empty()) returnValue = &table[i].back();
    return returnValue;
}

//obtiene el ambito de un simbolo
int symtable::scopeSymbol(string name) {
    int i = getHash(name);
    
    list<symrec>::reverse_iterator s;
    for (s = table[i].rbegin(); s != table[i].rend(); ++s) {
        //si el nombre del simbolo coincide devolvemos su ambito.
        if (s->name == name)
            return s->scope;
    }
    return -1;
}

//imprime tabla
void symtable::printState(){
	cout << endl;
	cout << "---------------------" << endl;
    cout << "---  State table  ---" << endl;
	cout << endl;
    list<symrec>::iterator s;
    
 
    for (int i=0; i<SYMTBLSIZE; ++i){
        for (s = table[i].begin(); s != table[i].end(); ++s){
            printSymbol(&(*s));
        }
    }

	cout << endl;    
    cout << "---  End table  ---" << endl;
	cout << "---------------------" << endl;
	cout << endl;
	letter = -1;
}

//imprime simbolo(variable o funcion )
void symtable::printSymbol(symrec * s){
    string nom_type[3];
    nom_type[_INT] = "INT";
    nom_type[_FLOAT] = "FLOAT"; 
    nom_type[_STR] = "STRING";
    
    if (s->scope == 0){letter++; }

    for (int e=0; e < s->scope; e++) 
		cout << "  ";
    cout << s->scope << " --> ";

	if (s->typesim == FUN){ 
		cout << s->name << "¡!";
		cout << endl;
		return;
	}

    if (s->typesim == VAR){
		cout << nom_type[s->typeVar] << " ";
		cout << s->name << ", MemPos = " << hex << s->memory <<" " << endl;
		return;
	}
	cout << endl;
   	
}

