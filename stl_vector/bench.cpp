#include "common/include/lib.h"
#include "lib.h"
#include <benchmark/benchmark.h>
#include <cstddef>

struct SomeType {};

// GEN_PROTO_BEGIN
static void BM_01_Local_Idx_Incr(benchmark::State& state);
static void BM_02_Global_Idx_Incr(benchmark::State& state);
static void BM_03_100El_Single_Access(benchmark::State& state);
static void BM_04_100El_Sgl_Acc_Local_Idx(benchmark::State& state);
static void BM_05_100El_Sgl_Acc_Global_Idx(benchmark::State& state);
static void BM_07_100El_Dbl_Access(benchmark::State& state);
static void BM_08_100El_Dbl_Acc_Local_Idx(benchmark::State& state);
static void BM_09_100El_Dbl_Acc_Global_Idx(benchmark::State& state);
static void BM_A6_10000El_Dbl_Access(benchmark::State& state);
static void BM_A7_10000El_Dbl_Access_Local_Idx(benchmark::State& state);
static void BM_A8_10000El_Dbl_Access_Global_Idx(benchmark::State& state);
// GEN_PROTO_END

#include <deque>
#include <list>
#include <numeric>
#include <vector>

using namespace stl_vector;
using namespace common;

template<typename Container, std::size_t A>
static Container global_container = generateRandomContainer<Container>(A);

static void BM_01_Local_Idx_Incr(benchmark::State& state) {
    using namespace std;
    std::size_t it = 0;
    for (auto _ : state) {
        auto x = ++it == 100 ? it = 1 : it;
        benchmark::DoNotOptimize(x);
    }
}

static void BM_02_Global_Idx_Incr(benchmark::State& state) {
    using namespace std;
    for (auto _ : state) {
        benchmark::DoNotOptimize(GetNextGlobalIndex());
    }
}

static void BM_03_100El_Single_Access(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 100>;
    for (auto _ : state) {
        uint32_t c = c1[0];
        benchmark::DoNotOptimize(c);
    }
}

static void BM_04_100El_Sgl_Acc_Local_Idx(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 100>;
    std::size_t it = 0;
    for (auto _ : state) {
        auto x = ++it == 100 ? it = 1 : it;
        uint32_t c = c1[x];
        benchmark::DoNotOptimize(c);
    }
}

static void BM_05_100El_Sgl_Acc_Global_Idx(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 100>;
    for (auto _ : state) {
        uint32_t c = c1[GetNextGlobalIndex()];
        benchmark::DoNotOptimize(c);
    }
}

// static void BM_06_100El_Dbl_Access_Static(benchmark::State& state) {
//     using namespace std;
//     auto c1 = global_container<vector<uint32_t>, 100>;
//     vector<uint32_t> c2(100);
//     iota(c2.begin(), c2.end(), 0);
//     for (auto _ : state) {
//         uint32_t c = c1[c2[0]];
//         benchmark::DoNotOptimize(c);
//     }
// }

static void BM_07_100El_Dbl_Access(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 100>;
    auto c2 = global_container<vector<uint32_t>, 100>;
    for (auto _ : state) {
        uint32_t c = c1[c2[0]];
        benchmark::DoNotOptimize(c);
    }
}

static void BM_08_100El_Dbl_Acc_Local_Idx(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 100>;
    auto c2 = global_container<vector<uint32_t>, 100>;
    std::size_t it = 0;
    for (auto _ : state) {
        auto x = ++it == 100 ? it = 1 : it;
        uint32_t c = c1[c2[x]];
        benchmark::DoNotOptimize(c);
    }
}

static void BM_09_100El_Dbl_Acc_Global_Idx(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 100>;
    auto c2 = global_container<vector<uint32_t>, 100>;
    for (auto _ : state) {
        uint32_t c = c1[c2[GetNextGlobalIndex()]];
        benchmark::DoNotOptimize(c);
    }
}

static void BM_A6_10000El_Dbl_Access(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 10000>;
    auto c2 = global_container<vector<uint32_t>, 10000>;
    for (auto _ : state) {
        uint32_t c = c1[c2[0]];
        benchmark::DoNotOptimize(c);
    }
}

static void BM_A7_10000El_Dbl_Access_Local_Idx(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 10000>;
    auto c2 = global_container<vector<uint32_t>, 10000>;
    std::size_t it = 0;
    for (auto _ : state) {
        auto x = ++it == 100 ? it = 1 : it;
        uint32_t c = c1[c2[x]];
        benchmark::DoNotOptimize(c);
    }
}

static void BM_A8_10000El_Dbl_Access_Global_Idx(benchmark::State& state) {
    using namespace std;
    auto c1 = global_container<vector<uint32_t>, 10000>;
    auto c2 = global_container<vector<uint32_t>, 10000>;
    for (auto _ : state) {
        uint32_t c = c1[c2[GetNextGlobalIndex()]];
        benchmark::DoNotOptimize(c);
    }
}

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
static void BMT_Ctor10000Elements(benchmark::State& state) {
    for (auto _ : state) {
        Container c(10000);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_Ctor100000Elements(benchmark::State& state) {
    for (auto _ : state) {
        Container c(100000);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_GlobalContainerAssignToLocal(benchmark::State& state) {
    for (auto _ : state) {
        Container c = global_container<Container, 1000>;
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
static void BMT_EmptyCopyAndCtor(benchmark::State& state) {
    for (auto _ : state) {
        Container c;
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
static void BMT_CtorReserved1000ElemsCopy(benchmark::State& state) {
    Container c = global_container<Container, 1000>;
    for (auto _ : state) {
        Container copy_c(1000);
        copy_c.assign(c.begin(), c.end());
        benchmark::DoNotOptimize(copy_c);
    }
}

template<typename Container>
static void BMT_CtorReserved1000ElemsCopyAndCtors(benchmark::State& state) {
    for (auto _ : state) {
        Container c(1000);
        Container copy_c(1000);
        copy_c.assign(c.begin(), c.end());
        benchmark::DoNotOptimize(copy_c);
    }
}

template<typename Container>
static void BMT_CtorReserved1000ElemsMove(benchmark::State& state) {
    Container c = global_container<Container, 1000>;
    for (auto _ : state) {
        Container move_c(1000);
        move_c = std::move(c);
        benchmark::DoNotOptimize(move_c);
    }
}

template<typename Container>
static void BMT_CtorReserved10000ElemsMove(benchmark::State& state) {
    Container c = global_container<Container, 10000>;
    for (auto _ : state) {
        Container move_c(10000);
        move_c = std::move(c);
        benchmark::DoNotOptimize(move_c);
    }
}

template<typename Container>
static void BMT_CtorReserved100000ElemsMove(benchmark::State& state) {
    Container c = global_container<Container, 100000>;
    for (auto _ : state) {
        Container move_c(100000);
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
    Container c = global_container<Container, 1000>;
    for (auto _ : state) {
        c.push_back(42);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_CtorReserved10000ElemsPushBack(benchmark::State& state) {
    Container c = global_container<Container, 10000>;
    for (auto _ : state) {
        c.push_back(42);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_CtorReserved100000ElemsPushBack(benchmark::State& state) {
    Container c = global_container<Container, 100000>;
    for (auto _ : state) {
        c.push_back(42);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_CtorReserved1000ElemsInsertMiddle(benchmark::State& state) {
    Container c = global_container<Container, 1000>;
    for (auto _ : state) {
        c.insert(std::next(c.begin(), c.size() / 2), 42);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_CtorReserved10000ElemsInsertMiddle(benchmark::State& state) {
    Container c = global_container<Container, 10000>;
    for (auto _ : state) {
        c.insert(std::next(c.begin(), c.size() / 2), 42);
        benchmark::DoNotOptimize(c);
    }
}

template<typename Container>
static void BMT_CtorReserved100000ElemsInsertMiddle(benchmark::State& state) {
    Container c = global_container<Container, 100000>;
    for (auto _ : state) {
        c.insert(std::next(c.begin(), c.size() / 2), 42);
        benchmark::DoNotOptimize(c);
    }
}

#define REGISTER_BENCHMARKS_FOR_CONTAINER(Container)                           \
    BENCHMARK_TEMPLATE(BMT_DefaultCtor, Container);                            \
    BENCHMARK_TEMPLATE(BMT_Ctor1000Elements, Container);                       \
    BENCHMARK_TEMPLATE(BMT_Ctor10000Elements, Container);                      \
    BENCHMARK_TEMPLATE(BMT_Ctor100000Elements, Container);                     \
    BENCHMARK_TEMPLATE(BMT_GlobalContainerAssignToLocal, Container);           \
    BENCHMARK_TEMPLATE(BMT_EmptyCopy, Container);                              \
    BENCHMARK_TEMPLATE(BMT_EmptyCopyAndCtor, Container);                       \
    BENCHMARK_TEMPLATE(BMT_EmptyMove, Container);                              \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsCopy, Container);              \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsCopyAndCtors, Container);      \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsMove, Container);              \
    BENCHMARK_TEMPLATE(BMT_CtorReserved10000ElemsMove, Container);             \
    BENCHMARK_TEMPLATE(BMT_CtorReserved100000ElemsMove, Container);            \
    BENCHMARK_TEMPLATE(BMT_EmptyPushBack, Container);                          \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsPushBack, Container);          \
    BENCHMARK_TEMPLATE(BMT_CtorReserved10000ElemsPushBack, Container);         \
    BENCHMARK_TEMPLATE(BMT_CtorReserved100000ElemsPushBack, Container);        \
    BENCHMARK_TEMPLATE(BMT_CtorReserved1000ElemsInsertMiddle, Container);      \
    BENCHMARK_TEMPLATE(BMT_CtorReserved10000ElemsInsertMiddle, Container);     \
    BENCHMARK_TEMPLATE(BMT_CtorReserved100000ElemsInsertMiddle, Container);

REGISTER_BENCHMARKS_FOR_CONTAINER(std::vector<uint32_t>);
REGISTER_BENCHMARKS_FOR_CONTAINER(std::deque<uint32_t>);
REGISTER_BENCHMARKS_FOR_CONTAINER(std::list<uint32_t>);

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_01_Local_Idx_Incr);
BENCHMARK(BM_02_Global_Idx_Incr);
BENCHMARK(BM_03_100El_Single_Access);
BENCHMARK(BM_04_100El_Sgl_Acc_Local_Idx);
BENCHMARK(BM_05_100El_Sgl_Acc_Global_Idx);
BENCHMARK(BM_07_100El_Dbl_Access);
BENCHMARK(BM_08_100El_Dbl_Acc_Local_Idx);
BENCHMARK(BM_09_100El_Dbl_Acc_Global_Idx);
BENCHMARK(BM_A6_10000El_Dbl_Access);
BENCHMARK(BM_A7_10000El_Dbl_Access_Local_Idx);
BENCHMARK(BM_A8_10000El_Dbl_Access_Global_Idx);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();
