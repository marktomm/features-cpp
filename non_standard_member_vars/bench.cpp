#include <benchmark/benchmark.h>
#include "lib.h"

struct SomeType {};

static void non_standard_member_vars_bench(benchmark::State& state) {
    using namespace non_standard_member_vars;
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
BENCHMARK(non_standard_member_vars_bench);

// Run the benchmark
BENCHMARK_MAIN();
