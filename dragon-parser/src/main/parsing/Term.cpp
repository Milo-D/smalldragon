#include <iostream>
#include <vector>
#include <string>

#include "../commandline/TokenList.hpp"
#include "../commandline/Token.hpp"
#include "../commandline/TokenKeys.hpp"
#include "Term.hpp"
#include "CharConst.hpp"
#include "IntConst.hpp"
#include "BoolConst.hpp"
#include "Expr.hpp"
#include "Variable.hpp"
#include "statements/MethodCall.hpp"

using namespace std;

Term::Term(Expr* expr){
	this->m5 = expr;
}

Term::Term(TokenList tokens, bool debug) {

	if(debug){
		cout << "Term(...)" << endl;
	}

	TokenList copy = TokenList(tokens);

	try {
		//TODO: re-insert later on
		//this->termNode = FloatConstNode(copy);
		throw "later";
	} catch (string e0) {
		try {
			this->m2 = new IntConst(copy,debug);
		} catch (string e1) {
			try {
				//a string constant is syntatic sugar.
				//in the parsing stage it is converted to an array of char constants
				//inline the stringConstant and its syntatic sugar
				Token token = tokens.get(0);
				//TODO: re-enable this later on
				/*
				if (token.kind == STRINGCONSTANT) {

					string content = token.getContents();
					TokenList tks = TokenList(vector(), tokens.relPath);
					tks.push_back(BaseToken(LBRACKET));
					for (int i = 0; i < content.size(); i++) {
						tks.push_back(BaseToken(CHARCONSTANT,content.at(i)));
						if (i < content.size() - 1) {
							tks.push_back(BaseToken(COMMA));
						}
					}
					tks.push_back(BaseToken(RBRACKET));
					this->termNode = ArrayConstantNode(tks);

					copy.consume(1);
				} else {
				*/
					throw "could not read stringConstant syntatic sugar";
				//}
			} catch (string e2) {
				try {
					TokenList copy2 = TokenList(copy);

					copy2.expect(Token(LPARENS));
					this->m5 = new Expr(copy2,debug);
					copy2.expect(Token(RPARENS));

					copy.set(copy2);
				} catch (string e3) {
					try {
						this->m4 = new MethodCall(copy,debug);
					} catch (string e4) {
						try {
							this->m1 = makeBoolConst(copy,debug);
						} catch (string e5) {
							try {
								this->m6 = new Variable(copy,debug);
							} catch (string e6) {
								//TODO: re-enable later
								/*
								try {
									this->termNode = ArrayConstantNode(copy);
								} catch (string e7) {
									*/
									this->m3 = new CharConst(copy,debug);
								//}
							}
						}
					}
				}
			}
		}
	}
	tokens.set(copy);
}
