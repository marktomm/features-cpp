#ifndef MACRO_poly_LIB_H
#define MACRO_poly_LIB_H

#include <cstdint>

namespace poly {

// depth: 4
class A {
public:
    virtual ~A() {}
    virtual void PureVirtualFn() = 0;
    int a;
};

class B: public A {
public:
    virtual void VirtualFn(){};
    int b;
};

class C: public B {
public:
    int c;
};

class D final: public C {
public:
    void PureVirtualFn() override {}
    void VirtualFn() override{};
    int d;
};

class E: public C {
public:
    void PureVirtualFn() override {}
    void VirtualFn() override{};
    int e;
};

class F: public C {
public:
    void PureVirtualFn() override {}
    void VirtualFn() override{};
    int f;
};

// depth: 4
class nonVirtualA {
public:
    void Fn() {}
    int a;
};

class nonVirtualB: public nonVirtualA {
public:
    int b;
};

class nonVirtualC: public nonVirtualB {
public:
    int c;
};

class nonVirtualD final: public nonVirtualC {
public:
    int d;
};

}; // namespace poly

#endif
