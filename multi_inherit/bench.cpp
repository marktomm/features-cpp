#include <benchmark/benchmark.h>
#include "lib.h"

struct SomeType {};

static void multi_inherit_bench(benchmark::State& state) {
    using namespace multi_inherit;
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
BENCHMARK(multi_inherit_bench);

// Run the benchmark
BENCHMARK_MAIN();
