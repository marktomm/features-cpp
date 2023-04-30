#include "lib.h"

using namespace lambda_fns;
using namespace std;

#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

// DoNotOptimize
[[maybe_unused]] static void escape(void* p) {
    asm volatile("" : : "g"(p) : "memory");
}

// ClobberMemory
[[maybe_unused]] static void clobber() { asm volatile("" : : : "memory"); }

std::function<void()> createLambdaMin() {
    [[maybe_unused]] LargeObject lo;
    auto lambda = [lo]() { [[maybe_unused]] auto dummy = lo; };
    return lambda;
}

int main() {
    auto lambda = createLambdaMin();
    lambda();
    return 0;
}
