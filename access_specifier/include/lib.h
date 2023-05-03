#ifndef MACRO_access_specifier_LIB_H
#define MACRO_access_specifier_LIB_H

#include <cstdint>

namespace access_specifier {

// klass A versioon 1
class A {
public:
    uint32_t a{5};
    uint32_t q{65535};
};

class A2 {
public:
    uint32_t a{5};

protected:
    uint32_t q{65535};
};

}; // namespace access_specifier

#endif
