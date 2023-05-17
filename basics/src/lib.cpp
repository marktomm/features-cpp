#include "lib.h"

namespace basics {

void doNotOptimize(void* p) { asm volatile("" : : "g"(p) : "memory"); }
void clobber() { asm volatile("" : : : "memory"); }

TimeDur::TimeDur(const char* desc, clock_t tdur) : desc_{desc}, tdur_{tdur} {}
TimeDur::TimeDur() : desc_{0}, tdur_{0} {}

const char* TimeDur::GetDesc() const noexcept { return desc_; }
clock_t TimeDur::GetDur() const noexcept { return tdur_; }

} // namespace basics
