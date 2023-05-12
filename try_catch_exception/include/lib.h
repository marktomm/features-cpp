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
int ErrCode_33p();
int ErrCode_50p();
int ErrCode_Arg(bool res);
int ErrCode_Vec_Rand(std::vector<bool> const& v);
int getRand12();
int getRand13();
std::size_t GetNextGlobalIndex();
std::vector<bool> GetRandBools();
std::vector<uint32_t> setup();
void ExBasic_50p();
void ExMessage_50p();
void fnx1();
void fnx2(std::function<int(bool)> fn);
void loop_pause_resume(benchmark::State& state);
void loop_Rand_33p_Cb_Arg(benchmark::State& state, cf callback);
void loop_Rand_50p_Cb_Arg(benchmark::State& state, cf callback);
void loop_random50(benchmark::State& state);
void loop_random(benchmark::State& state);
void loop_StdFn_Call(benchmark::State& state);
void loop_StdFn_Call_throw(benchmark::State& state);
void loop_StdFn_Cr_Dr(benchmark::State& state);
void loop_vbools_pause_resume_sfn(ci callback, benchmark::State& state);
void loop_VecRand_Cb_Arg(benchmark::State& state, cb callback);
void loop_VecRand_Global_Idx(benchmark::State& state);
void loop_VecRand_Local_Idx(benchmark::State& state);
void loop_VecRand_Local_Idx_Opt(benchmark::State& state);
void pspdfkit_BasicEx();
void pspdfkit_MessageEx();
void Return_33p();
void Return_50p();
void strip_BasicEx(bool res);
void strip_MessageEx(bool res);
void strip_Return(bool res);
// GEN_PROTO_END

}; // namespace try_catch_exception

#endif
