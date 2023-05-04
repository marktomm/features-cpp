#include "lib.h"

namespace trivial_type {

void FnNoop([[maybe_unused]] std::unique_ptr<int>) {}
void FnNoop([[maybe_unused]] int*) {}

int TestFunction(std::unique_ptr<int> x) { return *x; }

int TestFunction(int* x) { return *x; }

static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }

void FnEscape([[maybe_unused]] std::unique_ptr<int> p) { escape(p.get()); }
void FnEscape([[maybe_unused]] int* p) { escape(p); }

} // namespace trivial_type