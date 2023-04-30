#include "lib.h"

namespace rvo {

// Function that returns by value
LargeObject return_by_value_no_rvo(const LargeObject& obj) { return obj; }

// Function that returns by value with RVO in C++17
LargeObject return_by_value_rvo() {
    LargeObject obj;
    return obj; // RVO will occur in C++17
}
} // namespace rvo
