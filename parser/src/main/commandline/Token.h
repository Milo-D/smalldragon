#ifndef TOKEN
#define TOKEN

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

struct Token {

	/*
	 -- FIELDS --
	 - Kind 	(the kind of token, for example RPARENS)
	 - Value	(for example "subr" for an identifier)
	*/
	uint16_t kind;
	uint32_t lineNumber;

	//this is intentionally not a 'char*'
	//in an effort to make the program simple.
	char value[20];
};

bool tokenEquals(struct Token* a, struct Token* b);

struct Token* makeToken(int kind);
struct Token* makeToken2(int kind, char* value);

void freeToken(struct Token* token);

#endif
