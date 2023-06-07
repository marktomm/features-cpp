#include "common/include/lib.h"
#include "lib.h"

#include <benchmark/benchmark.h>
#include <memory>

#include <cstddef>
#include <random>
#include <vector>

using namespace poly;
using namespace common;

// GEN_PROTO_BEGIN
static void BM_00_Trivial_Fn(benchmark::State& state);
static void BM_03_Virt_Base_Fn(benchmark::State& state);
static void BM_05_Virt_Rand_Ptr_Fn(benchmark::State& state);
static void BM_06_Virt_Rand_Up_Fn(benchmark::State& state);
static void BM_10_Trivial_Fn_Inc(benchmark::State& state);
static void BM_13_Virt_Base_Fn_Add(benchmark::State& state);
static void BM_14_Virt_Drv_Fn(benchmark::State& state);
static void BM_A0_Trivial_Base_Cr_Dr(benchmark::State& state);
static void BM_A1_Trivial_Drv_Cr_Dr(benchmark::State& state);
static void BM_A3_Virt_Drv_Cr_Dr(benchmark::State& state);
static void BM_D2_Trivial_Random_Fn(benchmark::State& state);
static void BM_F0_VirtA_Drv_Cr_Dr(benchmark::State& state);
static void BM_F1_VirtA_Base_Fn(benchmark::State& state);
static void BM_F2_VirtA_Drv_Fn(benchmark::State& state);
static void BM_F3_Virt_Same_Fn(benchmark::State& state);
static void BM_F4_Virt_Int_Fn(benchmark::State& state);
static void BM_K1_Trivial_Drv_Fn_Inc(benchmark::State& state);
// GEN_PROTO_END

static void BM_00_Trivial_Fn(benchmark::State& state) {
    nonVA a;
    for (auto _ : state) {
        a.FnNone();
        benchmark::DoNotOptimize(&a);
    }
}

static void BM_10_Trivial_Fn_Inc(benchmark::State& state) {
    nonVA a;
    for (auto _ : state) {
        asm volatile("3:");
        a.Fn(9);
        benchmark::DoNotOptimize(&a);
        asm volatile("4:");
    }
}

static void BM_K1_Trivial_Drv_Fn_Inc(benchmark::State& state) {
    nonVD d;
    for (auto _ : state) {
        asm volatile("1:");
        d.Fn(14);
        benchmark::DoNotOptimize(&d);
        asm volatile("2:");
    }
}

static void BM_D2_Trivial_Random_Fn(benchmark::State& state) {
    // Create a container with random instances of derived classes
    std::vector<nonVA*> container;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 3);

    for (int i = 0; i < 100; ++i) {
        int random_value = distr(gen);
        switch (random_value) {
        case 1:
            container.push_back(new nonVD);
            break;
        case 2:
            container.push_back(new nonVD1);
            break;
        case 3:
            container.push_back(new nonVD2);
            break;
        }
    }

    std::size_t it = 0;
    for (auto _ : state) {
        auto x = ++it == 100 ? it = 0 : it;
        container[static_cast<std::size_t>(x)]->Fn(255);
    }
    benchmark::DoNotOptimize(container.data());

    for (auto* ptr : container) {
        delete ptr; // leak
    }
}

static void BM_03_Virt_Base_Fn(benchmark::State& state) {
    D d;
    A* ptr = &d;
    for (auto _ : state) {
        ptr->PureVFn();
        benchmark::DoNotOptimize(ptr);
        benchmark::DoNotOptimize(d);
    }
}

static void BM_13_Virt_Base_Fn_Add(benchmark::State& state) {
    D d;
    A* ptr = &d;
    for (auto _ : state) {
        ptr->PureVFn(65);
        benchmark::DoNotOptimize(ptr);
        benchmark::DoNotOptimize(d);
    }
}

static void BM_14_Virt_Drv_Fn(benchmark::State& state) {
    D d;
    D* ptr = &d;
    for (auto _ : state) {
        ptr->PureVFn();
        benchmark::DoNotOptimize(ptr);
        benchmark::DoNotOptimize(d);
    }
}

static void BM_05_Virt_Rand_Ptr_Fn(benchmark::State& state) {
    // Create a container with random instances of derived classes
    std::vector<A*> container;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 2);

    for (int i = 0; i < 100; ++i) {
        int random_value = distr(gen);
        switch (random_value) {
        case 1:
            container.push_back(new D);
            break;
        case 2:
            container.push_back(new E);
            break;
        }
    }

    std::size_t it = 0;
    for (auto _ : state) {
        auto x = ++it == 100 ? it = 0 : it;
        asm volatile("1:");
        container[static_cast<std::size_t>(x)]->PureVFn();
        asm volatile("10:");
    }
    benchmark::DoNotOptimize(container.data());

    for (auto* ptr : container) {
        delete ptr;
    }
}

static void BM_06_Virt_Rand_Up_Fn(benchmark::State& state) {
    // Create a container with random instances of derived classes
    std::vector<std::unique_ptr<A> > container;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 2);

    for (int i = 0; i < 100; ++i) {
        int random_value = distr(gen);
        switch (random_value) {
        case 1:
            container.push_back(std::make_unique<D>());
            break;
        case 2:
            container.push_back(std::make_unique<D>());
            break;
        }
    }

    std::size_t it = 0;
    for (auto _ : state) {
        auto x = ++it == 100 ? it = 0 : it;
        asm volatile("100:");
        container[static_cast<std::size_t>(x)]->PureVFn();
        asm volatile("101:");
    }
    benchmark::DoNotOptimize(container.data());
}

static void BM_A0_Trivial_Base_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        nonVA a;
        benchmark::DoNotOptimize(&a);
    }
}

static void BM_A1_Trivial_Drv_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        nonVD d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_A3_Virt_Drv_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        D d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_F0_VirtA_Drv_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        Dx d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_F1_VirtA_Base_Fn(benchmark::State& state) {
    Ax d;
    for (auto _ : state) {
        d.Fn();
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_F2_VirtA_Drv_Fn(benchmark::State& state) {
    Dx d;
    for (auto _ : state) {
        d.Fn();
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_F3_Virt_Same_Fn(benchmark::State& state) {
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

static void BM_F4_Virt_Int_Fn(benchmark::State& state) {
    D d;
    D* ptr = &d;
    for (auto _ : state) {
        ptr->VFn();
        benchmark::DoNotOptimize(ptr);
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_Trivial_Fn);
BENCHMARK(BM_03_Virt_Base_Fn);
BENCHMARK(BM_05_Virt_Rand_Ptr_Fn);
BENCHMARK(BM_06_Virt_Rand_Up_Fn);
BENCHMARK(BM_10_Trivial_Fn_Inc);
BENCHMARK(BM_13_Virt_Base_Fn_Add);
BENCHMARK(BM_14_Virt_Drv_Fn);
BENCHMARK(BM_A0_Trivial_Base_Cr_Dr);
BENCHMARK(BM_A1_Trivial_Drv_Cr_Dr);
BENCHMARK(BM_A3_Virt_Drv_Cr_Dr);
BENCHMARK(BM_D2_Trivial_Random_Fn);
BENCHMARK(BM_F0_VirtA_Drv_Cr_Dr);
BENCHMARK(BM_F1_VirtA_Base_Fn);
BENCHMARK(BM_F2_VirtA_Drv_Fn);
BENCHMARK(BM_F3_Virt_Same_Fn);
BENCHMARK(BM_F4_Virt_Int_Fn);
BENCHMARK(BM_K1_Trivial_Drv_Fn_Inc);
// GEN_BENCHMARK_END

BENCHMARK_MAIN();
