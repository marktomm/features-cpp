#ifndef MACRO_trivial_type_LIB_H
#define MACRO_trivial_type_LIB_H

#include <cstdint>
#include <memory>

namespace trivial_type {

// GEN_PROTO_BEGIN
int FnRet([[maybe_unused]] int* p);
int FnRet([[maybe_unused]] std::unique_ptr<int> p);
int TestFunction(int* x);
int TestFunction(std::unique_ptr<int> x);
void FnEscape([[maybe_unused]] int* p);
void FnEscape([[maybe_unused]] std::unique_ptr<int> p);
void FnNoop([[maybe_unused]] int*);
void FnNoop([[maybe_unused]] std::unique_ptr<int>);
// GEN_PROTO_END

}; // namespace trivial_type

#endif
