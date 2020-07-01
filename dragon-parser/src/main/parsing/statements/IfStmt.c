#include <stdio.h>
#include <stdlib.h>

#include "IfStmt.h"
#include "../../commandline/TokenKeys.h"
#include "../../commandline/TokenList.h"
#include "../../commandline/smalloc.h"
#include "../Expr.h"
#include "Stmt.h"

struct IfStmt* makeIfStmt(struct TokenList* tokens, bool debug) {

	if(debug){
		printf("IfStmt(...)\n"); 
	}

	struct IfStmt* res = smalloc(sizeof(struct IfStmt));
	
	res->condition = NULL;
	
	res->count_statements = 0;
	res->statements 	= smalloc(sizeof(struct Stmt*)*1);

	res->count_elseStatements = 0;
	res->elseStatements = smalloc(sizeof(struct Stmt*)*1);

	struct TokenList* copy = makeTokenList(tokens);

	if(list_size(copy) < 3){
		//"not enough tokens";
		return NULL;
	}

	if(!list_expect(copy, IF)){return NULL;}
	res->condition = makeExpr(copy,debug);
	if(res->condition == NULL){return NULL;}
	if(!list_expect(copy, LCURLY)){return NULL;}

	struct Token* next = list_get(copy, 0);
	if(next == NULL){return NULL;}
	
	while (next->kind != RCURLY) {

		res->statements[res->count_statements] = makeStmt(copy,debug);
		res->count_statements++;
		int newsize = sizeof(struct Stmt*) * res->count_statements+1;
		res->statements = realloc(res->statements,newsize);

		next = list_get(copy, 0);
		if(next == NULL){return NULL;}
	}

	if(!list_expect(copy, RCURLY)){return NULL;}

	//maybe there is an else
	if (list_startsWith(copy, ELSE)) {

		if(!list_expect(copy, ELSE)){return NULL;}

		if(!list_expect(copy, LCURLY)){return NULL;}

		//maybe there be some statements
		struct Token* elsenext = list_get(copy, 0);
		if(elsenext == NULL){return NULL;}

		while (elsenext->kind != RCURLY) {

			res->elseStatements[res->count_elseStatements] = makeStmt(copy,debug);
			res->count_elseStatements++;
			int newsize2 = sizeof(struct Stmt*) * res->count_elseStatements+1;
			res->elseStatements = realloc(res->elseStatements,newsize2);

			elsenext = list_get(copy, 0);
			if(elsenext == NULL){return NULL;}
		}

		if(!list_expect(copy, RCURLY)){return NULL;}
	}

	list_set(tokens, copy);

	return res;
}
