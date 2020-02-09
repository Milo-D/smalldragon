#ifndef TOKENREADER
#define TOKENREADER

#include <string>
#include <stdio.h>
#include <optional>
#include "Token.hpp"
#include "TokenList.hpp"
#include "TokenKeys.hpp"

optional<Token> recognizeToken(string tkn, bool debug);

#endif