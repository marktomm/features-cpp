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

int main() {
    // auto lambda = create_lambda_min();
    // lambda();
    // large_obj_lambda_call();

    // will add 40KB
    large_obj_lambda_ret();
    // nothing
    large_obj_lambda_call();
    return 0;
}
