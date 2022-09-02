#pragma once

#include "cgql2/query.h"
#include "cgql2/schema.h"

namespace cgql2 {

void printSchema(const Schema&);
void printQuery(const Document&);

}
