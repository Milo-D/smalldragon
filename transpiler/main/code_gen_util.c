#include <stdio.h>

#include "ctx.h"

void indent(struct Ctx* ctx){
	
	for(int i=0;i < ctx->indentLevel; i++){
		fprintf(ctx->file, "\t");
	}
}
