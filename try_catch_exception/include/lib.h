#ifndef MACRO_try_catch_exception_LIB_H
#define MACRO_try_catch_exception_LIB_H

#include <benchmark/benchmark.h>

#include <cstdint>

namespace try_catch_exception {

class A {
public:
};

// GEN_PROTO_BEGIN
int getRandom();
int pspdfkit_ErrorCode();
int strip_ErrorCode(bool res);
int strip_ErrorCodeVbools(std::vector<bool> const& v);
void loop_pause_resume(benchmark::State& state);
void loop_random(benchmark::State& state);
void loop_std_function(benchmark::State& state);
void loop_std_function_call(benchmark::State& state);
void loop_std_function_call_throw(benchmark::State& state);
void loop_vbools_access_no_opt(benchmark::State& state);
void loop_vbools_access_opt(benchmark::State& state);
void loop_vbools_global_index_access_no_opt(benchmark::State& state);
void pspdfkit_BasicException();
void pspdfkit_MessageException();
void pspdfkit_Return();
void strip_BasicException(bool res);
void strip_MessageException(bool res);
void strip_Return(bool res);
// GEN_PROTO_END

}; // namespace try_catch_exception

#endif
