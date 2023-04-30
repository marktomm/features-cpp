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

// clang-format off
// grep -E '^[[:blank:]]*(inline[[:blank:]]+)?(virtual[[:blank:]]+)?(explicit[[:blank:]]+)?(static[[:blank:]]+)?(const[[:blank:]]+)?(constexpr[[:blank:]]+)?[a-zA-Z_][a-zA-Z0-9_]*[[:blank:]]+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^{}]*\)\s*(const)?[[:blank:]]*\{' try_catch_exception/bench.cpp | sed -E 's/(.*\)) *\{.*/\1;/' | sort -k 2,1
// clang-format on
// GEN_PROTO_BEGIN
void BM_00_A1_random(benchmark::State& state);
void BM_00_A5_vbools_global_index_access(benchmark::State& state);
void BM_00_A8_pspdfkit_BasicException(benchmark::State& state);
void BM_01_A9_pspdfkit_MessageException(benchmark::State& state);
void BM_02_B1_pspdfkit_Return(benchmark::State& state);
void BM_03_B2_pspdfkit_ErrorCode(benchmark::State& state);
void BM_04_C2_vbools_try_block_ptr_BasicException(benchmark::State& state);
void BM_05_C3_vbools_try_block_ptr_MessageException(benchmark::State& state);
void BM_06_C4_vbools_try_block_ptr_Return(benchmark::State& state);
void BM_07_C5_vbools_try_block_ptr_ErrorCode(benchmark::State& state);
void BM_08_C51_vbools_try_block_ptr_ErrorCode(benchmark::State& state);
void BM_A0_vbools_pause_resume_sfn(benchmark::State& state);
void BM_A2_pause_resume(benchmark::State& state);
void BM_A3_vbools_access_opt(benchmark::State& state);
void BM_A4_vbools_access(benchmark::State& state);
void BM_A6_std_function(benchmark::State& state);
void BM_A71_std_function_call_throw(benchmark::State& state);
void BM_A7_std_function_call(benchmark::State& state);
void BM_B3_getrandom_try_block_ptr_BasicException(benchmark::State& state);
void BM_B4_getrandom_try_block_ptr_MessageException(benchmark::State& state);
void BM_B5_getrandom_try_block_ptr_Return(benchmark::State& state);
void BM_B6_getrandom_try_block_ptr_ErrorCode(benchmark::State& state);
void BM_B7_getrandom_try_block_fsn_BasicException(benchmark::State& state);
void BM_B8_getrandom_try_block_fsn_MessageException(benchmark::State& state);
void BM_B9_getrandom_try_block_fsn_Return(benchmark::State& state);
void BM_C1_getrandom_try_block_fsn_ErrorCode(benchmark::State& state);
void BM_C6_vbools_pause_resume_sfn_BasicException(benchmark::State& state);
void BM_C7_vbools_pause_resume_sfn_MessageException(benchmark::State& state);
void BM_C8_vbools_pause_resume_sfn_Return(benchmark::State& state);
void BM_C9_vbools_pause_resume_sfn_ErrorCode(benchmark::State& state);
void BM_test21_exitWithErrorCode(benchmark::State& state);
void BM_test31_exitWithErrorCode(benchmark::State& state);
// GEN_PROTO_END

// Initial base code taken from:
// https://pspdfkit.com/blog/2020/performance-overhead-of-exceptions-in-cpp/
// BEGIN

// 1.
void BM_00_A8_pspdfkit_BasicException(benchmark::State& state) {
    for (auto _ : state) {
        try {
            pspdfkit_BasicException();
        } catch (int ex) {
            // Caught! Carry on next iteration.
        }
    }
}
// 2.
void BM_01_A9_pspdfkit_MessageException(benchmark::State& state) {
    for (auto _ : state) {
        try {
            pspdfkit_MessageException();
        } catch (const std::runtime_error& ex) {
            // Caught! Carry on next iteration.
        }
    }
}
// 3.
void BM_02_B1_pspdfkit_Return(benchmark::State& state) {
    for (auto _ : state) {
        pspdfkit_Return();
    }
}
// 4.
void BM_03_B2_pspdfkit_ErrorCode(benchmark::State& state) {
    for (auto _ : state) {
        auto err = pspdfkit_ErrorCode();
        if (err < 0) {
            // `handle_error()` ...
        }
    }
}

// Initial base code taken from:
// https://pspdfkit.com/blog/2020/performance-overhead-of-exceptions-in-cpp/
// END

void BM_A0_vbools_pause_resume_sfn(benchmark::State& state) {
    loop_vbools_pause_resume_sfn([](int) {}, state);
}

void BM_00_A1_random(benchmark::State& state) { loop_random(state); }

void BM_A2_pause_resume(benchmark::State& state) { loop_pause_resume(state); }

void BM_A3_vbools_access_opt(benchmark::State& state) {
    loop_vbools_access_opt(state);
}

void BM_A4_vbools_access(benchmark::State& state) {
    loop_vbools_access_no_opt(state);
}

void BM_00_A5_vbools_global_index_access(benchmark::State& state) {
    loop_vbools_global_index_access_no_opt(state);
}

void BM_A6_std_function(benchmark::State& state) { loop_std_function(state); }

void BM_A7_std_function_call(benchmark::State& state) {
    loop_std_function_call(state);
}
void BM_A71_std_function_call_throw(benchmark::State& state) {
    loop_std_function_call_throw(state);
}

// 1.
void BM_04_C2_vbools_try_block_ptr_BasicException(benchmark::State& state) {
    loop_vbools_try_block_ptr(state, strip_BasicException);
}
// 2.
void BM_05_C3_vbools_try_block_ptr_MessageException(benchmark::State& state) {
    loop_vbools_try_block_ptr(state, strip_MessageException);
}
// 3.
void BM_06_C4_vbools_try_block_ptr_Return(benchmark::State& state) {
    loop_vbools_try_block_ptr(state, strip_Return);
}
// 4.
void BM_07_C5_vbools_try_block_ptr_ErrorCode(benchmark::State& state) {
    auto v = GetRandomBools();
    for (auto _ : state) {
        auto it = GetNextGlobalIndex();
        bool res = v[it];
        auto err = strip_ErrorCode(res);
        if (err < 0) {
        }
    }
}
// x.
void BM_08_C51_vbools_try_block_ptr_ErrorCode(benchmark::State& state) {
    auto v = GetRandomBools();
    for (auto _ : state) {
        auto err = strip_ErrorCodeVbools(v);
        if (err < 0) {
        }
    }
}

// 1.
void BM_B3_getrandom_try_block_ptr_BasicException(benchmark::State& state) {
    loop_getrandom_try_block_ptr(state, strip_BasicException);
}
// 2.
void BM_B4_getrandom_try_block_ptr_MessageException(benchmark::State& state) {
    loop_getrandom_try_block_ptr(state, strip_MessageException);
}
// 3.
void BM_B5_getrandom_try_block_ptr_Return(benchmark::State& state) {
    loop_getrandom_try_block_ptr(state, strip_Return);
}
// 4.
void BM_B6_getrandom_try_block_ptr_ErrorCode(benchmark::State& state) {
    for (auto _ : state) {
        bool res = getRandom() == errorInt;
        auto err = strip_ErrorCode(res);
        if (err < 0) {
        }
    }
}
// 5.
void BM_test21_exitWithErrorCode(benchmark::State& state) {
    for (auto _ : state) {
        auto err = pspdfkit_ErrorCode();
        if (err < 0) {
        }
    }
}

// 1.
void BM_B7_getrandom_try_block_fsn_BasicException(benchmark::State& state) {
    loop_getrandom_try_block_sfn(state, strip_BasicException);
}
// 2.
void BM_B8_getrandom_try_block_fsn_MessageException(benchmark::State& state) {
    loop_getrandom_try_block_sfn(state, strip_MessageException);
}
// 3.
void BM_B9_getrandom_try_block_fsn_Return(benchmark::State& state) {
    loop_getrandom_try_block_sfn(state, strip_Return);
}
// 4.
void BM_C1_getrandom_try_block_fsn_ErrorCode(benchmark::State& state) {
    std::function<int(bool)> fn = strip_ErrorCode;
    for (auto _ : state) {
        bool res = getRandom() == errorInt;
        auto err = fn(res);
        if (err < 0) {
        }
    }
}
// 5.
void BM_test31_exitWithErrorCode(benchmark::State& state) {
    for (auto _ : state) {
        auto err = pspdfkit_ErrorCode();
        if (err < 0) {
        }
    }
}

void BM_C6_vbools_pause_resume_sfn_BasicException(benchmark::State& state) {
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

void BM_C7_vbools_pause_resume_sfn_MessageException(benchmark::State& state) {
    loop_vbools_pause_resume_sfn(
        [](bool it) {
            try {
                if (it == true) {
                    throw std::runtime_error("Message");
                }
            } catch (std::runtime_error const& ex) {
            }
        },
        state);
}

void BM_C8_vbools_pause_resume_sfn_Return(benchmark::State& state) {
    loop_vbools_pause_resume_sfn(
        [](bool it) {
            if (it == true) {
                return;
            }
        },
        state);
}

void BM_C9_vbools_pause_resume_sfn_ErrorCode(benchmark::State& state) {
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
BENCHMARK(BM_00_A1_random);
BENCHMARK(BM_00_A5_vbools_global_index_access);
BENCHMARK(BM_00_A8_pspdfkit_BasicException);
BENCHMARK(BM_01_A9_pspdfkit_MessageException);
BENCHMARK(BM_02_B1_pspdfkit_Return);
BENCHMARK(BM_03_B2_pspdfkit_ErrorCode);
BENCHMARK(BM_04_C2_vbools_try_block_ptr_BasicException);
BENCHMARK(BM_05_C3_vbools_try_block_ptr_MessageException);
BENCHMARK(BM_06_C4_vbools_try_block_ptr_Return);
BENCHMARK(BM_07_C5_vbools_try_block_ptr_ErrorCode);
BENCHMARK(BM_08_C51_vbools_try_block_ptr_ErrorCode);
BENCHMARK(BM_A0_vbools_pause_resume_sfn);
BENCHMARK(BM_A2_pause_resume);
BENCHMARK(BM_A3_vbools_access_opt);
BENCHMARK(BM_A4_vbools_access);
BENCHMARK(BM_A6_std_function);
BENCHMARK(BM_A71_std_function_call_throw);
BENCHMARK(BM_A7_std_function_call);
BENCHMARK(BM_B3_getrandom_try_block_ptr_BasicException);
BENCHMARK(BM_B4_getrandom_try_block_ptr_MessageException);
BENCHMARK(BM_B5_getrandom_try_block_ptr_Return);
BENCHMARK(BM_B6_getrandom_try_block_ptr_ErrorCode);
BENCHMARK(BM_B7_getrandom_try_block_fsn_BasicException);
BENCHMARK(BM_B8_getrandom_try_block_fsn_MessageException);
BENCHMARK(BM_B9_getrandom_try_block_fsn_Return);
BENCHMARK(BM_C1_getrandom_try_block_fsn_ErrorCode);
BENCHMARK(BM_C6_vbools_pause_resume_sfn_BasicException);
BENCHMARK(BM_C7_vbools_pause_resume_sfn_MessageException);
BENCHMARK(BM_C8_vbools_pause_resume_sfn_Return);
BENCHMARK(BM_C9_vbools_pause_resume_sfn_ErrorCode);
BENCHMARK(BM_test21_exitWithErrorCode);
BENCHMARK(BM_test31_exitWithErrorCode);
// GEN_BENCHMARK_END
#endif

BENCHMARK_MAIN();
