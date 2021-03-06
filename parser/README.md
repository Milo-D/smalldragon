<img src="https://raw.githubusercontent.com/pointbazaar/smalldragon/master/dragon-lexer/img/dragon-logo.svg" width="100" height="100"/>

# Dragon-Parser

This is the parser for [smalldragon](https://github.com/pointbazaar/smalldragon), 
a simple, statically typed, compiled programming language.

You can use it to build your own
compiler/interpreter/typechecker/static analyzer/... 
for that language.

## Grammar that it recognizes

```
ArrayConstant ::= '[' expression (',' expression)* ']'

AST ::= namespace+

//the name of the namespace is the filename.
namespace ::=  structDecl* method*

structDecl ::= 'struct' SimpleType '{' structMemberDecl (',' structMemberDecl)* '}'

structMemberDecl ::= Type identifier

SubroutineType ::= '(' Type* ')' arrow Type
SimpleType ::= upperCaseLetter alphanumeric* | anyTypeToken
BasicTypeWrapped ::= SimpleType | '(' SubroutineType ')'

TypeParameter ::= '?T' ( 0 | 1 | ... )

ArrayType :: = '[' Type ']'

Type ::= BasicTypeWrapped | TypeParameter | ArrayType

simplevariable ::= identifier ('[' expression ']')?
variable ::= simplevariable ('.' variable)*

stmtblock ::= '{' statement* '}'

method ::= 'fn' identifier '(' declaredArgument* ')' arrow Type stmtblock

declaredArgument ::= Type identifier? 

//the optional identifier is there to support for example the 
//" (?T0,PInt size)~>[?T0] newarray{...} " builtin subroutine.
//in that case we receive just the type as a parameter, not an instance of it.

statement ::=   ( methodCall ';' )
                | whileStatement 
                | ifStatement 
                | returnStatement 
                | assignmentStatement
		| loopStatement
		| breakStatement

methodCall ::= identifier '(' (expression (, expression)*)?  ')'

breakStatement ::= 'break' ';'

loopStatement ::= 'loop' expression stmtblock

whileStatement ::= 'while' expression stmtblock

ifStatement ::= 'if' expression stmtblock
				( 'else' stmtblock )?
				
returnStatement ::= 'return' expression? ';'

assignmentStatement ::= Type? variable '=' expression ';'

UnOpTerm ::= op Term //op must be a unary operator like '!', '~'

Term ::= ArrayConstant 
		| boolConstant 
		| integerConstant 
		| charConstant 
		| methodCall 
		| '(' expression ')' 
		| variable

expression ::= UnOpTerm (op UnOpTerm)*

```

## Simplifications performed
- it transforms a string constant into an array

```
expression ::= UnOpTerm (op UnOpTerm)*

//is transformed into:

expression ::= UnOpTerm (op UnOpTerm)+

//with operator precedence recognized
```


