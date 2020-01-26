
//standard headers
#include <vector>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>

//project headers
#include "StructMemberDeclNode.hpp"
#include "../../../lexing/TokenList.hpp"
#include "BasicTypeWrappedNode.hpp"
#include "IdentifierNode.hpp"

class StructMemberDeclNode {

public:
	BasicTypeWrappedNode typeNode;
	string name;

	StructMemberDeclNode(TokenList tokens, bool debug) {
		if (debug) {
			System.out.println("try to parse " + this.getClass().getSimpleName() + " from '" + tokens.toSourceCodeFragment() + "'");
		}

		TokenList copy = tokens.copy();

		this.typeNode = new BasicTypeWrappedNode(copy);
		this.name = new IdentifierNode(copy).identifier;

		tokens.set(copy);
	}

};