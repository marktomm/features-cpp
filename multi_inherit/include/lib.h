#ifndef MACRO_multi_inherit_LIB_H
#define MACRO_multi_inherit_LIB_H

#include <cstdint>

namespace multi_inherit {

class A {
public:
    uint32_t a{5};
};

class B {
public:
    uint32_t b{255};
};

class CC: public A, public B {
    /* ... */
};

}; // namespace multi_inherit

#endif
