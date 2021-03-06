#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "FloatConst.h"
#include "../commandline/TokenList.h"
#include "../commandline/TokenKeys.h"
#include "../commandline/Token.h"
#include "../../../../util/util.h"

struct FloatConst* makeFloatConst(struct TokenList* tokens, bool debug){

	if(debug){
		printf("FloatConst(...)\n");
	}

	if(list_size(tokens) == 0){ return NULL; }

	struct FloatConst* res = smalloc(sizeof(struct FloatConst));

	struct TokenList* copy = list_copy(tokens);

	struct Token* tk = list_head(copy);

	res->value = 1.0;
	
	if(tk->kind == OPKEY && strcmp(tk->value, "-") == 0){
		
		res->value = -1.0;
		
		list_consume(copy, 1);

		if(debug){ printf("parsed sign\n"); }
	}

	if(list_size(copy) == 0){
		freeFloatConst(res);
		freeTokenListShallow(copy);
		return NULL;
	}

	if(list_head(copy)->kind != FLOATING){
		freeFloatConst(res);
		freeTokenListShallow(copy);
		return NULL;
	}

	res->value *= atof(list_head(copy)->value);
	list_consume(copy, 1);


	list_set(tokens, copy);
	freeTokenListShallow(copy);

	return res;
}

void freeFloatConst(struct FloatConst* fc){
	free(fc);
}
