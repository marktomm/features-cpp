#include "lib.h"

namespace trivial_type {

void fn([[maybe_unused]] std::unique_ptr<int>) {}
void fn([[maybe_unused]] int*) {}

int testFunction(std::unique_ptr<int> x) { return *x; }

int testFunctionPtr(int* x) { return *x; }

} // namespace trivial_type