#include "NamespaceTest.h"
#include "../../main/commandline/TokenList.h"
#include "../../main/commandline/TokenKeys.h"
#include "../../main/commandline/Token.h"
#include "../../main/parsing/Namespace.h"
#include "../../main/parsing/StructDecl.h"

#include <stdbool.h>

int namespace_test_can_parse_namespace_with_1_empty_struct() {

	struct TokenList* l = makeTokenList();

	list_add(l, makeToken(STRUCT));
	list_add(l, makeToken2(TYPEIDENTIFIER,"MyStruct"));
	list_add(l, makeToken(LCURLY));
	list_add(l, makeToken(RCURLY));

	struct Namespace* n = makeNamespace(&l,"Main", false);

	bool assert1 = (1 == n->count_structs);
	bool assert2 = (0 == n->structs[0]->count_members);

	return (assert1&&assert2)?1:0;
}

int namespace_test_can_parse_namespace_with_1_empty_method() {

	//TODO:
	//these parser tests are problematic, because they don't just test the parser,
	//they also test the lexer.
	//i should write the tests so that the parser alone can accomplic shem

	struct TokenList* l = makeTokenList();

	list_add(l, makeToken(FN));
	list_add(l, makeToken2(ID,"main"));
	list_add(l, makeToken(LPARENS));
	list_add(l, makeToken2(TYPEIDENTIFIER,"String"));
	list_add(l, makeToken2(ID,"hello"));
	list_add(l, makeToken(RPARENS));
	list_add(l, makeToken(ARROW));
	list_add(l, makeToken2(TYPEIDENTIFIER,"PInt"));
	list_add(l, makeToken(LCURLY));

	list_add(l, makeToken(RCURLY));

	struct Namespace* n = makeNamespace(&l,"Main", false);

	bool assert1 = string("Main").compare(n->name) == 0;
	bool assert2 = (1 == n->count_methods);

	return (assert1&&assert2)?1:0;
}
