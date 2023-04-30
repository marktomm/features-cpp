#ifndef MACRO_try_catch_exception_LIB_H
#define MACRO_try_catch_exception_LIB_H

#include <benchmark/benchmark.h>

#include <cstdint>
#include <functional>

namespace try_catch_exception {

class A {
public:
};

using cb = void (*)(bool);
using cf = std::function<void(bool)>;
using ci = std::function<void(int)>;

// GEN_PROTO_BEGIN
int getRandom();
int pspdfkit_ErrorCode();
int strip_ErrorCode(bool res);
int strip_ErrorCodeVbools(std::vector<bool> const& v);
std::size_t GetNextGlobalIndex();
std::vector<bool> GetRandomBools();
std::vector<uint32_t> setup();
void fnx1();
void fnx2(std::function<int(bool)> fn);
void loop_getrandom_try_block_ptr(benchmark::State& state, cb callback);
void loop_getrandom_try_block_sfn(benchmark::State& state, cf callback);
void loop_pause_resume(benchmark::State& state);
void loop_random(benchmark::State& state);
void loop_std_function(benchmark::State& state);
void loop_std_function_call(benchmark::State& state);
void loop_std_function_call_throw(benchmark::State& state);
void loop_vbools_access_no_opt(benchmark::State& state);
void loop_vbools_access_opt(benchmark::State& state);
void loop_vbools_global_index_access_no_opt(benchmark::State& state);
void loop_vbools_pause_resume_sfn(ci callback, benchmark::State& state);
void loop_vbools_try_block_ptr(benchmark::State& state, cb callback);
void pspdfkit_BasicException();
void pspdfkit_MessageException();
void pspdfkit_Return();
void strip_BasicException(bool res);
void strip_MessageException(bool res);
void strip_Return(bool res);
// GEN_PROTO_END

}; // namespace try_catch_exception

#endif
