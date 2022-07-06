#include <cgql2/parse.h>
#include <cgql2/printer.h>
#include <cgql2/schema.h>

#include <iostream>

using namespace cgql2;

int main() {
  std::string s = "type Query { person: Person }";
  SchemaParser parser(s);
  Schema schema1 = parser.parseSchema();
  printSchema(schema1);

  Schema schema;

  Ptr<Type> stringType = makePtr<Type>("String", DefinitionType::kScalar);
  schema.addType(stringType);

  Ptr<Type> queryType = makePtr<Type>("Query", DefinitionType::kObject);
  schema.addType(queryType);

  Ptr<Type> personType = makePtr<Type>("Person", DefinitionType::kObject);
  schema.addType(personType);

  ObjectTypeAttributes queryObject;

  Field personField;
  personField.setName("person");
  personField.setFieldType(schema.getType("Person"));

  queryObject.addField(personField);

  queryType->assign(queryObject);

  ObjectTypeAttributes personObject;

  Field nameField;
  nameField.setName("name");
  nameField.setFieldType(schema.getType("String"));

  Field relationField;
  relationField.setName("relation");
  relationField.setFieldType(schema.getType("Person"));

  personObject.addField(nameField);
  personObject.addField(relationField);

  personType->assign(personObject);

  printSchema(schema);

  return 0;
}
