#include <benchmark/benchmark.h>
#include "lib.h"

struct SomeType {};

static void class_member_funcion_bench(benchmark::State& state) {
    using namespace class_member_funcion;
    // Perform setup here
    using Ports = std::vector<SomeType>;
    Ports ports;
    // ...
    for (auto _ : state) {
        // This code gets timed
        benchmark::DoNotOptimize(ports.data());
        //...
        benchmark::ClobberMemory();
    }
}

// Register the function as a benchmark
BENCHMARK(class_member_funcion_bench);

// Run the benchmark
BENCHMARK_MAIN();
