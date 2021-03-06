#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "BoolConst.h"
#include "../commandline/TokenList.h"
#include "../commandline/TokenKeys.h"
#include "../../../../util/util.h"

struct BoolConst* makeBoolConst(struct TokenList* tokens, bool debug) {

	if(debug){
		printf("makeBoolConst(...) from: ");
		list_print(tokens);
	}

	if(list_size(tokens) == 0){
		return NULL;
	}

	//struct TokenList* copy = list_copy(tokens);
	
	struct BoolConst* res = smalloc(sizeof(struct BoolConst));
	
	struct Token* tk = list_head(tokens);
	
	if (tk->kind == BCONST) {
		
		if(strcmp(tk->value,"true") == 0) {
			res->value = true;
		}else if(strcmp(tk->value,"false") == 0){
			res->value = false;
		}else{
			printf("tk->value was not satisfactory.\n");
			printf("boolconst parsing fatal error\n");
			free(res);
			exit(1);
		}
		list_consume(tokens, 1);
	} else {
		if(debug){
			printf("token was not the right kind.\n");
		}
		free(res);
		return NULL;
	}

	return res;
}

void freeBoolConst(struct BoolConst* bc){
	free(bc);
}
