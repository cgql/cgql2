#pragma once

#include <vector>
#include <string>

namespace cgql2 {

enum class DefinitionType {
  kUndefined,
  kObject,
  kScalar
};

class Type;

class Field final {
public:
  void setName(std::string name) { this->name = name; }
  const std::string& getName() const { return this->name; }
  void setFieldType(Type*);
  Type* getFieldType() const;
private:
  std::string name;
  Type* fieldType;
};

class ObjectTypeAttributes final {
public:
  void addField(Field);
  const std::vector<Field>& getFields() const;
private:
  std::vector<Field> fields;
};

class Type final {
public:
  Type(
    std::string name,
    DefinitionType requiredType = DefinitionType::kUndefined
  ) : name(name), requiredType(requiredType) {}
  const std::string& getName() const { return this->name; }
  void assign(const ObjectTypeAttributes&);
  ObjectTypeAttributes* getObject() const;
private:
  std::string name;
  DefinitionType definitionType = DefinitionType::kUndefined;
  DefinitionType requiredType = DefinitionType::kUndefined;

  union {
    ObjectTypeAttributes* object;
  } value = {};

private:
  void allocateForType(DefinitionType);
};

}
