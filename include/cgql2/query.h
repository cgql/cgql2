#pragma once

#include <string>
#include <vector>
#include <memory>

namespace cgql2 {

enum class SelectionType {
  kField,
  kInlineFragment,
  kFragment
};

enum class OperationType {
  kQuery,
  kMutation,
  kSubscription
};

class Selection;
using Selections = std::vector<std::shared_ptr<Selection>>;

class Selection {
public:
  void setSelectionSet(Selections);
  const Selections& getSelectionSet() const;
  SelectionType getSelectionType() const { return this->selectionType; }
protected:
  Selections selection;
  SelectionType selectionType;
};

class FieldNode : public Selection {
public:
  FieldNode() { this->selectionType = SelectionType::kField; }
  void setName(std::string name) { this->name = name; }
  const std::string& getName() const { return this->name; }
private:
  std::string name;
};

struct Operation {
  Selections selections;
  OperationType operationType;
};

struct Document {
  std::vector<Operation> operations;
};

}
