#include "lib.h"

using namespace lambda_fns;
using namespace std;

#include <array>
#include <iostream>
#include <memory>
#include <utility>

// DoNotOptimize
[[maybe_unused]] static void escape(void* p) {
    asm volatile("" : : "g"(p) : "memory");
}

// ClobberMemory
[[maybe_unused]] static void clobber() { asm volatile("" : : : "memory"); }

auto large_lambda(
    [[maybe_unused]] std::unique_ptr<LargeObject, void (*)(LargeObject*)> obj) {
    auto lambda = [pobj = *(obj.get())]() mutable {
        // std::cout << "Captured large object with size " << sizeof(*pobj)
        //   << std::endl;
        [[maybe_unused]] LargeObject& robj = pobj;
        ::escape(&pobj);
        ::escape(&robj);
    };
    return lambda;
    // return []() {};
}

void large_lambda_2() {
    std::unique_ptr<LargeObject> obj = std::make_unique<LargeObject>();
    auto lambda = [obj = move(*obj)]() {
        std::cout << "Captured large object with size " << sizeof(obj)
                  << std::endl;
    };
    lambda();
}

int main() {
    // LargeObject lobj;
    auto* const ptr = new LargeObject{}; // &lobj;
    std::unique_ptr<LargeObject, void (*)(LargeObject*)> obj(
        ptr, [](LargeObject*) {});
    auto lambda = large_lambda(move(obj));
    delete (ptr);
    lambda();

    large_lambda_2();

    return 0;
}
