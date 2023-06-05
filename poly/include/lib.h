#ifndef MACRO_poly_LIB_H
#define MACRO_poly_LIB_H

#include <cstdint>

namespace poly {

// depth: 4
class nonVA {
public:
    void Fn(uint32_t i) { a += i; }
    void FnNone() {}
    int a{66};
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

class nonVD1 final: public nonVC {
public:
    int d;
};

class nonVD2 final: public nonVC {
public:
    int d;
};

class Ax {
public:
    virtual ~Ax() {}
    virtual void Fn(){};
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

// depth: 6 A - E
class A {
public:
    virtual ~A() {}
    virtual void PureVFn() = 0;
    virtual void PureVFn(int i) = 0;
    virtual void VFn(){};
    int a;
};

// class B: public A {
// public:
//     int b;
// };

// class C: public B {
// public:
//     int c;
// };

class D final: public A {
public:
    void PureVFn() override {}
    void PureVFn(int i) override { d += i; }
    void VFn() override{};
    int d{544};
};

class E: public A {
public:
    void PureVFn() override {}
    void PureVFn(int i) override { e += i; }
    void VFn() override{};
    int e{644};
};

// class F: public C {
// public:
//     void PureVFn() override {}
//     void VFn() override{};
//     int f;
// };

}; // namespace poly

#endif
