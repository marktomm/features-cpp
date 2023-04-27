#ifndef MACRO_class_member_funcion_LIB_H
#define MACRO_class_member_funcion_LIB_H

#include <cstdint>

namespace class_member_funcion {

class Z {
public:
    Z* fn3([[maybe_unused]] uint32_t x) { return this; }
};

uint32_t fn4(uint32_t x);

}; // namespace class_member_funcion

#endif
