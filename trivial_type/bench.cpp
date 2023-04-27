#include <benchmark/benchmark.h>
#include "lib.h"

struct SomeType {};

static void trivial_type_bench(benchmark::State& state) {
    using namespace trivial_type;
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
BENCHMARK(trivial_type_bench);

// Run the benchmark
BENCHMARK_MAIN();
