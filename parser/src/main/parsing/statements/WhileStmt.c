#include <stdio.h>
#include <stdlib.h>

#include "../StmtBlock.h"
#include "WhileStmt.h"
#include "../../commandline/TokenList.h"
#include "../../commandline/TokenKeys.h"
#include "../../commandline/Token.h"
#include "../Expr.h"
#include "Stmt.h"
#include "../../../../../util/util.h"

struct WhileStmt* makeWhileStmt(struct TokenList* tokens, bool debug){

	if(debug){
		printf("WhileStmt(...)\n");
	}

	struct WhileStmt* res = smalloc(sizeof(struct WhileStmt));

	res->condition = NULL;
	res->block     = NULL;

	struct TokenList* copy = list_copy(tokens);

	if(!list_expect(copy, WHILE)){
		//this part can be parsed deterministically
		printf("expected 'while', but was: %s\n", list_code(copy, debug));
		exit(1);
		return NULL;
	}

	res->condition = makeExpr(copy,debug);
	if(res->condition == NULL){
		free(res);
		return NULL;
	}

	res->block = makeStmtBlock(copy, debug);
	if(res->block == NULL){
		freeExpr(res->condition);
		free(res);
		return NULL;
	}
	
	if(debug){
		printf("sucess parsing WhileStmt\n");
	}

	list_set(tokens, copy);
	freeTokenListShallow(copy);

	return res;
}

void freeWhileStmt(struct WhileStmt* ws){
	freeExpr(ws->condition);
	freeStmtBlock(ws->block);
	free(ws);
}
