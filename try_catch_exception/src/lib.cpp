#include "lib.h"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <random>
#include <stdexcept>

namespace try_catch_exception {

// Initial base code taken from:
// https://pspdfkit.com/blog/2020/performance-overhead-of-exceptions-in-cpp/
// BEGIN

const int randomRange12 = 2; // Give me a number between 0 and 2.
const int errorInt = 0;      // Stop every time the number is 0.
int getRand12() { return static_cast<int>(random()) % randomRange12; }
const int randomRange13 = 2; // Give me a number between 0 and 2.
int getRand13() { return static_cast<int>(random()) % randomRange13; }

// 1.
void pspdfkit_BasicEx() {
    if (getRand13() == errorInt) {
        throw -2;
    }
}
// 2.
void pspdfkit_MessageEx() {
    if (getRand13() == errorInt) {
        throw std::runtime_error("Halt! Who goes there?");
    }
}
// 3.
void Return_33p() {
    if (getRand13() == errorInt) {
        return;
    }
}
// 4.
int ErrCode_33p() {
    if (getRand13() == errorInt) {
        return -1;
    }
    return 0;
}
// END
// 1.
void ExBasic_50p() {
    if (getRand12() == errorInt) {
        throw -2;
    }
}
// 2.
void ExMessage_50p() {
    if (getRand12() == errorInt) {
        throw std::runtime_error("Halt! Who goes there?");
    }
}
// 3.
void Return_50p() {
    if (getRand12() == errorInt) {
        return;
    }
}
// 4.
int ErrCode_50p() {
    if (getRand12() == errorInt) {
        return -1;
    }
    return 0;
}

void loop_random50(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(getRand12() == errorInt);
    }
}

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

std::vector<bool> GetRandBools() {
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

void loop_vbools_pause_resume_sfn(ci callback, benchmark::State& state) {
    auto v = GetRandBools();
    std::size_t it = 0;
    for (auto _ : state) {
        state.PauseTiming();
        ++it == 100 ? it = 1 : it;
        auto res = v[it];
        state.ResumeTiming();
        callback(res);
    }
}

void loop_pause_resume(benchmark::State& state) {
    auto v = GetRandBools();
    for (auto _ : state) {
        state.PauseTiming();
        state.ResumeTiming();
    }
}

void loop_VecRand_Local_Idx(benchmark::State& state) {
    auto v = GetRandBools();
    std::size_t it = 0;
    for (auto _ : state) {
        ++it == 100 ? it = 1 : it;
        auto res = v[it];
        benchmark::DoNotOptimize(res);
    }
}

void loop_VecRand_Local_Idx_Opt(benchmark::State& state) {
    auto v = GetRandBools();
    std::size_t it = 0;
    for (auto _ : state) {
        ++it == 100 ? it = 1 : it;
        [[maybe_unused]] auto res = v[it];
    }
}

void loop_StdFn_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        std::function<void(void)> fn = []() {};
        benchmark::DoNotOptimize(fn);
    }
}

void loop_StdFn_Call(benchmark::State& state) {
    std::function<int(void)> fn = []() -> int { return 2; };
    for (auto _ : state) {
        benchmark::DoNotOptimize(fn);
        benchmark::DoNotOptimize(fn());
    }
}

void loop_StdFn_Call_throw(benchmark::State& state) {
    for (auto _ : state) {
        try {
            std::function<int(void)> fn = []() -> int { return 2; };
            benchmark::DoNotOptimize(fn());
            throw 0;
        } catch (int x) {
        }
    }
}

void loop_VecRand_Global_Idx(benchmark::State& state) {
    auto v = GetRandBools();
    std::size_t it = 0;
    for (auto _ : state) {
        it = GetNextGlobalIndex();
        [[maybe_unused]] auto res = v[it];
        benchmark::DoNotOptimize(it);
        benchmark::DoNotOptimize(res);
    }
}

void loop_random(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(getRand13() == errorInt);
    }
}

// 1. == strip_BasicEx
void strip_BasicEx(bool res) {
    if (res) {
        throw -2;
    }
}
// 2.
void strip_MessageEx(bool res) {
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
int ErrCode_Arg(bool res) {
    if (res) {
        return -1;
    }
    return 0;
}
// x.
int ErrCode_Vec_Rand(std::vector<bool> const& v) {
    auto it = GetNextGlobalIndex();
    auto res = v[it];
    if (res) {
        return -1;
    }
    return 0;
}

void fnx1() {
    auto res = getRand13() == errorInt;
    auto err = ErrCode_Arg(res);
    if (err < 0) {
    }
}

void loop_Rand_33p_Cb_Arg(benchmark::State& state, cf callback) {

    for (auto _ : state) {
        auto res = getRand13() == errorInt;
        try {
            callback(res);
        } catch (int ex) {
        } catch (const std::runtime_error& ex) {
        }
    }
}

void loop_Rand_50p_Cb_Arg(benchmark::State& state, cf callback) {

    for (auto _ : state) {
        auto res = getRand12() == errorInt;
        try {
            callback(res);
        } catch (int ex) {
        } catch (const std::runtime_error& ex) {
        }
    }
}

void fnx2(std::function<int(bool)> fn) {

    auto res = getRand13() == errorInt;
    auto err = fn(res);
    if (err < 0) {
    }
}

void loop_VecRand_Cb_Arg(benchmark::State& state, cb callback) {

    auto v = GetRandBools();
    for (auto _ : state) {
        auto it = GetNextGlobalIndex();
        auto res = v[it];
        try {
            callback(res);
        } catch (int ex) {
        } catch (const std::runtime_error& ex) {
        }
    }
}

} // namespace try_catch_exception
