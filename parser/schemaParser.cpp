#include "cgql2/parse.h"
#include "cgql2/ptr.h"
#include "cgql2/schema.h"

namespace cgql2 {

Field SchemaParser::parseField(Schema& schema) {
  Field field;
  field.setName(this->parseName());
  this->advanceIf(TokenType::COLON);
  field.setFieldType(schema.getType(this->parseName()));
  return field;
}

void SchemaParser::parseObjectType(Schema& schema) {
  this->lexer.advance();
  Type* objectType =
    schema.registerType(this->parseName(), DefinitionType::kObject);
  if(this->peek(TokenType::CURLY_BRACES_L)) {
    this->lexer.advance();
    do {
      objectType->getObject()->addField(this->parseField(schema));
    } while(!this->peek(TokenType::CURLY_BRACES_R));
    this->lexer.advance();
  }
}

void SchemaParser::parseDefinition(Schema& schema) {
  std::string lookAhead = this->lexer.lookAheadOfDescription();
  if(lookAhead == "type")
    this->parseObjectType(schema);
}

Schema SchemaParser::parseSchema() {
  Schema schema;
  this->advanceIf(TokenType::START);
  do {
    this->parseDefinition(schema);
  } while(!this->peek(TokenType::END));
  return schema;
}

}
