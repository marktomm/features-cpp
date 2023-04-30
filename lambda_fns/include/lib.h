#ifndef MACRO_lambda_LIB_H
#define MACRO_lambda_LIB_H

#include <array>

#include <cstdint>
#include <functional>

#include <benchmark/benchmark.h>

namespace lambda_fns {

struct SmallObject {
    std::array<int, 1> data{};
};

struct LargeObject {
    std::array<int, 10000> data{};
};

// GEN_PROTO_BEGIN
std::function<void()> create_lambda_min();
std::function<void()> large_obj_lambda_ret();
std::function<void()> small_obj_lambda_ret();
void large_obj();
void large_obj_lambda();
void large_obj_lambda_call();
void large_obj_lambda_call_ref(LargeObject& obj);
void large_obj_lambda_opt();
void large_obj_lambda_opt_ref(LargeObject& obj);
void large_obj_lambda_ref(LargeObject& obj);
void large_obj_opt();
void small_obj();
void small_obj_lambda();
void small_obj_lambda_call();
void small_obj_lambda_call_ref(SmallObject& obj);
void small_obj_lambda_opt();
void small_obj_lambda_opt_ref(SmallObject& obj);
void small_obj_lambda_ref(SmallObject& obj);
void small_obj_opt();
// GEN_PROTO_END

}; // namespace lambda_fns

#endif
