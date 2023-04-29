#include "lib.h"

using namespace lambda_fns;
using namespace std;

#include <array>
#include <iostream>
#include <memory>
#include <utility>

void large_lambda() {
    std::unique_ptr<LargeObject> obj = std::make_unique<LargeObject>();
    auto lambda = [move(*obj)]() {
        std::cout << "Captured large object with size " << sizeof(*obj)
                  << std::endl;
    };
    lambda();
}

int main() {
    large_lambda();
    return 0;
}
