#pragma once

#include "cgql2/lexer.h"
#include "cgql2/query.h"
#include "cgql2/schema.h"

#include <string>

namespace cgql2 {

class BaseParser {
public:
  BaseParser(const std::string&);
protected:
  Lexer lexer;

  Token advanceIf(TokenType);
  bool peek(TokenType);
  std::string parseName();
};

class SchemaParser : public BaseParser {
public:
  using BaseParser::BaseParser;

  Schema parseSchema();
private:
  void parseDefinition(Schema&);
  void parseObjectType(Schema&);
  Field parseField(Schema&);
};

class DocumentParser : public BaseParser {
public:
  using BaseParser::BaseParser;

  Document parseQuery();
private:
  std::shared_ptr<FieldNode> parseField();
  std::shared_ptr<Selection> parseSelection();
  Selections parseSelections();
  Operation parseOperation();
};

}
