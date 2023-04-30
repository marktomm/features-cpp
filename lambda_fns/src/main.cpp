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

void large_lambda_3() {
    // std::unique_ptr<LargeObject> obj = std::make_unique<LargeObject>();
    // std::unique_ptr<LargeObject> obj1 = std::make_unique<LargeObject>();
    // std::unique_ptr<LargeObject> obj2 = std::make_unique<LargeObject>();
    // std::unique_ptr<LargeObject> obj3 = std::make_unique<LargeObject>();
    // std::unique_ptr<LargeObject> obj4 = std::make_unique<LargeObject>();
    LargeObject* obj = new LargeObject{};
    LargeObject* obj1 = new LargeObject{};
    LargeObject* obj2 = new LargeObject{};
    LargeObject* obj3 = new LargeObject{};
    LargeObject* obj4 = new LargeObject{};
    [[maybe_unused]] auto lambda = [pobj = *obj, pobj1 = *obj1, pobj2 = *obj2,
                                    pobj3 = *obj3, pobj4 = *obj4]() {
        [[maybe_unused]] auto cobj = pobj;
        [[maybe_unused]] auto cobj1 = pobj1;
        [[maybe_unused]] auto cobj2 = pobj2;
        [[maybe_unused]] auto cobj3 = pobj3;
        [[maybe_unused]] auto cobj4 = pobj4;
        std::cout << "Captured large object with size " << sizeof(cobj)
                  << std::endl;
        std::cout << "Captured large object with size " << sizeof(pobj1)
                  << std::endl;
        std::cout << "Captured large object with size " << sizeof(pobj2)
                  << std::endl;
        std::cout << "Captured large object with size " << sizeof(pobj3)
                  << std::endl;
        std::cout << "Captured large object with size " << sizeof(pobj4)
                  << std::endl;
    };
    // [[maybe_unused]] auto lambda = [pobj = move(*obj), pobj1 = move(*obj1),
    //                                 pobj2 = move(*obj2), pobj3 = move(*obj3),
    //                                 pobj4 = move(*obj4)]() {
    //     std::cout << "Captured large object with size " << sizeof(pobj)
    //               << std::endl;
    //     std::cout << "Captured large object with size " << sizeof(pobj1)
    //               << std::endl;
    //     std::cout << "Captured large object with size " << sizeof(pobj2)
    //               << std::endl;
    //     std::cout << "Captured large object with size " << sizeof(pobj3)
    //               << std::endl;
    //     std::cout << "Captured large object with size " << sizeof(pobj4)
    //               << std::endl;
    // };
    delete obj;
    delete obj1;
    delete obj2;
    delete obj3;
    delete obj4;
    lambda();
}

std::function<void()> createLambda() {
    LargeObject lo;
    LargeObject lo1;
    LargeObject lo2;
    LargeObject lo3;
    LargeObject lo4;
    // Capture lo by value
    auto lambda = [lo, lo1, lo2, lo3, lo4]() {
        std::cout << "First element of the captured LargeObject: " << lo.data[0]
                  << std::endl;
        std::cout << "First element of the captured LargeObject: "
                  << lo1.data[0] << std::endl;
        std::cout << "First element of the captured LargeObject: "
                  << lo2.data[0] << std::endl;
        std::cout << "First element of the captured LargeObject: "
                  << lo3.data[0] << std::endl;
        std::cout << "First element of the captured LargeObject: "
                  << lo4.data[0] << std::endl;
    };

    return lambda;
}

std::function<void()> createLambdaMin() {
    LargeObject lo;
    // LargeObject lo1;
    // LargeObject lo2;
    // LargeObject lo3;
    // LargeObject lo4;
    // Capture lo by value
    auto lambda = [lo
                   //, lo1, lo2, lo3, lo4
    ]() {
        std::cout << "First element of the captured LargeObject: " << lo.data[0]
                  << std::endl;
        // std::cout << "First element of the captured LargeObject: "
        //           << lo1.data[0] << std::endl;
        // std::cout << "First element of the captured LargeObject: "
        //           << lo2.data[0] << std::endl;
        // std::cout << "First element of the captured LargeObject: "
        //           << lo3.data[0] << std::endl;
        // std::cout << "First element of the captured LargeObject: "
        //           << lo4.data[0] << std::endl;
    };

    return lambda;
}

int main() {
    // LargeObject lobj;
    // auto* const ptr = new LargeObject{}; // &lobj;
    // std::unique_ptr<LargeObject, void (*)(LargeObject*)> obj(
    //     ptr, [](LargeObject*) {});
    // auto lambda = large_lambda(move(obj));
    // lambda();
    // delete (ptr);

    // large_lambda_2();

    // large_lambda_3();

    // auto lambda4 = createLambdaMin();
    // lambda4();

    LargeObject* ptr = new LargeObject{};
    // LargeObject lobj;
    std::cout << ptr->data[0];
    delete ptr;
    return 0;
}
