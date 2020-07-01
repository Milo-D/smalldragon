#ifndef SIMPLETYPE
#define SIMPLETYPE

#include <stdbool.h>

struct TokenList;

struct SimpleType {
	
	char* typeName;
};

struct SimpleType* makeSimpleType(struct TokenList* tokens, bool debug);
struct SimpleType* makeSimpleType(char* typeName);

#endif