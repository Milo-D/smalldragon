#ifndef LOCALVARSYMTABLE
#define LOCALVARSYMTABLE

#include "../../../ast/ast.h"

struct LVSTLine;

struct LVST {
	//Local Variable Symbol Table (LVST)
	//local variable symbol table
	
	unsigned int count;
	size_t capacity;
	
	struct LVSTLine** lines;
};

struct LVSTLine {
	//a line in the 'local variable symbol table'
	//name, type, struct AssignStmt* firstOccur
	
	//local variable identifier
	char name[DEFAULT_STR_SIZE]; 
	
	//a reference to the type of the variable
	struct Type* type; 
	
	//the first occurence
	//in the subroutine
	//where this local variable was 
	//assigned.
	//can be NULL and is not relevant if isArg == true
	struct AssignStmt* firstOccur;
	
	
	//TODO: we must differentiate if 
	//it is an argument to the function
	//or not.
	//because arguments already have a type declared
	//(for the c code generation)
	
	
	//is it an argument
	bool isArg;
};

void freeLVSTLine(struct LVSTLine* l);

struct LVST* makeLocalVarSymTable(struct Method* subr, bool debug);


//obtain a reference to the line for that identifier
struct LVSTLine* lvst_get(struct LVST* lvst, char* name);

#endif
