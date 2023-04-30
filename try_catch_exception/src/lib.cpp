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
// x.
int strip_ErrorCodeVbools(std::vector<bool> const& v) {
    auto it = GetNextGlobalIndex();
    bool res = v[it];
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
        } catch (const std::runtime_error& ex) {
        }
    }
}

} // namespace try_catch_exception
