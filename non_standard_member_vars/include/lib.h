#ifndef MACRO_non_standard_member_vars_LIB_H
#define MACRO_non_standard_member_vars_LIB_H

#include <cstdint>

namespace non_standard_member_vars {

class Base {
public:
    int a{65535};
};

class NonStandard: public Base {
public:
    int b{65525};
};

class StandardClass {
public:
    int a{65515};
    int b{65505};
};

}; // namespace non_standard_member_vars

#endif
