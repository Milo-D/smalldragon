#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "StringConst.h"
#include "../commandline/TokenList.h"
#include "../commandline/Token.h"
#include "../commandline/TokenKeys.h"
#include "../../../../util/util.h"

struct StringConst* makeStringConst(struct TokenList* tokens, bool debug){
	
	if(debug){
		printf("StringConst(...) from ");
		list_print(tokens);
	}
	
	if(list_size(tokens) == 0){return NULL;}
	
	struct StringConst* res = smalloc(sizeof(struct StringConst));
	
	struct Token* head = list_head(tokens);
	
	if(head->kind == STRINGCONST){
		strncpy(res->value, head->value, 99);
		list_consume(tokens, 1);
	}else{
		freeStringConst(res);
		return NULL;
	}
	
	return res;
}

void freeStringConst(struct StringConst* s){
	free(s);
}
