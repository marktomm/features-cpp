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

// GEN_PROTO_BEGIN
LargeObject return_by_value_no_rvo(const LargeObject& obj);
LargeObject return_by_value_rvo();
// GEN_PROTO_END

}; // namespace rvo

#endif
