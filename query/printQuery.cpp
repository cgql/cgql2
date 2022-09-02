#include "cgql2/printer.h"
#include "cgql2/query.h"

#include <iostream>

namespace cgql2 {

static void printOperationType(OperationType op) {
  switch(op) {
    case OperationType::kQuery:
      std::cout << "Operation - QUERY\n"; break;
    case OperationType::kMutation:
      std::cout << "Operation - MUTATION\n"; break;
    case OperationType::kSubscription:
      std::cout << "Operation - SUBSCRIPTION\n";   break;
  }
}

static void printSelectionType(SelectionType selectionType) {
  switch(selectionType) {
    case SelectionType::kField:
      std::cout << "FIELD\n"; break;
    case SelectionType::kFragment:
      std::cout << "FRAGMENT\n"; break;
    case SelectionType::kInlineFragment:
      std::cout << "INLINE FRAGMENT\n"; break;
  }
}

static int indent = 0;
static void printSelections(const Selections& selections);

static void printField(const std::shared_ptr<FieldNode>& field) {
  std::cout << field->getName() << " ";
  printSelectionType(field->getSelectionType());
  printSelections(field->getSelectionSet());
}

static void printSelections(const Selections& selections) {
  ++indent;
  for(const auto& selection : selections) {
    for(int i = 1; i <= indent; i++) std::cout << "  ";
    switch(selection->getSelectionType()) {
      case SelectionType::kField:
        printField(std::static_pointer_cast<FieldNode>(selection));
        break;
      default: break;
    }
  }
  --indent;
}

void printQuery(const Document& document) {
  for(const Operation& operation : document.operations) {
    printOperationType(operation.operationType);
    printSelections(operation.selections);
  }
}

}
