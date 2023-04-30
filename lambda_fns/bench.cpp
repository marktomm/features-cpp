#include "lib.h"
#include <benchmark/benchmark.h>

#include <memory>
#include <utility>

using namespace lambda_fns;
using namespace std;

// GEN_PROTO_BEGIN
static void BM_00_LargeObj(benchmark::State& state);
static void BM_01_LargeObjOpt(benchmark::State& state);
static void BM_02_LargeObjLambda(benchmark::State& state);
static void BM_03_LargeObjLambdaOpt(benchmark::State& state);
static void BM_04_LargeObjLambdaRef(benchmark::State& state);
static void BM_05_LargeObjLambdaOptRef(benchmark::State& state);
static void BM_06_LargeObjLambdaCall(benchmark::State& state);
static void BM_07_LargeObjLambdaCallRef(benchmark::State& state);
static void BM_10_SmallObj(benchmark::State& state);
static void BM_11_SmallObjOpt(benchmark::State& state);
static void BM_12_SmallObjLambda(benchmark::State& state);
static void BM_13_SmallObjLambdaOpt(benchmark::State& state);
static void BM_14_SmallObjLambdaRef(benchmark::State& state);
static void BM_15_SmallObjLambdaOptRef(benchmark::State& state);
static void BM_16_SmallObjLambdaCall(benchmark::State& state);
static void BM_17_SmallObjLambdaCallRef(benchmark::State& state);
// GEN_PROTO_END

static void BM_17_SmallObjLambdaCallRef(benchmark::State& state) {
    SmallObject obj;
    for (auto _ : state) {
        small_obj_lambda_call_ref(obj);
    }
}

static void BM_16_SmallObjLambdaCall(benchmark::State& state) {
    for (auto _ : state) {
        small_obj_lambda_call();
    }
}

static void BM_10_SmallObj(benchmark::State& state) {
    for (auto _ : state) {
        small_obj();
    }
}

static void BM_11_SmallObjOpt(benchmark::State& state) {
    for (auto _ : state) {
        small_obj_opt();
    }
}

static void BM_12_SmallObjLambda(benchmark::State& state) {
    for (auto _ : state) {
        small_obj_lambda();
    }
}

static void BM_13_SmallObjLambdaOpt(benchmark::State& state) {
    for (auto _ : state) {
        small_obj_lambda_opt();
    }
}

static void BM_14_SmallObjLambdaRef(benchmark::State& state) {
    SmallObject obj;
    for (auto _ : state) {
        small_obj_lambda_ref(obj);
    }
}

static void BM_15_SmallObjLambdaOptRef(benchmark::State& state) {
    SmallObject obj;
    for (auto _ : state) {
        small_obj_lambda_opt_ref(obj);
    }
}

static void BM_07_LargeObjLambdaCallRef(benchmark::State& state) {
    LargeObject obj;
    for (auto _ : state) {
        large_obj_lambda_call_ref(obj);
    }
}

static void BM_06_LargeObjLambdaCall(benchmark::State& state) {
    for (auto _ : state) {
        large_obj_lambda_call();
    }
}

static void BM_00_LargeObj(benchmark::State& state) {
    for (auto _ : state) {
        large_obj();
    }
}

static void BM_01_LargeObjOpt(benchmark::State& state) {
    for (auto _ : state) {
        large_obj_opt();
    }
}

static void BM_02_LargeObjLambda(benchmark::State& state) {
    for (auto _ : state) {
        large_obj_lambda();
    }
}

static void BM_03_LargeObjLambdaOpt(benchmark::State& state) {
    for (auto _ : state) {
        large_obj_lambda_opt();
    }
}

static void BM_04_LargeObjLambdaRef(benchmark::State& state) {
    LargeObject obj;
    for (auto _ : state) {
        large_obj_lambda_ref(obj);
    }
}

static void BM_05_LargeObjLambdaOptRef(benchmark::State& state) {
    LargeObject obj;
    for (auto _ : state) {
        large_obj_lambda_opt_ref(obj);
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_LargeObj);
BENCHMARK(BM_01_LargeObjOpt);
BENCHMARK(BM_02_LargeObjLambda);
BENCHMARK(BM_03_LargeObjLambdaOpt);
BENCHMARK(BM_04_LargeObjLambdaRef);
BENCHMARK(BM_05_LargeObjLambdaOptRef);
BENCHMARK(BM_06_LargeObjLambdaCall);
BENCHMARK(BM_07_LargeObjLambdaCallRef);
BENCHMARK(BM_10_SmallObj);
BENCHMARK(BM_11_SmallObjOpt);
BENCHMARK(BM_12_SmallObjLambda);
BENCHMARK(BM_13_SmallObjLambdaOpt);
BENCHMARK(BM_14_SmallObjLambdaRef);
BENCHMARK(BM_15_SmallObjLambdaOptRef);
BENCHMARK(BM_16_SmallObjLambdaCall);
BENCHMARK(BM_17_SmallObjLambdaCallRef);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();
