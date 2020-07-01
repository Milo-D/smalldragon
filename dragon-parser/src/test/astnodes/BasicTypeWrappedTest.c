#include "BasicTypeWrappedTest.h"

#include "../../main/commandline/TokenList.h"
#include "../../main/commandline/TokenKeys.h"
#include "../../main/commandline/Token.h"


#include "../../main/parsing/typenodes/BasicTypeWrapped.h"

int basictypewrapped_test_type_parsing_simple_type() {

	struct TokenList* list = makeTokenList();
	list_add(list, makeToken(TYPEIDENTIFIER,"PInt"));

	struct BasicTypeWrapped* b = makeBasicTypeWrapped(list,false);

	bool assert1 = (b->m1 != NULL && b->m2 == NULL);	//it is SimpleType
	bool assert2 = (0 == list->size());

	return (assert1&&assert2)?1:0;
}