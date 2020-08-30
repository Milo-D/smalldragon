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
	
	//max 32 chars for a local variable identifier
	char name[32]; 
	
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

//to add a row to the local variable symbol table
//the lvst works as a set regarding the 'name' of the local variable
void lvst_add(struct LVST* lvst, struct LVSTLine* line);

//obtain a reference to the line for that identifier
struct LVSTLine* lvst_get(struct LVST* lvst, char* name);

#endif
