#include <iostream>
#include <vector>
#include <set>
#include <optional>
#include <string>
#include <sstream>

//project headers
#include "SimpleVariableNode.hpp"
#include "../commandline/TokenKeys.hpp"
#include "ExpressionNode.hpp"

using namespace std;

SimpleVariableNode::SimpleVariableNode(TokenList tokens, bool debug) {

	if(debug){
		cout << "WhileStatementNode(...)" << endl;
	}

	TokenList copy = TokenList(tokens);

	Token token = copy.get(0);

	if (token.kind == IDENTIFIER) {
		this->name = token.value;
		copy.consume(1);

		//it could have an index
		if (copy.size() > 0 && copy.get(0).kind == LBRACKET) {
			copy.expectAndConsumeOtherWiseThrowException(Token(LBRACKET));
			this->indexOptional = optional(new ExpressionNode(copy,debug));
			copy.expectAndConsumeOtherWiseThrowException(Token(RBRACKET));
		} else {
			this->indexOptional = nullopt;
			//pass, this assignment has no index to it
		}

	} else {
		stringstream msg;
		msg << tokens.relPath 
		<< string(":") 
		<< token.lineNumber
		<< ": could not read variable name. token was " 
		<< token.value
		<< " from context  '" 
		<< tokens.toSourceCodeFragment().substr(0, min(20, (int)tokens.toSourceCodeFragment().size())) 
		<< "'";

		throw msg.str();
	}

	tokens.set(copy);
}

