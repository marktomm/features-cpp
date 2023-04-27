#ifndef MACRO_trivial_type_LIB_H
#define MACRO_trivial_type_LIB_H

#include <cstdint>
#include <memory>

namespace trivial_type {

void fn(std::unique_ptr<int>);
void fn(int*);

int testFunction(std::unique_ptr<int> x);
int testFunctionPtr(int* x);

}; // namespace trivial_type

#endif
