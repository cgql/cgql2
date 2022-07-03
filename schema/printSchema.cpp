#include "cgql2/printer.h"
#include "cgql2/schema.h"

#include <iostream>

namespace cgql2 {

static void printDefinitionType(DefinitionType definitionType) {
  switch(definitionType) {
    case DefinitionType::kObject:
      std::cout << "OBJECT\n"; break;
    case DefinitionType::kScalar:
      std::cout << "SCALAR\n"; break;
    case DefinitionType::kUndefined:
      std::cout << "UNDEFINED\n"; break;
  }
}

static void printType(Ptr<Type>);

static void printObject(Ptr<ObjectTypeAttributes> object) {
  for(auto field : object->getFields()) {
    std::cout << "  " << field.getName() << " " <<
      field.getFieldType()->getName() << "\n";
  }
}

static void printType(Ptr<Type> type) {
  switch(type->getDefinitionType()) {
    case DefinitionType::kObject:
      printObject(type->getObject()); break;
    default: break;
  }
}

void printSchema(const cgql2::Schema& schema) {
  for(auto const& [typeName, type] : schema.getAllTypes()) {
    std::cout << typeName << " ";
    printDefinitionType(type->getDefinitionType());
    printType(type);
  }
}

}
