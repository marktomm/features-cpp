#include <benchmark/benchmark.h>

#include "lib.h"

#include <algorithm>
#include <random>
#include <stdexcept>

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
    for (uint32_t i = 0; i < 50; ++i) {
        bools[v[i]] = false;
    }

    randomDone = true;
    return bools;
}

void BM_ExitWithBasicException(benchmark::State& state) {
    for (auto _ : state) {
        for (auto it : GetRandomBools()) {
            try {
                if (it == true) {
                    throw 0;
                }
            } catch (int ex) {
            }
            benchmark::DoNotOptimize(it);
        }
    }
}

void BM_ExitWithMessageException(benchmark::State& state) {
    for (auto _ : state) {
        for (auto it : GetRandomBools()) {
            try {
                if (it == true) {
                    throw std::runtime_error("Message");
                }
            } catch (std::runtime_error const& ex) {
            }
            benchmark::DoNotOptimize(it);
        }
    }
}

void BM_ExitWithReturn(benchmark::State& state) {
    for (auto _ : state) {
        for (auto it : GetRandomBools()) {
            if (it == true) {
                return;
            }
            benchmark::DoNotOptimize(it);
        }
    }
}

void BM_ExitWithErrorCode(benchmark::State& state) {
    for (auto _ : state) {
        for (auto it : GetRandomBools()) {
            auto err = it;
            if (err == true) {
                int x = 0;
                benchmark::DoNotOptimize(x);
            }
            benchmark::DoNotOptimize(err);
        }
    }
}

BENCHMARK(BM_ExitWithBasicException);
BENCHMARK(BM_ExitWithMessageException);
BENCHMARK(BM_ExitWithReturn);
BENCHMARK(BM_ExitWithErrorCode);

BENCHMARK_MAIN();
