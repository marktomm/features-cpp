#include "lib.h"
#include <benchmark/benchmark.h>

#include <utility>

using namespace trivial_type;
using namespace std;

// GEN_PROTO_BEGIN
static void BM_00_Ptr_Ctor_Dtor(benchmark::State& state);
static void BM_02_Ptr_Ctor_Dtor_Fn_Escape(benchmark::State& state);
static void BM_A0_Up_Ctor_Dtor(benchmark::State& state);
static void BM_A2_Up_Ctor_Dtor_Fn_Escape(benchmark::State& state);
static void BM_XX_Ptr_Ctor_Dtor_Fn_Noop(benchmark::State& state);
static void BM_XX_Ptr_Ctor_Dtor_Fn_Ret(benchmark::State& state);
static void BM_XX_Up_Ctor_Dtor_Fn_Noop(benchmark::State& state);
static void BM_XX_Up_Ctor_Dtor_Fn_Ret(benchmark::State& state);
// GEN_PROTO_END

static void BM_00_Ptr_Ctor_Dtor(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        benchmark::DoNotOptimize(ptr);
        delete ptr;
    }
}

static void BM_XX_Ptr_Ctor_Dtor_Fn_Noop(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        FnNoop(ptr);
        benchmark::DoNotOptimize(ptr);
        delete ptr;
    }
}

static void BM_02_Ptr_Ctor_Dtor_Fn_Escape(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        FnEscape(ptr);
        benchmark::DoNotOptimize(ptr);
        delete ptr;
    }
}

static void BM_XX_Ptr_Ctor_Dtor_Fn_Ret(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        int x = TestFunction(ptr);
        benchmark::DoNotOptimize(ptr);
        benchmark::DoNotOptimize(x);
        delete ptr;
    }
}

static void BM_A0_Up_Ctor_Dtor(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
    }
}

static void BM_XX_Up_Ctor_Dtor_Fn_Noop(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
        FnNoop(move(ptr));
    }
}

static void BM_A2_Up_Ctor_Dtor_Fn_Escape(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
        FnEscape(move(ptr));
    }
}

static void BM_XX_Up_Ctor_Dtor_Fn_Ret(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
        int x = TestFunction(move(ptr));
        benchmark::DoNotOptimize(x);
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_Ptr_Ctor_Dtor);
BENCHMARK(BM_02_Ptr_Ctor_Dtor_Fn_Escape);
BENCHMARK(BM_A0_Up_Ctor_Dtor);
BENCHMARK(BM_A2_Up_Ctor_Dtor_Fn_Escape);
BENCHMARK(BM_XX_Ptr_Ctor_Dtor_Fn_Noop);
BENCHMARK(BM_XX_Ptr_Ctor_Dtor_Fn_Ret);
BENCHMARK(BM_XX_Up_Ctor_Dtor_Fn_Noop);
BENCHMARK(BM_XX_Up_Ctor_Dtor_Fn_Ret);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();
