#include <cgql2/parse.h>
#include <cgql2/printer.h>
#include <cgql2/schema.h>

#include <iostream>
#include <chrono>

using namespace cgql2;

class Timer {
public:
  Timer(std::string name = "Time taken")
    : name(name) {
    start = std::chrono::steady_clock::now();
  }
  ~Timer() {
    end = std::chrono::steady_clock::now();
    printResult();
  }
private:
  std::chrono::steady_clock::time_point start;
  std::chrono::steady_clock::time_point end;
  std::string name;

private:
  void printResult() {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << name << ": " << duration.count() << "ms\n";
  }
};

int main() {
  {
    Timer t("50000");
    for(int i = 0; i < 50000; i++) {
      std::string s = "type Person { name: String } type Query { person: Person }";
      SchemaParser parser(s);
      Schema schema1 = parser.parseSchema();
    }
  }

  Schema schema;

  Type* stringType = schema.registerType("String", DefinitionType::kScalar);
  Type* queryType = schema.registerType("Query", DefinitionType::kObject);
  Type* personType = schema.registerType("Person", DefinitionType::kObject);

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
