#include "lib.h"

#include <benchmark/benchmark.h>

#include <cstddef>
#include <random>
#include <vector>

using namespace poly;

// GEN_PROTO_BEGIN
static void BM_00_Regular_Base_Cr_Dr(benchmark::State& state);
static void BM_01_Regular_Drv_Cr_Dr(benchmark::State& state);
static void BM_03_Virt_Drv_Cr_Dr(benchmark::State& state);
static void BM_04_Regular_Base_Call(benchmark::State& state);
static void BM_05_Regular_Drv_Call(benchmark::State& state);
static void BM_07_Virt_Base_Call(benchmark::State& state);
static void BM_08_Virt_Drv_Call(benchmark::State& state);
static void BM_09_Virt_Random_Call(benchmark::State& state);
static void BM_F0_VirtA_Drv_Cr_Dr(benchmark::State& state);
static void BM_F1_VirtA_Base_Call(benchmark::State& state);
static void BM_F2_VirtA_Drv_Call(benchmark::State& state);
static void BM_F3_Virt_Same_Call(benchmark::State& state);
static void BM_F4_Virt_Int_Call(benchmark::State& state);
// GEN_PROTO_END

static void BM_00_Regular_Base_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        nonVA a;
        benchmark::DoNotOptimize(&a);
    }
}

static void BM_01_Regular_Drv_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        nonVD d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_F0_VirtA_Drv_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        Dx d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_03_Virt_Drv_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        D d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_04_Regular_Base_Call(benchmark::State& state) {
    nonVA a;
    for (auto _ : state) {
        a.Fn();
        benchmark::DoNotOptimize(&a);
    }
}

static void BM_05_Regular_Drv_Call(benchmark::State& state) {
    nonVD d;
    for (auto _ : state) {
        d.Fn();
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_F1_VirtA_Base_Call(benchmark::State& state) {
    Ax d;
    for (auto _ : state) {
        d.Fn();
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_F2_VirtA_Drv_Call(benchmark::State& state) {
    Dx d;
    for (auto _ : state) {
        d.Fn();
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_07_Virt_Base_Call(benchmark::State& state) {
    D d;
    A* ptr = &d;
    for (auto _ : state) {
        ptr->PureVFn();
        benchmark::DoNotOptimize(ptr);
    }
}

static void BM_08_Virt_Drv_Call(benchmark::State& state) {
    D d;
    D* ptr = &d;
    for (auto _ : state) {
        ptr->PureVFn();
        benchmark::DoNotOptimize(ptr);
    }
}

static void BM_09_Virt_Random_Call(benchmark::State& state) {
    // Create a container with random instances of derived classes
    std::vector<A*> container;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 3);

    for (int i = 0; i < 1000; ++i) {
        int random_value = distr(gen);
        switch (random_value) {
        case 1:
            container.push_back(new D);
            break;
        case 2:
            container.push_back(new E);
            break;
        case 3:
            container.push_back(new F);
            break;
        }
    }

    std::uniform_int_distribution<> distr2(0, 999);
    int random_value2 = distr2(gen);

    // Benchmark the virtual calls
    for (auto _ : state) {
        container[static_cast<std::size_t>(random_value2)]->PureVFn();
    }
    benchmark::DoNotOptimize(container.data());

    // Clean up memory
    for (auto* ptr : container) {
        delete ptr;
    }
}

static void BM_F3_Virt_Same_Call(benchmark::State& state) {
    // Create a container with random instances of derived classes
    std::vector<A*> container;

    for (int i = 0; i < 1000; ++i) {
        container.push_back(new D);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr2(0, 999);
    int random_value2 = distr2(gen);

    // Benchmark the virtual calls
    for (auto _ : state) {
        container[static_cast<std::size_t>(random_value2)]->PureVFn();
    }
    benchmark::DoNotOptimize(container.data());

    // Clean up memory
    for (auto* ptr : container) {
        delete ptr;
    }
}

static void BM_F4_Virt_Int_Call(benchmark::State& state) {
    D d;
    B* ptr = &d;
    for (auto _ : state) {
        ptr->VFn();
        benchmark::DoNotOptimize(ptr);
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_Regular_Base_Cr_Dr);
BENCHMARK(BM_01_Regular_Drv_Cr_Dr);
BENCHMARK(BM_03_Virt_Drv_Cr_Dr);
BENCHMARK(BM_04_Regular_Base_Call);
BENCHMARK(BM_05_Regular_Drv_Call);
BENCHMARK(BM_07_Virt_Base_Call);
BENCHMARK(BM_08_Virt_Drv_Call);
BENCHMARK(BM_09_Virt_Random_Call);
BENCHMARK(BM_F0_VirtA_Drv_Cr_Dr);
BENCHMARK(BM_F1_VirtA_Base_Call);
BENCHMARK(BM_F2_VirtA_Drv_Call);
BENCHMARK(BM_F3_Virt_Same_Call);
BENCHMARK(BM_F4_Virt_Int_Call);
// GEN_BENCHMARK_END

BENCHMARK_MAIN();
