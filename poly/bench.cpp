#include "lib.h"

#include <benchmark/benchmark.h>

#include <cstddef>
#include <random>
#include <vector>

using namespace poly;

static void BM_Virtual_D_Creation_Destruction(benchmark::State& state) {
    for (auto _ : state) {
        D d;
        benchmark::DoNotOptimize(&d);
    }
}
BENCHMARK(BM_Virtual_D_Creation_Destruction);

static void BM_NonVirtual_D_Creation_Destruction(benchmark::State& state) {
    for (auto _ : state) {
        nonVirtualD d;
        benchmark::DoNotOptimize(&d);
    }
}
BENCHMARK(BM_NonVirtual_D_Creation_Destruction);

static void BM_PureVirtualFn_D_Ptr(benchmark::State& state) {
    D d;
    D* ptr = &d;
    for (auto _ : state) {
        ptr->PureVirtualFn();
        benchmark::DoNotOptimize(ptr);
    }
}
BENCHMARK(BM_PureVirtualFn_D_Ptr);

static void BM_PureVirtualFn_A_Ptr(benchmark::State& state) {
    D d;
    A* ptr = &d;
    for (auto _ : state) {
        ptr->PureVirtualFn();
        benchmark::DoNotOptimize(ptr);
    }
}
BENCHMARK(BM_PureVirtualFn_A_Ptr);

static void BM_VirtualFn_D_Ptr(benchmark::State& state) {
    D d;
    D* ptr = &d;
    for (auto _ : state) {
        ptr->VirtualFn();
        benchmark::DoNotOptimize(ptr);
    }
}
BENCHMARK(BM_VirtualFn_D_Ptr);

static void BM_VirtualFn_B_Ptr(benchmark::State& state) {
    D d;
    B* ptr = &d;
    for (auto _ : state) {
        ptr->VirtualFn();
        benchmark::DoNotOptimize(ptr);
    }
}
BENCHMARK(BM_VirtualFn_B_Ptr);

static void BM_Fn_nonVirtualD(benchmark::State& state) {
    nonVirtualD d;
    for (auto _ : state) {
        d.Fn();
        benchmark::DoNotOptimize(&d);
    }
}
BENCHMARK(BM_Fn_nonVirtualD);

static void BM_Fn_nonVirtualA(benchmark::State& state) {
    nonVirtualA a;
    for (auto _ : state) {
        a.Fn();
        benchmark::DoNotOptimize(&a);
    }
}
BENCHMARK(BM_Fn_nonVirtualA);

static void BM_RandomVirtualCalls(benchmark::State& state) {
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
        container[static_cast<std::size_t>(random_value2)]->PureVirtualFn();
    }
    benchmark::DoNotOptimize(container.data());

    // Clean up memory
    for (auto* ptr : container) {
        delete ptr;
    }
}

BENCHMARK(BM_RandomVirtualCalls);

static void BM_SameVirtualCalls(benchmark::State& state) {
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
        container[static_cast<std::size_t>(random_value2)]->PureVirtualFn();
    }
    benchmark::DoNotOptimize(container.data());

    // Clean up memory
    for (auto* ptr : container) {
        delete ptr;
    }
}

BENCHMARK(BM_SameVirtualCalls);

static void BM_SameVirtualCalls2(benchmark::State& state) {
    // Create a container with random instances of derived classes
    std::vector<A*> container;

    for (int i = 0; i < 1000; ++i) {
        container.push_back(new D);
    }

    // Benchmark the virtual calls
    for (auto _ : state) {
        container[1]->PureVirtualFn();
    }
    benchmark::DoNotOptimize(container.data());

    // Clean up memory
    for (auto* ptr : container) {
        delete ptr;
    }
}

BENCHMARK(BM_SameVirtualCalls2);

BENCHMARK_MAIN();
