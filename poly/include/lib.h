#ifndef MACRO_poly_LIB_H
#define MACRO_poly_LIB_H

#include <cstdint>

namespace poly {

// depth: 4
class A {
public:
    virtual ~A() {}
    virtual void PureVFn() = 0;
    int a;
};

class B: public A {
public:
    virtual void VFn(){};
    int b;
};

class C: public B {
public:
    int c;
};

class D final: public C {
public:
    void PureVFn() override {}
    void VFn() override{};
    int d;
};

class E: public C {
public:
    void PureVFn() override {}
    void VFn() override{};
    int e;
};

class F: public C {
public:
    void PureVFn() override {}
    void VFn() override{};
    int f;
};

// depth: 4
class nonVA {
public:
    void Fn() {}
    int a;
};

class nonVB: public nonVA {
public:
    int b;
};

class nonVC: public nonVB {
public:
    int c;
};

class nonVD final: public nonVC {
public:
    int d;
};

class Ax {
public:
    virtual ~Ax() {}
    int a;
};

class Bx: virtual public Ax {
public:
    int b;
};

class Cx: virtual public Ax {
public:
    int c;
};

class Dx: public Bx, public Cx {
public:
    int d;
};

}; // namespace poly

#endif
