#ifndef BASETOKEN
#define BASETOKEN

//standard includes
#include <string>

//project includes

using namespace std;

class BaseToken {

	/*
	It should have fields for 
	Kind,	(the kind of token, for example RPARENS)
	Value	(for example "subr" for an identifier)
	*/

	public: 
		BaseToken(string kind);
		BaseToken(string kind, char value);
		BaseToken(char idk);
		BaseToken(bool value);
		BaseToken();
		long lineNumber;
		string kind;
		string value;

		string getContents(){

			return this->value;
		}
	
};
#endif