#include "lib.h"
#include <benchmark/benchmark.h>

struct SomeType {};

// GEN_PROTO_BEGIN

// GEN_PROTO_END

#include <deque>
#include <list>
#include <vector>

using namespace stl_vector;

template<typename Container>
static void BMT_DefaultCtor(benchmark::State& state) {
    for (auto _ : state) {
        Container c;
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_Ctor1000Elements(benchmark::State& state) {
    for (auto _ : state) {
        Container c(1000);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_EmptyCopy(benchmark::State& state) {
    Container c;
    for (auto _ : state) {
        Container copy_c(c);
        benchmark::DoNotOptimize(copy_c);
    }
}

template<typename Container>
static void BMT_EmptyMove(benchmark::State& state) {
    for (auto _ : state) {
        Container c;
        Container move_c(std::move(c));
        benchmark::DoNotOptimize(move_c);
    }
}

template<typename Container>
static Container global_container = generateRandomContainer<Container>(1000);

template<typename Container>
static void BMT_CtorReserved1000ElemsCopy(benchmark::State& state) {
    Container c = global_container<Container>;
    for (auto _ : state) {
        Container copy_c(1000);
        // copy_c.reserve(1000);
        copy_c.assign(c.begin(), c.end());
        benchmark::DoNotOptimize(copy_c);
    }
}

template<typename Container>
static void BMT_CtorReserved1000ElemsMove(benchmark::State& state) {
    Container c = global_container<Container>;
    for (auto _ : state) {
        Container move_c(1000);
        // move_c.reserve(1000);
        move_c = std::move(c);
        benchmark::DoNotOptimize(move_c);
    }
}

template<typename Container>
static void BMT_EmptyPushBack(benchmark::State& state) {
    Container c;
    for (auto _ : state) {
        c.push_back(42);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_CtorReserved1000ElemsPushBack(benchmark::State& state) {
    Container c = global_container<Container>;
    for (auto _ : state) {
        for (int i = 0; i < 1000; ++i) {
            c.push_back(i);
        }
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_CtorReserved1000ElemsInsertMiddle(benchmark::State& state) {
    Container c = global_container<Container>;
    for (auto _ : state) {
        c.insert(std::next(c.begin(), c.size() / 2), 42);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_CtorReserved10000ElemsInsertMiddle(benchmark::State& state) {
    Container c = global_container<Container>;
    for (auto _ : state) {
        c.insert(std::next(c.begin(), c.size() / 2), 42);
        benchmark::DoNotOptimize(c);
    }
}

#define REGISTER_BENCHMARKS_FOR_CONTAINER(Container)                           \
    BENCHMARK_TEMPLATE(BMT_DefaultCtor, Container);                            \
    BENCHMARK_TEMPLATE(BMT_Ctor1000Elements, Container);                       \
    BENCHMARK_TEMPLATE(BMT_EmptyCopy, Container);                              \
    BENCHMARK_TEMPLATE(BMT_EmptyMove, Container);                              \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsCopy, Container);              \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsMove, Container);              \
    BENCHMARK_TEMPLATE(BMT_EmptyPushBack, Container);                          \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsPushBack, Container);          \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsInsertMiddle, Container);      \
    BENCHMARK_TEMPLATE(BMT_CtorReserved10000ElemsInsertMiddle, Container);

REGISTER_BENCHMARKS_FOR_CONTAINER(std::vector<int>);
REGISTER_BENCHMARKS_FOR_CONTAINER(std::deque<int>);
REGISTER_BENCHMARKS_FOR_CONTAINER(std::list<int>);

// GEN_BENCHMARK_BEGIN

// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();
