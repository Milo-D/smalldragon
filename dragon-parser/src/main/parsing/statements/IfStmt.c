#include <stdio.h>
#include <stdlib.h>

#include "IfStmt.h"
#include "../../commandline/TokenKeys.h"
#include "../../commandline/TokenList.h"
#include "../Expr.h"
#include "Stmt.h"
#include "../../../../../util/util.h"

struct IfStmt* makeIfStmt(struct TokenList* tokens, bool debug) {

	if(debug){
		printf("IfStmt(...) from: ");
		list_print(tokens);
	}
	
	if(list_size(tokens) < 3){ return NULL; }

	struct IfStmt* res = smalloc(sizeof(struct IfStmt));
	
	res->condition = NULL;
	
	res->count_statements = 0;
	res->statements 	= smalloc(sizeof(struct Stmt*)*1);

	res->count_elseStatements = 0;
	res->elseStatements = smalloc(sizeof(struct Stmt*)*1);

	struct TokenList* copy = list_copy(tokens);

	if(!list_expect(copy, IF)){
		free(res->statements);
		free(res->elseStatements);
		free(res);
		return NULL;
	}

	res->condition = makeExpr(copy,debug);
	if(res->condition == NULL){
		free(res->statements);
		free(res->elseStatements);
		free(res);
		return NULL;
	}

	if(!list_expect(copy, LCURLY)){
		freeExpr(res->condition);
		free(res->statements);
		free(res->elseStatements);
		free(res);
		return NULL;
	}

	struct Token* next = list_head(copy);
	if(next == NULL){
		freeExpr(res->condition);
		free(res->statements);
		free(res->elseStatements);
		free(res);
		return NULL;
	}
	
	while (next->kind != RCURLY) {

		struct Stmt* stmt = makeStmt(copy, debug);
		if(stmt == NULL){
			freeExpr(res->condition);
			free(res->statements);
			free(res->elseStatements);
			free(res);
			return NULL;
		}

		res->statements[res->count_statements] = stmt;
		res->count_statements++;

		const int newsize = sizeof(struct Stmt*) * (res->count_statements+1);
		res->statements = realloc(res->statements,newsize);

		next = list_head(copy);
		if(next == NULL){
			freeExpr(res->condition);
			free(res->statements);
			free(res->elseStatements);
			free(res);
			return NULL;
		}
	}

	if(!list_expect(copy, RCURLY)){
		freeExpr(res->condition);
		free(res->statements);
		free(res->elseStatements);
		free(res);
		return NULL;
	}

	//maybe there is an else
	if (list_startsWith(copy, makeToken(ELSE))) {
		list_consume(copy, 1);

		if(!list_expect(copy, LCURLY)){
			freeExpr(res->condition);
			free(res->statements);
			free(res->elseStatements);
			free(res);
			return NULL;
		}

		struct Token* elsenext = list_head(copy);
		if(elsenext == NULL){
			free(res);
			return NULL;
		}

		while (elsenext->kind != RCURLY) {

			struct Stmt* stmt = makeStmt(copy, debug);
			if(stmt == NULL){
				freeExpr(res->condition);
				free(res->statements);
				free(res->elseStatements);
				free(res);
				return NULL;
			}

			res->elseStatements[res->count_elseStatements] = stmt;

			res->count_elseStatements++;
			const int newsize2 = sizeof(struct Stmt*) * res->count_elseStatements+1;
			res->elseStatements = realloc(res->elseStatements,newsize2);

			elsenext = list_head(copy);
			if(elsenext == NULL){
				freeExpr(res->condition);
				free(res->statements);
				free(res->elseStatements);
				free(res);
				return NULL;
			}
		}

		if(!list_expect(copy, RCURLY)){
			free(res);
			return NULL;
		}
	}
	
	if(debug){
		printf("sucess parsing IfStmt\n");
	}

	list_set(tokens, copy);
	freeTokenListShallow(copy);

	return res;
}

void freeIfStmt(struct IfStmt* is){
	
	freeExpr(is->condition);
	
	for(int i=0;i < is->count_statements; i++){
		freeStmt(is->statements[i]);
	}
	free(is->statements);
	
	for(int i=0;i < is->count_elseStatements; i++){
		freeStmt(is->elseStatements[i]);
	}
	free(is->elseStatements);
	
	free(is);
}

