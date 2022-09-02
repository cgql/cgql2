#include "cgql2/lexer.h"
#include "cgql2/parse.h"
#include "cgql2/query.h"

namespace cgql2 {

std::shared_ptr<FieldNode> DocumentParser::parseField() {
  std::shared_ptr<FieldNode> field =
    std::make_shared<FieldNode>();
  field->setName(this->parseName());
  if(this->peek(TokenType::CURLY_BRACES_L)) {
    Selections selectionSet = this->parseSelections();
    field->setSelectionSet(selectionSet);
  }
  return field;
}

std::shared_ptr<Selection> DocumentParser::parseSelection() {
  return this->parseField();
}

Selections DocumentParser::parseSelections() {
  this->advanceIf(TokenType::CURLY_BRACES_L);
  Selections selections;
  do {
    selections.push_back(this->parseSelection());
  } while(!this->peek(TokenType::CURLY_BRACES_R));
  this->lexer.advance();
  return selections;
}

Operation DocumentParser::parseOperation() {
  return {
    .selections = this->parseSelections(),
    .operationType = OperationType::kQuery
  };
}

Document DocumentParser::parseQuery() {
  Document document;
  this->advanceIf(TokenType::START);
  do {
    document.operations.push_back(this->parseOperation());
  } while(!this->peek(TokenType::END));
  return document;
}

}
