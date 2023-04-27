#include "lib.h"
#include <benchmark/benchmark.h>

// struct SomeType {};

// static void virtual_base_class_bench(benchmark::State& state) {
//     using namespace virtual_base_class;
//     // Perform setup here
//     using Ports = std::vector<SomeType>;
//     Ports ports;
//     // ...
//     for (auto _ : state) {
//         // This code gets timed
//         benchmark::DoNotOptimize(ports.data());
//         //...
//         benchmark::ClobberMemory();
//     }
// }

// // Register the function as a benchmark
// BENCHMARK(virtual_base_class_bench);

// // Run the benchmark
// BENCHMARK_MAIN();

using namespace virtual_base_class;

//// 1
// BM_Diamond_BaseToDerived: Dynamic casting from the base class to the derived
// class in a diamond hierarchy.
static void BM_Diamond_BaseToDerived(benchmark::State& state) {
    A* a_ptr = new D();
    for (auto _ : state) {
        D* d_ptr = dynamic_cast<D*>(a_ptr);
        benchmark::DoNotOptimize(d_ptr);
    }
    delete a_ptr;
}
BENCHMARK(BM_Diamond_BaseToDerived);
// BM_NonDiamond_BaseToDerived: Dynamic casting from the base class to the
// derived class in a non-diamond hierarchy.
static void BM_NonDiamond_BaseToDerived(benchmark::State& state) {
    nonDiamondA* a_ptr = new nonDiamondD();
    for (auto _ : state) {
        nonDiamondD* d_ptr = dynamic_cast<nonDiamondD*>(a_ptr);
        benchmark::DoNotOptimize(d_ptr);
    }
    delete a_ptr;
}
BENCHMARK(BM_NonDiamond_BaseToDerived);
// BM_NonDiamond_BaseToDerived_StaticCast: Static casting from the base class to
// the derived class in a non-diamond hierarchy.
static void BM_NonDiamond_BaseToDerived_StaticCast(benchmark::State& state) {
    nonDiamondA* a_ptr = new nonDiamondD();
    for (auto _ : state) {
        nonDiamondD* d_ptr = static_cast<nonDiamondD*>(a_ptr);
        benchmark::DoNotOptimize(d_ptr);
    }
    delete a_ptr;
}
BENCHMARK(BM_NonDiamond_BaseToDerived_StaticCast);

//// 2 Sideways
// BM_Diamond_Sideways: Dynamic casting from one sibling class to another in a
// diamond hierarchy.
static void BM_Diamond_Sideways(benchmark::State& state) {
    B* b_ptr = new D();
    for (auto _ : state) {
        C* c_ptr = dynamic_cast<C*>(b_ptr);
        benchmark::DoNotOptimize(c_ptr);
    }
    delete b_ptr;
}
BENCHMARK(BM_Diamond_Sideways);
// // BM_NonDiamond_Sideways: Dynamic casting from one sibling class to another
// in
// // a non-diamond hierarchy.
// static void BM_NonDiamond_Sideways(benchmark::State& state) {
//     nonDiamondB* b_ptr = new nonDiamondC();
//     for (auto _ : state) {
//         nonDiamondC* c_ptr = dynamic_cast<nonDiamondC*>(b_ptr);
//         benchmark::DoNotOptimize(c_ptr);
//     }
//     delete b_ptr;
// }
// BENCHMARK(BM_NonDiamond_Sideways);
// BM_NonVirtualDiamond_Sideways_Casting: Dynamic casting from one sibling class
// to another in a non-virtual diamond inheritance hierarchy. Note that this is
// not recommended due to the multiple instances of the base class, which can
// lead to unexpected behavior.
static void BM_NonVirtualDiamond_Sideways_Casting(benchmark::State& state) {
    nonVirtualDiamondB* b_ptr = new nonVirtualDiamondD();
    for (auto _ : state) {
        nonVirtualDiamondC* c_ptr = dynamic_cast<nonVirtualDiamondC*>(b_ptr);
        benchmark::DoNotOptimize(c_ptr);
    }
    delete b_ptr;
}
BENCHMARK(BM_NonVirtualDiamond_Sideways_Casting);

//// 3 Diamond
// BM_Diamond_DerivedToBase: Dynamic casting from the derived class to the base
// class in a diamond hierarchy.
static void BM_Diamond_DerivedToBase(benchmark::State& state) {
    D* d_ptr = new D();
    for (auto _ : state) {
        A* a_ptr = dynamic_cast<A*>(d_ptr);
        benchmark::DoNotOptimize(a_ptr);
    }
    delete d_ptr;
}
BENCHMARK(BM_Diamond_DerivedToBase);
// BM_NonDiamond_DerivedToBase: Dynamic casting from the derived class to the
// base class in a non-diamond hierarchy.
static void BM_NonDiamond_DerivedToBase(benchmark::State& state) {
    nonDiamondD* d_ptr = new nonDiamondD();
    for (auto _ : state) {
        nonDiamondA* a_ptr = dynamic_cast<nonDiamondA*>(d_ptr);
        benchmark::DoNotOptimize(a_ptr);
    }
    delete d_ptr;
}
BENCHMARK(BM_NonDiamond_DerivedToBase);
static void BM_Diamond_DerivedToBase_StaticCast(benchmark::State& state) {
    D* d_ptr = new D();
    for (auto _ : state) {
        A* a_ptr = static_cast<A*>(d_ptr);
        benchmark::DoNotOptimize(a_ptr);
    }
    delete d_ptr;
}
BENCHMARK(BM_Diamond_DerivedToBase_StaticCast);
// BM_NonDiamond_DerivedToBase_StaticCast: Static casting from the derived class
// to the base class in a non-diamond hierarchy.
static void BM_NonDiamond_DerivedToBase_StaticCast(benchmark::State& state) {
    nonDiamondD* d_ptr = new nonDiamondD();
    for (auto _ : state) {
        nonDiamondA* a_ptr = static_cast<nonDiamondA*>(d_ptr);
        benchmark::DoNotOptimize(a_ptr);
    }
    delete d_ptr;
}
BENCHMARK(BM_NonDiamond_DerivedToBase_StaticCast);

// // does not compile:
// // BM_NonVirtualDiamond_Intermediate_Casting: Dynamic casting from the base
// // class to the derived class that is more than one level down in the
// // non-virtual diamond inheritance hierarchy, passing through an intermediate
// // class.
// static void BM_NonVirtualDiamond_Intermediate_Casting(benchmark::State&
// state) {
//     nonVirtualDiamondA* a_ptr = new nonVirtualDiamondD();
//     for (auto _ : state) {
//         nonVirtualDiamondD* d_ptr = dynamic_cast<nonVirtualDiamondD*>(a_ptr);
//         benchmark::DoNotOptimize(d_ptr);
//     }
//     delete a_ptr;
// }
// BENCHMARK(BM_NonVirtualDiamond_Intermediate_Casting);
// // use this instead:
static void BM_NonVirtualDiamond_Intermediate_Casting(benchmark::State& state) {
    nonVirtualDiamondD* d_ptr = new nonVirtualDiamondD();
    nonVirtualDiamondB* b_ptr = static_cast<nonVirtualDiamondB*>(d_ptr);
    for (auto _ : state) {
        nonVirtualDiamondA* a_ptr = dynamic_cast<nonVirtualDiamondA*>(b_ptr);
        benchmark::DoNotOptimize(a_ptr);
    }
    delete d_ptr;
}
BENCHMARK(BM_NonVirtualDiamond_Intermediate_Casting);

//// 4 Cross casting
// BM_Cross_Casting: Dynamic casting from one sibling class to another in a
// multiple inheritance hierarchy, where the classes don't share the same base
// class (cross-casting).
static void BM_Cross_Casting(benchmark::State& state) {
    X* x_ptr = new Z();
    for (auto _ : state) {
        Y* y_ptr = dynamic_cast<Y*>(x_ptr);
        benchmark::DoNotOptimize(y_ptr);
    }
    delete x_ptr;
}
BENCHMARK(BM_Cross_Casting);

//// 5
// BM_Intermediate_Casting: Dynamic casting from a base class to a derived class
// that is more than one level down in the inheritance hierarchy, passing
// through an intermediate class.
static void BM_Intermediate_Casting(benchmark::State& state) {
    I* i_ptr = new K();
    for (auto _ : state) {
        K* k_ptr = dynamic_cast<K*>(i_ptr);
        benchmark::DoNotOptimize(k_ptr);
    }
    delete i_ptr;
}
BENCHMARK(BM_Intermediate_Casting);

//// 6
// BM_Unrelated_Casting: Dynamic casting from a base class to an unrelated
// class, which is not part of the same inheritance hierarchy.
static void BM_Unrelated_Casting(benchmark::State& state) {
    M* m_ptr = new M();
    for (auto _ : state) {
        N* n_ptr = dynamic_cast<N*>(m_ptr);
        benchmark::DoNotOptimize(n_ptr);
    }
    delete m_ptr;
}
BENCHMARK(BM_Unrelated_Casting);

BENCHMARK_MAIN();
