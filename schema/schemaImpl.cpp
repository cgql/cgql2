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

Type::Type(
  std::string name,
  DefinitionType requiredType
) : name(name) {
  this->allocateForType(requiredType);
}
Type::~Type() {
  switch(this->definitionType) {
    case DefinitionType::kObject:
      delete this->value.object;
      break;
    case DefinitionType::kScalar:
    case DefinitionType::kUndefined:
      break;
  }
}
void Type::assign(const ObjectTypeAttributes& object) {
  *this->value.object = object;
}
void Type::assign(const ScalarTypeAttributes& scalar) {
  this->value.scalar = scalar;
}
ObjectTypeAttributes* Type::getObject() const {
  return this->value.object;
}
const ScalarTypeAttributes& Type::getScalar() const {
  return this->value.scalar;
}
void Type::allocateForType(DefinitionType type) {
  if(definitionType != DefinitionType::kUndefined)
    return;
  switch(type) {
    case DefinitionType::kObject:
      this->value.object = new ObjectTypeAttributes;
      break;
    case DefinitionType::kScalar:
    case DefinitionType::kUndefined:
      break;
  }
  this->definitionType = type;
}

Schema::Schema() {
  this->registerType("Int", DefinitionType::kScalar);
}

Type* Schema::getType(std::string name) {
  return this->types[name].get();
}
Type* Schema::registerType(std::string name, DefinitionType defType) {
  Type* type = new Type(name, defType);
  this->types[name] = type;
  return type;
}

}
