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
int getRandom();
int pspdfkit_ErrorCode();
int strip_ErrorCode(bool res);
void BM_01_vbools_pause_resume_sfn(benchmark::State& state);
void BM_A1_random(benchmark::State& state);
void BM_A2_pause_resume(benchmark::State& state);
void BM_A3_vbools_access_opt(benchmark::State& state);
void BM_A4_vbools_access(benchmark::State& state);
void BM_A5_vbools_global_index_access(benchmark::State& state);
void BM_A6_std_function(benchmark::State& state);
void BM_A71_std_function_call_throw(benchmark::State& state);
void BM_A7_std_function_call(benchmark::State& state);
void BM_A8_pspdfkit_BasicException(benchmark::State& state);
void BM_A9_pspdfkit_MessageException(benchmark::State& state);
void BM_B1_pspdfkit_Return(benchmark::State& state);
void BM_B2_pspdfkit_ErrorCode(benchmark::State& state);
void BM_B3_getrandom_try_block_ptr_BasicException(benchmark::State& state);
void BM_B4_getrandom_try_block_ptr_MessageException(benchmark::State& state);
void BM_B5_getrandom_try_block_ptr_Return(benchmark::State& state);
void BM_B6_getrandom_try_block_ptr_ErrorCode(benchmark::State& state);
void BM_B7_getrandom_try_block_fsn_BasicException(benchmark::State& state);
void BM_B8_getrandom_try_block_fsn_MessageException(benchmark::State& state);
void BM_B9_getrandom_try_block_fsn_Return(benchmark::State& state);
void BM_C1_getrandom_try_block_fsn_ErrorCode(benchmark::State& state);
void BM_C2_vbools_try_block_ptr_BasicException(benchmark::State& state);
void BM_C3_vbools_try_block_ptr_MessageException(benchmark::State& state);
void BM_C4_vbools_try_block_ptr_Return(benchmark::State& state);
void BM_C5_vbools_try_block_ptr_ErrorCode(benchmark::State& state);
void BM_C6_vbools_pause_resume_sfn_BasicException(benchmark::State& state);
void BM_C7_vbools_pause_resume_sfn_MessageException(benchmark::State& state);
void BM_C8_vbools_pause_resume_sfn_Return(benchmark::State& state);
void BM_C9_vbools_pause_resume_sfn_ErrorCode(benchmark::State& state);
void BM_test21_exitWithErrorCode(benchmark::State& state);
void BM_test31_exitWithErrorCode(benchmark::State& state);
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

// Initial base code taken from:
// https://pspdfkit.com/blog/2020/performance-overhead-of-exceptions-in-cpp/
// BEGIN

const int randomRange = 2; // Give me a number between 0 and 2.
const int errorInt = 0;    // Stop every time the number is 0.
int getRandom() { return static_cast<int>(random()) % randomRange; }

// 1.
void pspdfkit_BasicException() {
    if (getRandom() == errorInt) {
        throw -2;
    }
}
// 2.
void pspdfkit_MessageException() {
    if (getRandom() == errorInt) {
        throw std::runtime_error("Halt! Who goes there?");
    }
}
// 3.
void pspdfkit_Return() {
    if (getRandom() == errorInt) {
        return;
    }
}
// 4.
int pspdfkit_ErrorCode() {
    if (getRandom() == errorInt) {
        return -1;
    }
    return 0;
}

// 1.
void BM_A8_pspdfkit_BasicException(benchmark::State& state) {
    for (auto _ : state) {
        try {
            pspdfkit_BasicException();
        } catch (int ex) {
            // Caught! Carry on next iteration.
        }
    }
}
// 2.
void BM_A9_pspdfkit_MessageException(benchmark::State& state) {
    for (auto _ : state) {
        try {
            pspdfkit_MessageException();
        } catch (const std::runtime_error& ex) {
            // Caught! Carry on next iteration.
        }
    }
}
// 3.
void BM_B1_pspdfkit_Return(benchmark::State& state) {
    for (auto _ : state) {
        pspdfkit_Return();
    }
}
// 4.
void BM_B2_pspdfkit_ErrorCode(benchmark::State& state) {
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

std::vector<uint32_t> setup() {
    static bool setupDone = false;
    static std::vector<uint32_t> v(100);
    if (setupDone) {
        return v;
    }
    std::random_device rd;
    std::mt19937 generator(rd());
    std::generate(v.begin(), v.end(), [n = 0]() mutable { return n++; });
    std::shuffle(v.begin(), v.end(), generator);
    setupDone = true;
    return v;
}

std::vector<bool> GetRandomBools() {
    static bool randomDone = false;
    static std::vector<bool> bools(100);

    if (randomDone) {
        return bools;
    }
    auto v = setup();

    for (uint32_t i = 0; i < 50; ++i) {
        bools[v[i]] = true;
    }
    for (uint32_t i = 51; i < 100; ++i) {
        bools[v[i]] = false;
    }

    randomDone = true;
    return bools;
}

std::size_t GetNextGlobalIndex() {
    static std::size_t it = 0;
    return (++it == 100 ? it = 1 : it);
}

void loop_vbools_pause_resume_sfn(std::function<void(int)> callback,
                                  benchmark::State& state) {
    auto v = GetRandomBools();
    std::size_t it = 0;
    for (auto _ : state) {
        state.PauseTiming();
        ++it == 100 ? it = 1 : it;
        bool res = v[it];
        state.ResumeTiming();
        callback(res);
    }
}

void loop_pause_resume(benchmark::State& state) {
    auto v = GetRandomBools();
    for (auto _ : state) {
        state.PauseTiming();
        state.ResumeTiming();
    }
}

void loop_vbools_access_opt(benchmark::State& state) {
    auto v = GetRandomBools();
    std::size_t it = 0;
    for (auto _ : state) {
        ++it == 100 ? it = 1 : it;
        bool res = v[it];
        benchmark::DoNotOptimize(res);
    }
}

void loop_vbools_access_no_opt(benchmark::State& state) {
    auto v = GetRandomBools();
    std::size_t it = 0;
    for (auto _ : state) {
        ++it == 100 ? it = 1 : it;
        [[maybe_unused]] bool res = v[it];
    }
}

void loop_std_function(benchmark::State& state) {
    for (auto _ : state) {
        std::function<void(void)> fn = []() {};
    }
}

void loop_std_function_call(benchmark::State& state) {
    for (auto _ : state) {
        std::function<void(void)> fn = []() {};
        fn();
    }
}

void loop_std_function_call_throw(benchmark::State& state) {
    for (auto _ : state) {
        try {
            std::function<void(void)> fn = []() {};
            fn();
            throw 0;
        } catch (int x) {
        }
    }
}

void loop_vbools_global_index_access_no_opt(benchmark::State& state) {
    auto v = GetRandomBools();
    std::size_t it = 0;
    for (auto _ : state) {
        it = GetNextGlobalIndex();
        [[maybe_unused]] bool res = v[it];
    }
}

void loop_random(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(getRandom() == errorInt);
    }
}

// 1. == strip_BasicException
void strip_BasicException(bool res) {
    if (res) {
        throw -2;
    }
}
// 2.
void strip_MessageException(bool res) {
    if (res) {
        throw std::runtime_error("Message");
    }
}
// 3.
void strip_Return(bool res) {
    if (res) {
        return;
    }
}
// 4.
int strip_ErrorCode(bool res) {
    if (res) {
        return -1;
    }
    return 0;
}

void loop_getrandom_try_block_ptr(benchmark::State& state,
                                  void (*callback)(bool)) {

    for (auto _ : state) {
        bool res = getRandom() == errorInt;
        try {
            callback(res);
        } catch (int ex) {
        } catch (const std::runtime_error& ex) {
        }
    }
}

void loop_getrandom_try_block_sfn(benchmark::State& state,
                                  std::function<void(bool)> callback) {

    for (auto _ : state) {
        bool res = getRandom() == errorInt;
        try {
            callback(res);
        } catch (int ex) {
        } catch (const std::runtime_error& ex) {
        }
    }
}

void loop_vbools_try_block_ptr(benchmark::State& state,
                               void (*callback)(bool)) {

    auto v = GetRandomBools();
    for (auto _ : state) {
        auto it = GetNextGlobalIndex();
        bool res = v[it];
        try {
            callback(res);
        } catch (int ex) {
            // Caught! Carry on next iteration.
        } catch (const std::runtime_error& ex) {
            // Caught! Carry on next iteration.
        }
    }
}

void BM_01_vbools_pause_resume_sfn(benchmark::State& state) {
    loop_vbools_pause_resume_sfn([](int) {}, state);
}

void BM_A1_random(benchmark::State& state) { loop_random(state); }

void BM_A2_pause_resume(benchmark::State& state) { loop_pause_resume(state); }

void BM_A3_vbools_access_opt(benchmark::State& state) {
    loop_vbools_access_opt(state);
}

void BM_A4_vbools_access(benchmark::State& state) {
    loop_vbools_access_no_opt(state);
}

void BM_A5_vbools_global_index_access(benchmark::State& state) {
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
void BM_C2_vbools_try_block_ptr_BasicException(benchmark::State& state) {
    loop_vbools_try_block_ptr(state, strip_BasicException);
}
// 2.
void BM_C3_vbools_try_block_ptr_MessageException(benchmark::State& state) {
    loop_vbools_try_block_ptr(state, strip_MessageException);
}
// 3.
void BM_C4_vbools_try_block_ptr_Return(benchmark::State& state) {
    loop_vbools_try_block_ptr(state, strip_Return);
}
// 4.
void BM_C5_vbools_try_block_ptr_ErrorCode(benchmark::State& state) {
    auto v = GetRandomBools();
    for (auto _ : state) {
        auto it = GetNextGlobalIndex();
        bool res = v[it];
        auto err = strip_ErrorCode(res);
        if (err < 0) {
            // `handle_error()` ...
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
BENCHMARK(BM_01_vbools_pause_resume_sfn);
BENCHMARK(BM_A1_random);
BENCHMARK(BM_A2_pause_resume);
BENCHMARK(BM_A3_vbools_access_opt);
BENCHMARK(BM_A4_vbools_access);
BENCHMARK(BM_A5_vbools_global_index_access);
BENCHMARK(BM_A6_std_function);
BENCHMARK(BM_A71_std_function_call_throw);
BENCHMARK(BM_A7_std_function_call);
BENCHMARK(BM_A8_pspdfkit_BasicException);
BENCHMARK(BM_A9_pspdfkit_MessageException);
BENCHMARK(BM_B1_pspdfkit_Return);
BENCHMARK(BM_B2_pspdfkit_ErrorCode);
BENCHMARK(BM_B3_getrandom_try_block_ptr_BasicException);
BENCHMARK(BM_B4_getrandom_try_block_ptr_MessageException);
BENCHMARK(BM_B5_getrandom_try_block_ptr_Return);
BENCHMARK(BM_B6_getrandom_try_block_ptr_ErrorCode);
BENCHMARK(BM_B7_getrandom_try_block_fsn_BasicException);
BENCHMARK(BM_B8_getrandom_try_block_fsn_MessageException);
BENCHMARK(BM_B9_getrandom_try_block_fsn_Return);
BENCHMARK(BM_C1_getrandom_try_block_fsn_ErrorCode);
BENCHMARK(BM_C2_vbools_try_block_ptr_BasicException);
BENCHMARK(BM_C3_vbools_try_block_ptr_MessageException);
BENCHMARK(BM_C4_vbools_try_block_ptr_Return);
BENCHMARK(BM_C5_vbools_try_block_ptr_ErrorCode);
BENCHMARK(BM_C6_vbools_pause_resume_sfn_BasicException);
BENCHMARK(BM_C7_vbools_pause_resume_sfn_MessageException);
BENCHMARK(BM_C8_vbools_pause_resume_sfn_Return);
BENCHMARK(BM_C9_vbools_pause_resume_sfn_ErrorCode);
BENCHMARK(BM_test21_exitWithErrorCode);
BENCHMARK(BM_test31_exitWithErrorCode);
// GEN_BENCHMARK_END
#endif

BENCHMARK_MAIN();
