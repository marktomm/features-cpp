#ifndef MACRO_virtual_base_class_LIB_H
#define MACRO_virtual_base_class_LIB_H

#include <cstdint>

/// @cond NO_NAMESPACE_IN_DOC
namespace virtual_base_class {
/// @endcond

class A {
public:
    virtual ~A() {}
    int a;
};

class B: virtual public A {
public:
    int b;
};

class C: virtual public A {
public:
    int c;
};

class D: public B, public C {
public:
    int d;
};

// non virtual diamond
class nonVirtualDiamondA {
public:
    virtual ~nonVirtualDiamondA() {}
    int a;
};

class nonVirtualDiamondB: public nonVirtualDiamondA {
public:
    int b;
};

class nonVirtualDiamondC: public nonVirtualDiamondA {
public:
    int c;
};

class nonVirtualDiamondD: public nonVirtualDiamondB, public nonVirtualDiamondC {
public:
    int d;
};

// depth: 4
class nonDiamondA {
public:
    virtual ~nonDiamondA() {}
    int a;
};

class nonDiamondB: public nonDiamondA {
public:
    int b;
};

class nonDiamondC: public nonDiamondB {
public:
    int c;
};

class nonDiamondD: public nonDiamondC {
public:
    int d;
};

// for cross casting
class X {
public:
    virtual ~X() {}
    int x;
};

class Y {
public:
    virtual ~Y() {}
    int y;
};

class Z: public X, public Y {
public:
    int z;
};

// depth: 3
class I {
public:
    virtual ~I() {}
    int i;
};

class J: public I {
public:
    int j;
};

class K: public J {
public:
    int k;
};

// unrelated casting
class M {
public:
    virtual ~M() {}
    int m;
};

class N {
public:
    virtual ~N() {}
    int n;
};

}; // namespace virtual_base_class

#endif
