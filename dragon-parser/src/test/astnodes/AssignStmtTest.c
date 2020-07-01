#include "AssignStmtTest.h"
#include "../../main/commandline/TokenList.h"
#include "../../main/commandline/TokenKeys.h"
#include "../../main/commandline/Token.h"
#include "../../main/parsing/statements/AssignStmt.h"
#include "../../main/parsing/Expr.h"
#include "../../main/parsing/Variable.h"

#include <stdio.h>
#include <stdbool.h>

int assignstmt_test1() {

	struct TokenList* tokens = makeTokenList();

	list_add(tokens, makeToken(ID,"x"));
	list_add(tokens, makeToken(OPKEY,"="));
	list_add(tokens, makeToken(INTEGER,"4"));
	list_add(tokens, SEMICOLON);

	struct AssignStmt* a = makeAssignStmt(tokens,false);

	return (a==NULL)?0:1;
}

int assignstmt_test_assign_method_call_result() {

	struct TokenList* tokens = makeTokenList();

	list_add(tokens, makeToken(ID,"x"));
	list_add(tokens, makeToken(OPKEY,"="));

	//nop refers to the no operation method. it does nothing with its argument
	list_add(tokens, makeToken(ID,"nop"));

	list_add(tokens, LPARENS);
	list_add(tokens, makeToken(INTEGER,"4"));
	list_add(tokens, RPARENS);

	list_add(tokens, SEMICOLON);

	struct AssignStmt* a = makeAssignStmt(tokens,false);
	return (a==NULL)?0:1;
		
}

int assignstmt_test_assign_method_call_result_2() {

	struct TokenList* tokens = makeTokenList();

	list_add(tokens, makeToken(ID,"x"));
	list_add(tokens, makeToken(OPKEY,"="));

	//nop refers to the no operation method. it does nothing with its argument
	list_add(tokens, makeToken(ID,"nop"));

	list_add(tokens, LPARENS);
	list_add(tokens, RPARENS);

	list_add(tokens, SEMICOLON);

	struct AssignStmt* a = makeAssignStmt(tokens,false);
	return (a==NULL)?0:1;
		
}

int assignstmt_test_assign_variable_with_array_index() {

	struct TokenList* tokens = makeTokenList();

	list_add(tokens, makeToken(ID,"x"));
	list_add(tokens, makeToken(OPKEY,"="));

	//nop refers to the no operation method. it does nothing with its argument
	list_add(tokens, makeToken(ID,"arr"));

	list_add(tokens, LBRACKET);
	list_add(tokens, makeToken(INTEGER,"4"));
	list_add(tokens, RBRACKET);

	list_add(tokens, SEMICOLON);

	struct AssignStmt* a = makeAssignStmt(tokens,false);
	return (a==NULL)?0:1;

}

int assignstmt_test_assign_char() {

	struct TokenList* tokens = makeTokenList();

	list_add(tokens, makeToken(ID,"x"));
	list_add(tokens, makeToken(OPKEY,"="));

	list_add(tokens, makeToken(CCONST,"x"));

	list_add(tokens, SEMICOLON);

	struct AssignStmt* a = makeAssignStmt(tokens,false);

	return (a==NULL)?0:1;

}

int assignstmt_test_can_assign_to_struct_member() {

	struct TokenList* tokens = makeTokenList();

	list_add(tokens, makeToken(ID,"x"));
	list_add(tokens, STRUCTMEMBERACCESS);
	list_add(tokens, makeToken(ID,"a"));
	list_add(tokens, makeToken(OPKEY,"="));
	list_add(tokens, makeToken(INTEGER,"3"));
	list_add(tokens, SEMICOLON);

	struct AssignStmt* a = makeAssignStmt(tokens,false);
	return (a==NULL)?0:1;

}

int assignstmt_test_type_declaration_for_variable() {

	struct TokenList* tokens = makeTokenList();
	list_add(tokens, makeToken(TYPEIDENTIFIER,"PInt"));
	list_add(tokens, makeToken(ID,"x"));
	list_add(tokens, makeToken(OPKEY,"="));
	list_add(tokens, makeToken(INTEGER,"3"));
	list_add(tokens, SEMICOLON);

	struct AssignStmt* a = makeAssignStmt(tokens,false);
	bool assert1 = (a->optTypeNode != NULL);
	bool assert2 = (0 == a->variableNode->count_memberAccessList);
	bool assert3 = (0 == tokens->size());

	return (assert1&&assert2&&assert3)?1:0;
}