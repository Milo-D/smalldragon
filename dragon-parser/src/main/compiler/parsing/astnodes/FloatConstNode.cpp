
//standard headers
#include <vector>
#include <set>

//project headers
#include "FloatConstNode.hpp"

class FloatConstNode : ITermNode {

public:
	//this can also have a negative value if it is preceded by a '-' operator token
	float floatValue;

	FloatConstNode(TokenList tokens) {

		TokenList copy = new TokenList(tokens);

		if (copy.get(0) instanceof OperatorToken) {
			OperatorToken tk = (OperatorToken) copy.get(0);
			if (tk.operator.equals("-") && (copy.get(1) instanceof FloatNonNegativeConstantToken)) {
				this.floatValue = -(((FloatNonNegativeConstantToken) copy.get(1)).value);
				copy.consume(2);
			} else {
				throw new Exception("cannot parse float constant node with such operator:" + tk.operator);
			}
		} else if (copy.get(0) instanceof FloatNonNegativeConstantToken) {
			this.floatValue = ((FloatNonNegativeConstantToken) copy.get(0)).value;
			copy.consume(1);
		} else {
			throw new Exception("could not read float constant node");
		}

		tokens.set(copy);
	}

};