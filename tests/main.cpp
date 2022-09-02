#include "cgql2/query.h"
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
    std::string s = "type Query { number: Int }";
    SchemaParser parser(s);
    Schema schema1 = parser.parseSchema();
    printSchema(schema1);
  }

  {
    std::string q = "{ person { name age } }";
    DocumentParser parser(q);
    Document doc = parser.parseQuery();
    printQuery(doc);
  }

  return 0;
}
