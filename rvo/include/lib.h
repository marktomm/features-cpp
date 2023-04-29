#ifndef MACRO_rvo_LIB_H
#define MACRO_rvo_LIB_H

#include <array>
#include <iostream>

#include <cstdint>

namespace rvo {

struct LargeObject {
    LargeObject() {}
    LargeObject(LargeObject const&) {}
    LargeObject(LargeObject&&) {}
    ~LargeObject() {}

    LargeObject& operator=(LargeObject const&) { return *this; }
    LargeObject& operator=(LargeObject&&) { return *this; }

    std::array<uint32_t, 10000> data;
};

}; // namespace rvo

#endif
