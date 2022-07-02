#include <cgql2/schema.h>

#include <iostream>

using namespace cgql2;

int main() {
  Type stringType("String", DefinitionType::kScalar);
  Type queryType("Query", DefinitionType::kObject);
  ObjectTypeAttributes object;

  Field nameField;
  nameField.setName("name");
  nameField.setFieldType(nullptr);

  object.addField(nameField);

  queryType.assign(object);

  std::cout << "Field name: " << nameField.getName() << "\n";
  std::cout << "Object name: " << queryType.getName() << "\n";

  return 0;
}
