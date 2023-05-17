#!/bin/bash

# ./this_script some_name
# ls -la some_name

set -e

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

ARG1=$1
ARG1=$(trimFwdSlashes ${ARG1})
ARG2=$2
onlyMeson=$([[ -n "${ARG2}" && "${ARG2}" == 'regen_meson' ]] && echo 0 || echo 1)
onlyMesonFunc() {
  return $onlyMeson
}

onlyLibAndBench=$([[ -n "${ARG2}" && "${ARG2}" == 'lib_bench' ]] && echo 0 || echo 1)
onlyLibAndBenchFunc() {
  return $onlyLibAndBench
}

onlyMesonFunc || onlyLibAndBenchFunc || mkdir ${ARG1} ${ARG1}/src ${ARG1}/include

(
cd ${ARG1}
cat << EOF

rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
${ARG1}_inc = include_directories(currentinc)
${ARG1}_main = ['src/main.cpp']
${ARG1}_perf = ['src/perf.cpp']
${ARG1}_src = [
    'src/lib.cpp',
]

${ARG1}_exe = executable(
    '${ARG1}_opt',
    [${ARG1}_main, ${ARG1}_src],
    include_directories: [${ARG1}_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

${ARG1}_exe_no_opt = executable(
    '${ARG1}_no_opt',
    [${ARG1}_main, ${ARG1}_src],
    include_directories: [${ARG1}_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

${ARG1}_inc_opt_o = ${ARG1}_exe.extract_objects(
    ${ARG1}_src,
)

${ARG1}_main_opt_o = ${ARG1}_exe.extract_objects(
    ${ARG1}_main,
)

${ARG1}_inc_o = ${ARG1}_inc_opt_o

${ARG1}_inc_no_opt_o = ${ARG1}_exe_no_opt.extract_objects(
    ${ARG1}_src,
)

${ARG1}_main_no_opt_o = ${ARG1}_exe_no_opt.extract_objects(
    ${ARG1}_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

${ARG1}_exe_sanitize = executable(
    '${ARG1}_opt_sanitize',
    include_directories: [${ARG1}_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        ${ARG1}_main_opt_o, 
        ${ARG1}_inc_opt_o, 
        common_inc_opt_o
    ],
)

${ARG1}_exe_no_opt_sanitize = executable(
    '${ARG1}_no_opt_sanitize',
    include_directories: [${ARG1}_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        ${ARG1}_main_no_opt_o, 
        ${ARG1}_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

${ARG1}_exe_perf = executable(
    '${ARG1}_opt_perf',
    [${ARG1}_perf],
    include_directories: [${ARG1}_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-pg'],
    dependencies: [bench, thread],
    objects: [
        ${ARG1}_inc_opt_o, 
        common_inc_opt_o
    ],
)

${ARG1}_exe_no_opt_perf = executable(
    '${ARG1}_no_opt_perf',
    [${ARG1}_perf],
    include_directories: [${ARG1}_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-pg',],
    dependencies: [bench, thread],
    objects: [
        ${ARG1}_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    ${ARG1}_benchmark_test = ['bench.cpp']

    ${ARG1}_benchmark_google_opt_exe = executable(
        '${ARG1}_benchmark_google_opt',
        [${ARG1}_benchmark_test],
        objects: [${ARG1}_inc_opt_o, common_inc_opt_o],
        include_directories: [${ARG1}_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        '${ARG1}_benchmark_google_opt',
        ${ARG1}_benchmark_google_opt_exe,
        suite: '${ARG1}',
        timeout: 0,
    )

    ${ARG1}_benchmark_google_no_opt_exe = executable(
        '${ARG1}_benchmark_google_no_opt',
        [${ARG1}_benchmark_test],
        objects: [${ARG1}_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [${ARG1}_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        '${ARG1}_benchmark_google_no_opt',
        ${ARG1}_benchmark_google_no_opt_exe,
        suite: '${ARG1}',
        timeout: 0,
    )

    custom_target(
        'bench_${ARG1}',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite ${ARG1} && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            ${ARG1}_benchmark_google_no_opt_exe,
            ${ARG1}_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: ${ARG1}_main,
    output: '${ARG1}_main_no_opt.s',
    command: [
        cpp_prog,
        '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

gen_asm_opt = custom_target(
    'gen_asm_opt',
    input: ${ARG1}_main,
    output: '${ARG1}_main_opt.s',
    command: [
        cpp_prog,
        '-O3', '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

gen_asm_lib = custom_target(
    'gen_asm_lib_no_opt',
    input: ${ARG1}_src,
    output: '${ARG1}_lib_no_opt.s',
    command: [
        cpp_prog,
        '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

gen_asm_lib_opt = custom_target(
    'gen_asm_lib_opt',
    input: ${ARG1}_src,
    output: '${ARG1}_lib_opt.s',
    command: [
        cpp_prog,
        '-O3', '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

gen_asm_bench = custom_target(
    'gen_asm_bench_no_opt',
    input: ${ARG1}_benchmark_test,
    output: '${ARG1}_benchmarks_no_opt.s',
    command: [
        cpp_prog,
        '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

gen_asm_bench_opt = custom_target(
    'gen_asm_bench_opt',
    input: ${ARG1}_benchmark_test,
    output: '${ARG1}_benchmarks_opt.s',
    command: [
        cpp_prog,
        '-O3', '-I' + meson.current_source_dir() + '/include/',
        '-I' + meson.current_source_dir() + '/../',
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
)

EOF
) > ${ARG1}/meson.build

onlyMesonFunc && ! onlyLibAndBenchFunc && exit 0

(
cd ${ARG1}
cat << EOF
#include <benchmark/benchmark.h>
#include "lib.h"

using namespace ${ARG1};

struct SomeType {};

// GEN_PROTO_BEGIN
// GEN_PROTO_END

static void ${ARG1}_bench(benchmark::State& state) {
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
BENCHMARK(${ARG1}_bench);


// GEN_BENCHMARK_BEGIN
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();
EOF
) > ${ARG1}/bench.cpp

! onlyLibAndBenchFunc && (
cat << EOF
#include "lib.h"

using namespace ${ARG1};
using namespace std;

int main() { 
    return 0; 
}
EOF
) > ${ARG1}/src/main.cpp

(
cat << EOF
#include "lib.h"

namespace ${ARG1} {

} // namespace ${ARG1}
EOF
) > ${ARG1}/src/lib.cpp

! onlyLibAndBenchFunc && (
cat << EOF
#ifndef MACRO_${ARG1}_LIB_H
#define MACRO_${ARG1}_LIB_H

#include <cstdint>

namespace ${ARG1} {

class A {
public:
};

// GEN_PROTO_BEGIN
// GEN_PROTO_END

}; // namespace ${ARG1}

#endif
EOF
) > ${ARG1}/include/lib.h

(
cat << EOF
#include "lib.h"

#include <benchmark/benchmark.h>

#include <asm/unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>

#include <cstdint>
#include <cstring>

using namespace ${ARG1};
using namespace std;

namespace pperf {

class A {
public:
    std::uintptr_t a{};
};

} // namespace pperf

int main() {
    pperf::A a;

    // Perf event attributes
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_HARDWARE;
    // pe.config = PERF_COUNT_HW_CACHE_MISSES;
    pe.config = PERF_COUNT_HW_CACHE_REFERENCES;
    pe.size = sizeof(struct perf_event_attr);
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;
    // Configure L1 data cache loads
    pe.config1 = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) |
                 (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16);
    // clang-format off
    // Configure L1 data cache load misses
    // pe.config1 = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) |
    //             (PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
    // clang-format on

    // Open perf event
    long int lfd = syscall(__NR_perf_event_open, &pe, 0, -1, -1, 0);
    if (lfd == -1) {
        cout << "perf_event_open" << endl;
        return 1;
    }
    int fd = static_cast<int>(lfd);

    // Enable perf event
    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

    // Code section to profile
    // Access the A local variable
    benchmark::DoNotOptimize(a);

    // Disable perf event and read the result
    ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
    uint64_t cache_loads;
    read(fd, &cache_loads, sizeof(uint64_t));

    // Print the cache X count
    cout << "L1 Cache Loads: " << cache_loads << endl;

    // Close perf event
    close(fd);

    return 0;
}
EOF
) > ${ARG1}/src/perf.cpp

! onlyLibAndBenchFunc && echo "subdir('${ARG1}')" >> meson.build || true