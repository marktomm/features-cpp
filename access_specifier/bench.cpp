#include <benchmark/benchmark.h>

struct SomeType {};

static void access_specifier_bench(benchmark::State& state) {
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
BENCHMARK(access_specifier_bench);

// Run the benchmark
BENCHMARK_MAIN();
