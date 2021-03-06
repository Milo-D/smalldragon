#ifndef ASTWRITER
#define ASTWRITER


#include "ast.h"

#include <stdlib.h>
#include <stdio.h>

void write_ast(char* filename, struct Namespace* namespaceNode);

// --- high level structures ---------

void writeNamespace(struct Namespace* m, 	FILE* file);

void writeMethod(struct Method* m, 		FILE* file);

void writeStructDecl(struct StructDecl* m, FILE* file);
void writeStructMember(struct StructMember* m, FILE* file);

void writeStmtBlock(struct StmtBlock* block, FILE* file);

// -----------------------------------

void writeDeclArg(struct DeclArg* m, 		FILE* file);
void writeExpr(struct Expr* m, 			FILE* file);
void writeOp(struct Op* m, 			FILE* file);

void writeIntConst(struct IntConst* m, 		 FILE* file);
void writeBoolConst(struct BoolConst* m, 	 FILE* file);
void writeCharConst(struct CharConst* m, 	 FILE* file);
void writeFloatConst(struct FloatConst* m, 	 FILE* file);
void writeStringConst(struct StringConst* m, FILE* file);

void writeVariable(struct Variable* m, 		FILE* file);
void writeSimpleVar(struct SimpleVar* m, 	FILE* file);
void writeTerm(struct Term* m, 				FILE* file);
void writeUnOpTerm(struct UnOpTerm* t,  	FILE* file);

//statementnodes
void writeStmt(struct Stmt* m, 			FILE* file);
void writeIfStmt(struct IfStmt* m, 		FILE* file);
void writeWhileStmt(struct WhileStmt* m, 	FILE* file);
void writeRetStmt(struct RetStmt* m, 		FILE* file);
void writeAssignStmt(struct AssignStmt* m, 	FILE* file);
void writeMethodCall(struct MethodCall* m, 	FILE* file);
void writeLoopStmt(struct LoopStmt* m, 		FILE* file);
void writeBreakStmt(struct BreakStmt* m, 	FILE* file);

//typenodes
void writeType(struct Type* m, 				FILE* file);
void writeSubrType(struct SubrType* m, 			FILE* file);
void writeSimpleType(struct SimpleType* m, 		FILE* file);
void writeArrayType(struct ArrayType* m, 		FILE* file);
void writeTypeParam(struct TypeParam* m, 		FILE* file);
void writeBasicTypeWrapped(struct BasicTypeWrapped* m, 	FILE* file);

#endif
