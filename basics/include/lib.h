#ifndef MACRO_basics_LIB_H
#define MACRO_basics_LIB_H

#include <cstdint>
#include <ctime>

namespace basics {

class A {
public:
    std::uintptr_t a{};
};

class A2 {
public:
    std::uintptr_t a{};
    std::uintptr_t b{};
};

class A3 {
public:
    std::uintptr_t a{};
    std::uintptr_t b{};
    std::uintptr_t c{};
    std::uintptr_t d{};
};

class A4 {
public:
    std::uintptr_t a[64] = {};
};

// GEN_PROTO_BEGIN
void clobber();
void doNotOptimize(void* p);
// GEN_PROTO_END

class TimeDur final {
public:
    TimeDur(const char* desc, clock_t tdur);
    TimeDur();

    const char* GetDesc() const noexcept;
    clock_t GetDur() const noexcept;

private:
    const char* desc_;
    clock_t tdur_;
};

}; // namespace basics

#endif
