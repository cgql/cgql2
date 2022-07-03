#include "cgql2/schema.h"

namespace cgql2 {

void Field::setFieldType(Ptr<Type> fieldType) {
  this->fieldType = fieldType;
}
Ptr<Type> Field::getFieldType() const {
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
      this->value.object.destroy();
      break;
    case DefinitionType::kScalar:
    case DefinitionType::kUndefined:
      break;
  }
}
void Type::assign(const ObjectTypeAttributes& object) {
  this->value.object.assign(object);
}
void Type::assign(const ScalarTypeAttributes& scalar) {
  this->value.scalar = scalar;
}
Ptr<ObjectTypeAttributes> Type::getObject() const {
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

Ptr<Type> Schema::getType(std::string name) const {
  auto it = this->types.find(name);
  return it->second.get();
}
void Schema::addType(Ptr<Type> type) {
  this->types.try_emplace(type->getName(), type);
}

}
