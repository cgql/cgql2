#include "cgql2/query.h"

namespace cgql2 {

void Selection::setSelectionSet(Selections selectionSet) {
  this->selection = selectionSet;
}
const Selections& Selection::getSelectionSet() const {
  return this->selection;
}

}
