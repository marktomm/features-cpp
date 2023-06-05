#include "lib.h"
#include <atomic>
#include <benchmark/benchmark.h>

#include <utility>

using namespace trivial_type;
using namespace std;

// GEN_PROTO_BEGIN
static void BM_00_Ptr_Cr_Dr(benchmark::State& state);
static void BM_02_Ptr_Cr_Dr_Fn(benchmark::State& state);
static void BM_03_Ptr_Cr_Dr_Fn_Ret(benchmark::State& state);
static void BM_A0_Up_Cr_Dr(benchmark::State& state);
static void BM_A2_Up_Cr_Dr_Fn(benchmark::State& state);
static void BM_A3_Up_Cr_Dr_Fn_Ret(benchmark::State& state);
static void BM_C0_Ptr_Cr_Dr_Rr1(benchmark::State& state);
static void BM_C4_Stack_Cr_Dr(benchmark::State& state);
static void BM_C5_Stack_Cr_Dr_Fn(benchmark::State& state);
static void BM_C6_Stack_Cr_Dr_Fn_Ret(benchmark::State& state);
static void BM_GG_New_4b(benchmark::State& state);
static void BM_S0_Ptr_Fn(benchmark::State& state);
static void BM_S1_Up_Fn(benchmark::State& state);
static void BM_S3_Ptr_Deref(benchmark::State& state);
static void BM_S4_Up_Deref(benchmark::State& state);
static void BM_XX_Ptr_Cr_Dr_Fn_Noop(benchmark::State& state);
static void BM_XX_Ptr_Cr_Dr_Fn_Ret(benchmark::State& state);
static void BM_XX_Up_Cr_Dr_Fn_Noop(benchmark::State& state);
static void BM_XX_Up_Cr_Dr_Fn_Ret(benchmark::State& state);
// GEN_PROTO_END

static void BM_GG_New_4b(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(new int{});
    }
}

static void BM_C0_Ptr_Cr_Dr_Rr1(benchmark::State& state) {
    auto bytes = state.range(0);
    for (auto _ : state) {
        char* ptr = new char[static_cast<uint64_t>(bytes)];
        benchmark::DoNotOptimize(ptr);
        delete[] ptr;
    }
}

static void BM_00_Ptr_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        benchmark::DoNotOptimize(ptr);
        delete ptr;
    }
}

static void BM_02_Ptr_Cr_Dr_Fn(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        FnEscape(ptr);
        benchmark::DoNotOptimize(ptr);
        delete ptr;
    }
}

static void BM_03_Ptr_Cr_Dr_Fn_Ret(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        auto x = FnRet(ptr);
        benchmark::DoNotOptimize(ptr);
        benchmark::DoNotOptimize(x);
        delete ptr;
    }
}

static void BM_C4_Stack_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        int value = 0;
        benchmark::DoNotOptimize(value);
    }
}

static void BM_C5_Stack_Cr_Dr_Fn(benchmark::State& state) {
    for (auto _ : state) {
        int value = 0;
        FnEscape(&value);
        benchmark::DoNotOptimize(value);
    }
}

static void BM_C6_Stack_Cr_Dr_Fn_Ret(benchmark::State& state) {
    for (auto _ : state) {
        int value = 0;
        auto x = FnRet(&value);
        benchmark::DoNotOptimize(value);
        benchmark::DoNotOptimize(x);
    }
}

static void BM_A0_Up_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
    }
}

static void BM_A2_Up_Cr_Dr_Fn(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
        FnEscape(move(ptr));
    }
}

static void BM_A3_Up_Cr_Dr_Fn_Ret(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
        auto x = FnRet(move(ptr));
        benchmark::DoNotOptimize(x);
    }
}

static void BM_S0_Ptr_Fn(benchmark::State& state) {
    int* ptr = new int{};
    for (auto _ : state) {
        FnEscape(ptr);
    }
    benchmark::DoNotOptimize(ptr);
    delete ptr;
}

static void BM_S1_Up_Fn(benchmark::State& state) {
    auto ptr = unique_ptr<int>{new int{}};
    for (auto _ : state) {
        asm volatile("4:");
        FnEscape(ptr.get());
        asm volatile("5:");
    }
    benchmark::DoNotOptimize(ptr.get());
}

static void BM_S3_Ptr_Deref(benchmark::State& state) {
    int* ptr = new int{};
    for (auto _ : state) {
        asm volatile("6:");
        auto x = *ptr;
        benchmark::DoNotOptimize(&x);
        asm volatile("7:");
    }
    benchmark::DoNotOptimize(ptr);
    delete ptr;
}

static void BM_S4_Up_Deref(benchmark::State& state) {
    auto ptr = unique_ptr<int>{new int{}};
    for (auto _ : state) {
        asm volatile("4:");
        auto& x = *ptr;
        benchmark::DoNotOptimize(x);
        asm volatile("5:");
    }
    benchmark::DoNotOptimize(ptr.get());
}

static void BM_XX_Up_Cr_Dr_Fn_Ret(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
        int x = TestFunction(move(ptr));
        benchmark::DoNotOptimize(x);
    }
}

static void BM_XX_Ptr_Cr_Dr_Fn_Noop(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        FnNoop(ptr);
        benchmark::DoNotOptimize(ptr);
        delete ptr;
    }
}

static void BM_XX_Up_Cr_Dr_Fn_Noop(benchmark::State& state) {
    for (auto _ : state) {
        auto ptr = unique_ptr<int>{new int{}};
        benchmark::DoNotOptimize(ptr.get());
        FnNoop(move(ptr));
    }
}

static void BM_XX_Ptr_Cr_Dr_Fn_Ret(benchmark::State& state) {
    for (auto _ : state) {
        int* ptr = new int{};
        int x = TestFunction(ptr);
        benchmark::DoNotOptimize(ptr);
        benchmark::DoNotOptimize(x);
        delete ptr;
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_Ptr_Cr_Dr);
BENCHMARK(BM_02_Ptr_Cr_Dr_Fn);
BENCHMARK(BM_03_Ptr_Cr_Dr_Fn_Ret);
BENCHMARK(BM_A0_Up_Cr_Dr);
BENCHMARK(BM_A2_Up_Cr_Dr_Fn);
BENCHMARK(BM_A3_Up_Cr_Dr_Fn_Ret);
BENCHMARK(BM_C0_Ptr_Cr_Dr_Rr1)->RangeMultiplier(2)->Range(4, 512);
BENCHMARK(BM_C4_Stack_Cr_Dr);
BENCHMARK(BM_C5_Stack_Cr_Dr_Fn);
BENCHMARK(BM_C6_Stack_Cr_Dr_Fn_Ret);
BENCHMARK(BM_GG_New_4b);
BENCHMARK(BM_S0_Ptr_Fn);
BENCHMARK(BM_S1_Up_Fn);
BENCHMARK(BM_S3_Ptr_Deref);
BENCHMARK(BM_S4_Up_Deref);
BENCHMARK(BM_XX_Ptr_Cr_Dr_Fn_Noop);
BENCHMARK(BM_XX_Ptr_Cr_Dr_Fn_Ret);
BENCHMARK(BM_XX_Up_Cr_Dr_Fn_Noop);
BENCHMARK(BM_XX_Up_Cr_Dr_Fn_Ret);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();
