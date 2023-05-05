#include "lib.h"

#include <benchmark/benchmark.h>

#include <cstddef>
#include <random>
#include <vector>

using namespace poly;

// GEN_PROTO_BEGIN
static void BM_00_NonV_D_Ctor_Dtor(benchmark::State& state);
static void BM_01_V_D_Ctor_Dtor(benchmark::State& state);
static void BM_02_VBase_Dx_Ctor_Dtor(benchmark::State& state);
static void BM_04_NonV_D_Fn(benchmark::State& state);
static void BM_05_NonV_A_Fn(benchmark::State& state);
static void BM_06_PureV_A_Fn_Ptr(benchmark::State& state);
static void BM_07_PureV_D_Fn_Ptr(benchmark::State& state);
static void BM_08_PureV_Random_Fn(benchmark::State& state);
static void BM_09_PureV_Same_Fn(benchmark::State& state);
static void BM_0A_PureV_Same_Fn_2(benchmark::State& state);
static void BM_0B_V_B_Fn_Ptr(benchmark::State& state);
static void BM_0C_V_D_Fn_Ptr(benchmark::State& state);
// GEN_PROTO_END

static void BM_02_VBase_Dx_Ctor_Dtor(benchmark::State& state) {
    for (auto _ : state) {
        Dx d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_01_V_D_Ctor_Dtor(benchmark::State& state) {
    for (auto _ : state) {
        D d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_00_NonV_D_Ctor_Dtor(benchmark::State& state) {
    for (auto _ : state) {
        nonVD d;
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_04_NonV_D_Fn(benchmark::State& state) {
    nonVD d;
    for (auto _ : state) {
        d.Fn();
        benchmark::DoNotOptimize(&d);
    }
}

static void BM_05_NonV_A_Fn(benchmark::State& state) {
    nonVA a;
    for (auto _ : state) {
        a.Fn();
        benchmark::DoNotOptimize(&a);
    }
}

static void BM_07_PureV_D_Fn_Ptr(benchmark::State& state) {
    D d;
    D* ptr = &d;
    for (auto _ : state) {
        ptr->PureVFn();
        benchmark::DoNotOptimize(ptr);
    }
}

static void BM_06_PureV_A_Fn_Ptr(benchmark::State& state) {
    D d;
    A* ptr = &d;
    for (auto _ : state) {
        ptr->PureVFn();
        benchmark::DoNotOptimize(ptr);
    }
}

static void BM_0C_V_D_Fn_Ptr(benchmark::State& state) {
    D d;
    D* ptr = &d;
    for (auto _ : state) {
        ptr->VFn();
        benchmark::DoNotOptimize(ptr);
    }
}

static void BM_0B_V_B_Fn_Ptr(benchmark::State& state) {
    D d;
    B* ptr = &d;
    for (auto _ : state) {
        ptr->VFn();
        benchmark::DoNotOptimize(ptr);
    }
}

static void BM_08_PureV_Random_Fn(benchmark::State& state) {
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

static void BM_09_PureV_Same_Fn(benchmark::State& state) {
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

static void BM_0A_PureV_Same_Fn_2(benchmark::State& state) {
    // Create a container with random instances of derived classes
    std::vector<A*> container;

    for (int i = 0; i < 1000; ++i) {
        container.push_back(new D);
    }

    // Benchmark the virtual calls
    for (auto _ : state) {
        container[1]->PureVFn();
    }
    benchmark::DoNotOptimize(container.data());

    // Clean up memory
    for (auto* ptr : container) {
        delete ptr;
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_NonV_D_Ctor_Dtor);
BENCHMARK(BM_01_V_D_Ctor_Dtor);
BENCHMARK(BM_02_VBase_Dx_Ctor_Dtor);
BENCHMARK(BM_04_NonV_D_Fn);
BENCHMARK(BM_05_NonV_A_Fn);
BENCHMARK(BM_06_PureV_A_Fn_Ptr);
BENCHMARK(BM_07_PureV_D_Fn_Ptr);
BENCHMARK(BM_08_PureV_Random_Fn);
BENCHMARK(BM_09_PureV_Same_Fn);
BENCHMARK(BM_0A_PureV_Same_Fn_2);
BENCHMARK(BM_0B_V_B_Fn_Ptr);
BENCHMARK(BM_0C_V_D_Fn_Ptr);
// GEN_BENCHMARK_END

BENCHMARK_MAIN();
