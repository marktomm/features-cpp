#include "lib.h"
#include <benchmark/benchmark.h>

#include <memory>
#include <utility>

using namespace lambda_fns;
using namespace std;

// GEN_PROTO_BEGIN
static void BM_00_LargeObjLambda(benchmark::State& state);
static void BM_01_LargeObjLambdaOpt(benchmark::State& state);
static void BM_02_LargeObj(benchmark::State& state);
static void BM_03_LargeObjOpt(benchmark::State& state);
static void BM_A1_SmallLambda(benchmark::State& state);
static void BM_A2_LargeObjLambdaCall(benchmark::State& state);
static void BM_A2_LargeObjLambdaCallRef(benchmark::State& state);
void large_obj();
void large_obj_lambda();
void large_obj_lambda_call();
void large_obj_lambda_call_ref(LargeObject& obj);
void large_obj_lambda_opt();
void large_obj_opt();
void small_lambda();
// GEN_PROTO_END

void small_lambda() {
    SmallObject obj;
    auto lambda = [obj]() { [[maybe_unused]] auto ptr = &obj; };
    lambda();
}

void large_obj_lambda_call_ref(LargeObject& obj) {
    auto lambda = [obj]() mutable { [[maybe_unused]] auto ptr = &obj; };
    lambda();
}

void large_obj_lambda_call() {
    LargeObject obj;
    auto lambda = [obj]() mutable { [[maybe_unused]] auto ptr = &obj; };
    lambda();
}

void large_obj_lambda() {
    LargeObject obj;
    [[maybe_unused]] auto lambda = [obj]() mutable {
        [[maybe_unused]] auto ptr = &obj;
    };
}

void large_obj_lambda_opt() {
    LargeObject obj;
    [[maybe_unused]] auto lambda = [obj]() mutable {
        [[maybe_unused]] auto ptr = &obj;
    };
    benchmark::DoNotOptimize(obj);
    benchmark::DoNotOptimize(lambda);
}

void large_obj() { [[maybe_unused]] LargeObject obj; }

void large_obj_opt() {
    LargeObject obj;
    benchmark::DoNotOptimize(obj);
}

static void BM_A1_SmallLambda(benchmark::State& state) {
    for (auto _ : state) {
        small_lambda();
    }
}

static void BM_A2_LargeObjLambdaCallRef(benchmark::State& state) {
    LargeObject obj;
    for (auto _ : state) {
        large_obj_lambda_call_ref(obj);
    }
}

static void BM_A2_LargeObjLambdaCall(benchmark::State& state) {
    for (auto _ : state) {
        large_obj_lambda_call();
    }
}

static void BM_00_LargeObjLambda(benchmark::State& state) {
    for (auto _ : state) {
        large_obj_lambda();
    }
}

static void BM_01_LargeObjLambdaOpt(benchmark::State& state) {
    for (auto _ : state) {
        large_obj_lambda_opt();
    }
}

static void BM_02_LargeObj(benchmark::State& state) {
    for (auto _ : state) {
        large_obj();
    }
}

static void BM_03_LargeObjOpt(benchmark::State& state) {
    for (auto _ : state) {
        large_obj_opt();
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_LargeObjLambda);
BENCHMARK(BM_01_LargeObjLambdaOpt);
BENCHMARK(BM_02_LargeObj);
BENCHMARK(BM_03_LargeObjOpt);
BENCHMARK(BM_A1_SmallLambda);
BENCHMARK(BM_A2_LargeObjLambdaCall);
BENCHMARK(BM_A2_LargeObjLambdaCallRef);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();
