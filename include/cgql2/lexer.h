#pragma once

#include <string>
#include <iostream>

namespace cgql2 {

enum class TokenType {
  NAME,

  CURLY_BRACES_L,
  CURLY_BRACES_R,
  COLON,

  START,
  END
};

struct Token {
  std::string value;
  TokenType type;
};

class Lexer {
public:
  Lexer(const std::string&);

  Token next();
  void advance();
  std::string lookAheadOfDescription();

  Token currentToken;
private:
  std::string lexName();
private:
  const char* current;
  const char* bufferEnd;
};

}

namespace std {

inline ostream& operator<<(ostream& os, cgql2::TokenType type) {
  switch(type) {
    case cgql2::TokenType::NAME:
      os << "NAME"; break;
    case cgql2::TokenType::CURLY_BRACES_L:
      os << "CURLY_BRACES_L"; break;
    case cgql2::TokenType::CURLY_BRACES_R:
      os << "CURLY_BRACES_R"; break;
    case cgql2::TokenType::COLON:
      os << "COLON"; break;
    case cgql2::TokenType::START:
      os << "START_OF_QUERY"; break;
    case cgql2::TokenType::END:
      os << "END_OF_QUERY"; break;
  }
  return os;
}

}

