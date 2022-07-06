#include "cgql2/parse.h"

namespace cgql2 {

BaseParser::BaseParser(const std::string& source)
  : lexer(source) {
}

Token BaseParser::advanceIf(TokenType tokenType) {
  if(this->lexer.currentToken.type != tokenType) {
    // error
  }
  Token token = this->lexer.currentToken;
  this->lexer.advance();
  return token;
}

std::string BaseParser::parseName() {
  return this->advanceIf(TokenType::NAME).value;
}

bool BaseParser::peek(TokenType tokenType) {
  return this->lexer.currentToken.type == tokenType;
}

}
