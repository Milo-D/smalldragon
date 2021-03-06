#ifndef INTCONST
#define INTCONST

#include <stdbool.h>

#include "../../../../ast/ast.h"

struct IntConst* makeIntConst(struct TokenList* tokens, bool debug);

void freeIntConst(struct IntConst* ic);

#endif
