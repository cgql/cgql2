#pragma once

#include "cgql2/ptr.h"

#include <map>
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

class ScalarTypeAttributes final {
private:
};

class Type final {
public:
  Type(
    std::string name,
    DefinitionType requiredType = DefinitionType::kUndefined
  );
  ~Type();
  const std::string& getName() const { return this->name; }
  DefinitionType getDefinitionType() const { return this->definitionType; }
  void assign(const ObjectTypeAttributes&);
  void assign(const ScalarTypeAttributes&);

  ObjectTypeAttributes* getObject() const;
  const ScalarTypeAttributes& getScalar() const;
private:
  std::string name;
  DefinitionType definitionType = DefinitionType::kUndefined;

  union {
    ObjectTypeAttributes* object;
    ScalarTypeAttributes scalar;
  } value = {};

private:
  void allocateForType(DefinitionType);
};

class Schema {
public:
  Schema();
  Type* getType(std::string name);
  const auto& getAllTypes() const { return this->types; };
  Type* registerType(std::string, DefinitionType);
private:
  std::map<std::string, RAIIPtr<Type>> types;
};

}
