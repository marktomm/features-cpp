#ifndef MACRO_basics_LIB_H
#define MACRO_basics_LIB_H

#include <cstdint>

namespace basics {

class A {
public:
    std::uintptr_t a{};
};

class A2 {
public:
    std::uintptr_t a{};
    std::uintptr_t b{};
};

class A3 {
public:
    std::uintptr_t a{};
    std::uintptr_t b{};
    std::uintptr_t c{};
    std::uintptr_t d{};
};

class A4 {
public:
    std::uintptr_t a[64] = {};
};

// GEN_PROTO_BEGIN

// GEN_PROTO_END

}; // namespace basics

#endif
