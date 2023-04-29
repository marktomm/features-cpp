#include <benchmark/benchmark.h>

#include "lib.h"

#include <iostream>

using namespace rvo;

// GEN_PROTO_BEGIN
LargeObject return_by_value_no_rvo(const LargeObject& obj);
LargeObject return_by_value_rvo();
static void BM_ReturnByValue(benchmark::State& state);
static void BM_ReturnByValueRVO(benchmark::State& state);
// GEN_PROTO_END

// Function that returns by value
LargeObject return_by_value_no_rvo(const LargeObject& obj) { return obj; }

// Function that returns by value with RVO in C++17
LargeObject return_by_value_rvo() {
    LargeObject obj;
    return obj; // RVO will occur in C++17
}

static void BM_ReturnByValue(benchmark::State& state) {
    for (auto _ : state) {
        LargeObject obj;
        obj = return_by_value_no_rvo(obj);
        benchmark::DoNotOptimize(obj);
    }
}

static void BM_ReturnByValueRVO(benchmark::State& state) {
    for (auto _ : state) {
        LargeObject obj = return_by_value_rvo();
        benchmark::DoNotOptimize(obj);
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_ReturnByValue);
BENCHMARK(BM_ReturnByValueRVO);
// GEN_BENCHMARK_END

BENCHMARK_MAIN();
