#include "cgql2/lexer.h"

#include <iostream>

namespace cgql2 {

Token genToken(TokenType type, std::string value = "") {
  return Token {
    .value = value,
    .type = type
  };
}

bool isLetter(char character) {
  return (character >= 'A' && character <= 'Z') ||
         (character >= 'a' && character <= 'z');
}

bool isDigit(char character) {
  return character >= '0' && character <= '9';
}

bool isNameStart(char character) {
  return isLetter(character) || character == '_';
}

bool isNameContinue(char character) {
  return isLetter(character) || isDigit(character) || character == '_';
}

Lexer::Lexer(const std::string& source)
  : current(source.data()),
    bufferEnd(source.data() + source.size()),
    currentToken(genToken(TokenType::START)) {
}

std::string Lexer::lookAheadOfDescription() {
  // to be implemented
  return this->currentToken.value;
}

Token Lexer::next() {
  for(;current < bufferEnd; ++current) {
    if(isNameStart(*current)) {
      return genToken(TokenType::NAME, this->lexName());
    }
    switch(*current) {
      case ' ':
      case '\n':
      case '\t':
      case ',':
        continue;
      case '{': ++current; return genToken(TokenType::CURLY_BRACES_L);
      case '}': ++current; return genToken(TokenType::CURLY_BRACES_R);
      case ':': ++current; return genToken(TokenType::COLON);
    }
  }
  return genToken(TokenType::END);
}

void Lexer::advance() {
  this->currentToken = this->next();
}

std::string Lexer::lexName() {
  const char* end = this->current;
  while(end < bufferEnd) {
    if(!isNameContinue(*end)) break;
    ++end;
  }
  std::string value(this->current, end - this->current);
  this->current = end;
  return value;
}

}
