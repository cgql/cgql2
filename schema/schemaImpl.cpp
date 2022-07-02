#include "cgql2/schema.h"

namespace cgql2 {

void Field::setFieldType(Type* fieldType) {
  this->fieldType = fieldType;
}
Type* Field::getFieldType() const {
  return this->fieldType;
}

void ObjectTypeAttributes::addField(Field field) {
  this->fields.push_back(field);
}
const std::vector<Field>& ObjectTypeAttributes::getFields() const {
  return this->fields;
}

void Type::assign(const ObjectTypeAttributes& object) {
  this->allocateForType(DefinitionType::kObject);
  *this->value.object = object;
}
ObjectTypeAttributes* Type::getObject() const {
  return this->value.object;
}
void Type::allocateForType(DefinitionType type) {
  switch(type) {
    case DefinitionType::kObject:
      this->value.object = new ObjectTypeAttributes;
      break;
    case DefinitionType::kUndefined:
      break;
  }
  this->definitionType = type;
}

}
