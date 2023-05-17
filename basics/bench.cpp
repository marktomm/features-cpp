#include "lib.h"
#include <benchmark/benchmark.h>

using namespace basics;

struct SomeType {};

// GEN_PROTO_BEGIN
static void BM_00_User_Type_Cr_Dr_8b(benchmark::State& state);
static void BM_01_User_Type_Cr_Dr_16b(benchmark::State& state);
static void BM_02_User_Type_Cr_Dr_32b(benchmark::State& state);
static void BM_03_User_Type_Cr_Dr_512b(benchmark::State& state);
static void BM_10_User_Type_Cr_Dr_8b(benchmark::State& state);
static void BM_11_User_Type_Cr_Dr_16b(benchmark::State& state);
static void BM_12_User_Type_Cr_Dr_32b(benchmark::State& state);
static void BM_13_User_Type_Cr_Dr_512b(benchmark::State& state);
static void BM_20_User_Type_Cr_Dr_8b(benchmark::State& state);
static void BM_21_User_Type_Cr_Dr_16b(benchmark::State& state);
static void BM_22_User_Type_Cr_Dr_32b(benchmark::State& state);
static void BM_23_User_Type_Cr_Dr_512b(benchmark::State& state);
static void BM_X0_Set_Single_Register(benchmark::State& state);
static void BM_X1_Set_Single_Local_Int(benchmark::State& state);
// GEN_PROTO_END

static void BM_X0_Set_Single_Register(benchmark::State& state) {
    asm volatile("push %rdx");
    for (auto _ : state) {
        asm volatile("movl $324, %edx");
    }
    asm volatile("pop %rdx");
}

static void BM_X1_Set_Single_Local_Int(benchmark::State& state) {
    for (auto _ : state) {
        int x = 234;
        benchmark::DoNotOptimize(x);
    }
}

static void BM_00_User_Type_Cr_Dr_8b(benchmark::State& state) {
    for (auto _ : state) {
        A a;
        benchmark::DoNotOptimize(a);
    }
}

static void BM_01_User_Type_Cr_Dr_16b(benchmark::State& state) {
    for (auto _ : state) {
        A2 a;
        benchmark::DoNotOptimize(a.a);
    }
}

static void BM_02_User_Type_Cr_Dr_32b(benchmark::State& state) {
    for (auto _ : state) {
        A3 a;
        benchmark::DoNotOptimize(a.a);
    }
}

static void BM_03_User_Type_Cr_Dr_512b(benchmark::State& state) {
    for (auto _ : state) {
        A4 a;
        benchmark::DoNotOptimize(a.a[0]);
    }
}

static void BM_10_User_Type_Cr_Dr_8b(benchmark::State& state) {
    for (auto _ : state) {
        A a;
        benchmark::DoNotOptimize(a);
    }
}

static void BM_11_User_Type_Cr_Dr_16b(benchmark::State& state) {
    for (auto _ : state) {
        A2 a;
        benchmark::DoNotOptimize(a);
    }
}

static void BM_12_User_Type_Cr_Dr_32b(benchmark::State& state) {
    for (auto _ : state) {
        A3 a;
        benchmark::DoNotOptimize(a);
    }
}

static void BM_13_User_Type_Cr_Dr_512b(benchmark::State& state) {
    for (auto _ : state) {
        A4 a;
        benchmark::DoNotOptimize(a);
    }
}

static void BM_20_User_Type_Cr_Dr_8b(benchmark::State& state) {
    for (auto _ : state) {
        A a;
        doNotOptimize(&a);
    }
}

static void BM_21_User_Type_Cr_Dr_16b(benchmark::State& state) {
    for (auto _ : state) {
        A2 a;
        doNotOptimize(&a.a);
    }
}

static void BM_22_User_Type_Cr_Dr_32b(benchmark::State& state) {
    for (auto _ : state) {
        A3 a;
        doNotOptimize(&a.a);
    }
}

static void BM_23_User_Type_Cr_Dr_512b(benchmark::State& state) {
    for (auto _ : state) {
        A4 a;
        doNotOptimize(&a.a[0]);
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_User_Type_Cr_Dr_8b);
BENCHMARK(BM_01_User_Type_Cr_Dr_16b);
BENCHMARK(BM_02_User_Type_Cr_Dr_32b);
BENCHMARK(BM_03_User_Type_Cr_Dr_512b);
BENCHMARK(BM_10_User_Type_Cr_Dr_8b);
BENCHMARK(BM_11_User_Type_Cr_Dr_16b);
BENCHMARK(BM_12_User_Type_Cr_Dr_32b);
BENCHMARK(BM_13_User_Type_Cr_Dr_512b);
BENCHMARK(BM_20_User_Type_Cr_Dr_8b);
BENCHMARK(BM_21_User_Type_Cr_Dr_16b);
BENCHMARK(BM_22_User_Type_Cr_Dr_32b);
BENCHMARK(BM_23_User_Type_Cr_Dr_512b);
BENCHMARK(BM_X0_Set_Single_Register);
BENCHMARK(BM_X1_Set_Single_Local_Int);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();
