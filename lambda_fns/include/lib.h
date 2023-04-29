#ifndef MACRO_lambda_LIB_H
#define MACRO_lambda_LIB_H

#include <array>

#include <cstdint>

namespace lambda_fns {

struct SmallObject {
    int data{254};
};

struct LargeObject {
    std::array<int, 1000000> data{};
};

}; // namespace lambda_fns

#endif
