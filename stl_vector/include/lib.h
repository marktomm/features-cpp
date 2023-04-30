#ifndef MACRO_stl_vector_LIB_H
#define MACRO_stl_vector_LIB_H

#include <cstdint>
#include <random>

namespace stl_vector {

class A {
public:
};

template<typename Container>
Container generateRandomContainer(std::size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-10000, 10000);

    Container c;
    for (std::size_t i = 0; i < size; ++i) {
        c.push_back(dist(gen));
    }
    return c;
}

// GEN_PROTO_BEGIN
// GEN_PROTO_END

}; // namespace stl_vector

#endif
