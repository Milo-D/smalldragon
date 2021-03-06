#ifndef DECLARG
#define DECLARG

#include <stdbool.h>

#include "../../../../ast/ast.h"

struct DeclArg* makeDeclArg(struct TokenList* tokens, bool debug);

void freeDeclArg(struct DeclArg* da);

#endif
