// Initial base code taken from:
// https://pspdfkit.com/blog/2020/performance-overhead-of-exceptions-in-cpp/

#include <benchmark/benchmark.h>

#include "lib.h"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <random>
#include <stdexcept>

using namespace try_catch_exception;

// clang-format off
// grep -E '^[[:blank:]]*(inline[[:blank:]]+)?(virtual[[:blank:]]+)?(explicit[[:blank:]]+)?(static[[:blank:]]+)?(const[[:blank:]]+)?(constexpr[[:blank:]]+)?[a-zA-Z_][a-zA-Z0-9_]*[[:blank:]]+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^{}]*\)\s*(const)?[[:blank:]]*\{' try_catch_exception/bench.cpp | sed -E 's/(.*\)) *\{.*/\1;/' | sort -k 2,1
// clang-format on
// GEN_PROTO_BEGIN
void BM_00_StdFn_Cr_Dr(benchmark::State& state);
void BM_01_StdFn_Call(benchmark::State& state);
void BM_02_StdFn_Call_Arg(benchmark::State& state);
void BM_03_StdFn_Call_Rand_Arg(benchmark::State& state);
void BM_51_Ex_VecRand_Cb_Arg_Message(benchmark::State& state);
void BM_53_Ex_Rand_33p_Cb_Arg_Message(benchmark::State& state);
void BM_55_Ex_Rand_33p_Basic(benchmark::State& state);
void BM_56_Ex_Rand_33p_Message(benchmark::State& state);
void BM_64_Ex_StdFn_Call(benchmark::State& state);
void BM_72_VecRand_Cb_Arg_Return(benchmark::State& state);
void BM_73_Ex_Rand_50p_Cb_Arg_Message(benchmark::State& state);
void BM_75_Rand_50p_Cb_Arg_Return(benchmark::State& state);
void BM_E8_Ex_Rand_50p_Cb_Arg_Basic(benchmark::State& state);
void BM_G3_Rand_33p_Cb_Arg_StdFn_ErrCode(benchmark::State& state);
void BM_I0_RuntimeEx_Cr_Dr(benchmark::State& state);
void BM_J1_Ex_VecRand_Cb_Arg_Basic(benchmark::State& state);
void BM_R0_Rand_33p(benchmark::State& state);
void BM_R1_Rand_33p_Return(benchmark::State& state);
void BM_R2_Rand_33p_ErrCode(benchmark::State& state);
void BM_R4_Rand_33p_Cb_Arg_ErrCode(benchmark::State& state);
void BM_R5_Rand_33p_Cb_Arg_Return(benchmark::State& state);
void BM_R8_Rand_50p(benchmark::State& state);
void BM_R9_Ex_Rand_33p_Cb_Arg_Basic(benchmark::State& state);
void BM_U1_VecRand_Cb_Arg_Return(benchmark::State& state);
void BM_U5_Ex_None(benchmark::State& state);
void BM_V0_VecRand_Local_Idx(benchmark::State& state);
void BM_V9_VecRand_Global_Idx(benchmark::State& state);
void BM_W1_VecRand_Local_Idx_Opt(benchmark::State& state);
void BM_XX_Ex_vbools_pause_resume_sfn_Basic(benchmark::State& state);
void BM_XX_pause_resume(benchmark::State& state);
void BM_XX_test21_exitWithErrCode(benchmark::State& state);
void BM_XX_test31_exitWithErrCode(benchmark::State& state);
void BM_XX_vbools_pause_resume_sfn(benchmark::State& state);
void BM_XX_vbools_pause_resume_sfn_ErrCode(benchmark::State& state);
void BM_XX_vbools_pause_resume_sfn_Return(benchmark::State& state);
void BM_YY_VecRand_Cb_Arg_ErrCode_2(benchmark::State& state);
void BM_YY_VecRand_Cb_Arg_ErrCode(benchmark::State& state);
// GEN_PROTO_END

// Initial base code taken from:
// https://pspdfkit.com/blog/2020/performance-overhead-of-exceptions-in-cpp/
// BEGIN

// 1.
void BM_55_Ex_Rand_33p_Basic(benchmark::State& state) {
    for (auto _ : state) {
        try {
            pspdfkit_BasicEx();
        } catch (int ex) {
            // Caught! Carry on next iteration.
        }
    }
}
// 2.
void BM_56_Ex_Rand_33p_Message(benchmark::State& state) {
    for (auto _ : state) {
        try {
            pspdfkit_MessageEx();
        } catch (const std::runtime_error& ex) {
            // Caught! Carry on next iteration.
        }
    }
}
// 3.
void BM_R1_Rand_33p_Return(benchmark::State& state) {
    for (auto _ : state) {
        Return_33p();
    }
}
// 4.
void BM_R2_Rand_33p_ErrCode(benchmark::State& state) {
    for (auto _ : state) {
        auto err = ErrCode_33p();
        if (err < 0) {
            // `handle_error()` ...
        }
    }
}

// Initial base code taken from:
// https://pspdfkit.com/blog/2020/performance-overhead-of-exceptions-in-cpp/
// END

void BM_XX_vbools_pause_resume_sfn(benchmark::State& state) {
    loop_vbools_pause_resume_sfn([](int) {}, state);
}

void BM_R0_Rand_33p(benchmark::State& state) { loop_random(state); }
void BM_R8_Rand_50p(benchmark::State& state) { loop_random50(state); }

void BM_I0_RuntimeEx_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        std::runtime_error("Message");
    }
}

void BM_XX_pause_resume(benchmark::State& state) { loop_pause_resume(state); }

void BM_V0_VecRand_Local_Idx(benchmark::State& state) {
    loop_VecRand_Local_Idx(state);
}

void BM_W1_VecRand_Local_Idx_Opt(benchmark::State& state) {
    loop_VecRand_Local_Idx_Opt(state);
}

void BM_V9_VecRand_Global_Idx(benchmark::State& state) {
    loop_VecRand_Global_Idx(state);
}

void BM_00_StdFn_Cr_Dr(benchmark::State& state) { loop_StdFn_Cr_Dr(state); }

void BM_01_StdFn_Call(benchmark::State& state) { loop_StdFn_Call(state); }

void BM_02_StdFn_Call_Arg(benchmark::State& state) {
    std::function<int(uint32_t)> fn = [](uint32_t a) -> uint32_t {
        return a++;
    };
    uint32_t it = 0;
    for (auto _ : state) {
        uint32_t x = ++it == 100 ? it = 0 : it;
        benchmark::DoNotOptimize(fn);
        benchmark::DoNotOptimize(fn(x));
    }
}

void BM_03_StdFn_Call_Rand_Arg(benchmark::State& state) {
    std::function<int(uint32_t)> fn = [](uint32_t a) -> uint32_t {
        return a++;
    };
    for (auto _ : state) {
        benchmark::DoNotOptimize(fn);
        benchmark::DoNotOptimize(fn(26));
    }
}

void BM_64_Ex_StdFn_Call(benchmark::State& state) {
    loop_StdFn_Call_throw(state);
}

// 1.
void BM_J1_Ex_VecRand_Cb_Arg_Basic(benchmark::State& state) {
    loop_VecRand_Cb_Arg(state, strip_BasicEx);
}
// 2.
void BM_51_Ex_VecRand_Cb_Arg_Message(benchmark::State& state) {
    loop_VecRand_Cb_Arg(state, strip_MessageEx);
}
// 3.
void BM_U1_VecRand_Cb_Arg_Return(benchmark::State& state) {
    loop_VecRand_Cb_Arg(state, strip_Return);
}

// 21.
void BM_R9_Ex_Rand_33p_Cb_Arg_Basic(benchmark::State& state) {
    loop_Rand_33p_Cb_Arg(state, strip_BasicEx);
}
// 22.
void BM_53_Ex_Rand_33p_Cb_Arg_Message(benchmark::State& state) {
    loop_Rand_33p_Cb_Arg(state, strip_MessageEx);
}

// 23.
void BM_R5_Rand_33p_Cb_Arg_Return(benchmark::State& state) {
    loop_Rand_33p_Cb_Arg(state, strip_Return);
}

// 3.
void BM_72_VecRand_Cb_Arg_Return(benchmark::State& state) {
    loop_VecRand_Cb_Arg(state, strip_Return);
}

// 21.
void BM_E8_Ex_Rand_50p_Cb_Arg_Basic(benchmark::State& state) {
    loop_Rand_50p_Cb_Arg(state, strip_BasicEx);
}
// 22.
void BM_73_Ex_Rand_50p_Cb_Arg_Message(benchmark::State& state) {
    loop_Rand_50p_Cb_Arg(state, strip_MessageEx);
}

// 23.
void BM_75_Rand_50p_Cb_Arg_Return(benchmark::State& state) {
    loop_Rand_50p_Cb_Arg(state, strip_Return);
}

// 4.
void BM_YY_VecRand_Cb_Arg_ErrCode(benchmark::State& state) {
    auto v = GetRandBools();
    for (auto _ : state) {
        auto it = GetNextGlobalIndex();
        bool res = v[it];
        auto err = ErrCode_Arg(res);
        if (err < 0) {
        }
    }
}
// x.
void BM_YY_VecRand_Cb_Arg_ErrCode_2(benchmark::State& state) {
    auto v = GetRandBools();
    for (auto _ : state) {
        auto err = ErrCode_Vec_Rand(v);
        if (err < 0) {
        }
    }
}

// 4.
void BM_R4_Rand_33p_Cb_Arg_ErrCode(benchmark::State& state) {
    for (auto _ : state) {
        fnx1();
    }
}
// 5.
void BM_XX_test21_exitWithErrCode(benchmark::State& state) {
    for (auto _ : state) {
        auto err = ErrCode_33p();
        if (err < 0) {
        }
    }
}

// 4.
void BM_G3_Rand_33p_Cb_Arg_StdFn_ErrCode(benchmark::State& state) {
    std::function<int(bool)> fn = ErrCode_Arg;
    for (auto _ : state) {
        fnx2(fn);
    }
}
// 5.
void BM_XX_test31_exitWithErrCode(benchmark::State& state) {
    for (auto _ : state) {
        auto err = ErrCode_33p();
        if (err < 0) {
        }
    }
}

void BM_XX_Ex_vbools_pause_resume_sfn_Basic(benchmark::State& state) {
    loop_vbools_pause_resume_sfn(
        [](bool it) {
            try {
                if (it == true) {
                    throw 0;
                }
            } catch (int ex) {
            }
        },
        state);
}

void BM_U5_Ex_None(benchmark::State& state) {
    auto it = false;
    for (auto _ : state) {
        try {
            if (it == true) {
                throw 0;
            }
            benchmark::DoNotOptimize(it);
        } catch (int ex) {
        }
    }
}

void BM_XX_vbools_pause_resume_sfn_Return(benchmark::State& state) {
    loop_vbools_pause_resume_sfn(
        [](bool it) {
            if (it == true) {
                return;
            }
        },
        state);
}

void BM_XX_vbools_pause_resume_sfn_ErrCode(benchmark::State& state) {
    loop_vbools_pause_resume_sfn(
        [](bool it) {
            if (it) {
                int x = 0;
                benchmark::DoNotOptimize(x);
            }
        },
        state);
}

#define AUTOSORT

#ifdef AUTOSORT
// clang-format off
// grep -E '^[[:blank:]]*(inline[[:blank:]]+)?(virtual[[:blank:]]+)?(explicit[[:blank:]]+)?(static[[:blank:]]+)?(const[[:blank:]]+)?(constexpr[[:blank:]]+)?[a-zA-Z_][a-zA-Z0-9_]*[[:blank:]]+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^{}]*\)\s*(const)?[[:blank:]]*\{' try_catch_exception/bench.cpp | sed -E 's/(.*\)) *\{.*/\1;/' | grep -F 'BM_' | sed -E 's/.*(BM_[^(]*).*/BENCHMARK(\1);/' | sort -k1.14
// clang-format on
// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_StdFn_Cr_Dr);
BENCHMARK(BM_01_StdFn_Call);
BENCHMARK(BM_02_StdFn_Call_Arg);
BENCHMARK(BM_03_StdFn_Call_Rand_Arg);
BENCHMARK(BM_51_Ex_VecRand_Cb_Arg_Message);
BENCHMARK(BM_53_Ex_Rand_33p_Cb_Arg_Message);
BENCHMARK(BM_55_Ex_Rand_33p_Basic);
BENCHMARK(BM_56_Ex_Rand_33p_Message);
BENCHMARK(BM_64_Ex_StdFn_Call);
BENCHMARK(BM_72_VecRand_Cb_Arg_Return);
BENCHMARK(BM_73_Ex_Rand_50p_Cb_Arg_Message);
BENCHMARK(BM_75_Rand_50p_Cb_Arg_Return);
BENCHMARK(BM_E8_Ex_Rand_50p_Cb_Arg_Basic);
BENCHMARK(BM_G3_Rand_33p_Cb_Arg_StdFn_ErrCode);
BENCHMARK(BM_I0_RuntimeEx_Cr_Dr);
BENCHMARK(BM_J1_Ex_VecRand_Cb_Arg_Basic);
BENCHMARK(BM_R0_Rand_33p);
BENCHMARK(BM_R1_Rand_33p_Return);
BENCHMARK(BM_R2_Rand_33p_ErrCode);
BENCHMARK(BM_R4_Rand_33p_Cb_Arg_ErrCode);
BENCHMARK(BM_R5_Rand_33p_Cb_Arg_Return);
BENCHMARK(BM_R8_Rand_50p);
BENCHMARK(BM_R9_Ex_Rand_33p_Cb_Arg_Basic);
BENCHMARK(BM_U1_VecRand_Cb_Arg_Return);
BENCHMARK(BM_U5_Ex_None);
BENCHMARK(BM_V0_VecRand_Local_Idx);
BENCHMARK(BM_V9_VecRand_Global_Idx);
BENCHMARK(BM_W1_VecRand_Local_Idx_Opt);
BENCHMARK(BM_XX_Ex_vbools_pause_resume_sfn_Basic);
BENCHMARK(BM_XX_pause_resume);
BENCHMARK(BM_XX_test21_exitWithErrCode);
BENCHMARK(BM_XX_test31_exitWithErrCode);
BENCHMARK(BM_XX_vbools_pause_resume_sfn);
BENCHMARK(BM_XX_vbools_pause_resume_sfn_ErrCode);
BENCHMARK(BM_XX_vbools_pause_resume_sfn_Return);
BENCHMARK(BM_YY_VecRand_Cb_Arg_ErrCode);
BENCHMARK(BM_YY_VecRand_Cb_Arg_ErrCode_2);
// GEN_BENCHMARK_END
#endif

BENCHMARK_MAIN();
