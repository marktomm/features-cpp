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

onlyMesonFunc || mkdir ${ARG1} ${ARG1}/src ${ARG1}/include

(
cd ${ARG1}
cat << EOF

rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
${ARG1}_inc = include_directories(currentinc)
${ARG1}_main = ['src/main.cpp']
# ${ARG1}_simple = ['src/user_simple.cpp']
${ARG1}_src = [
    'src/lib.cpp',
]

${ARG1}_exe = executable(
    '${ARG1}_opt',
    [${ARG1}_main, ${ARG1}_src],
    include_directories: [${ARG1}_inc, common_inc],
    install: true,
)

${ARG1}_exe_no_opt = executable(
    '${ARG1}_no_opt',
    [${ARG1}_main, ${ARG1}_src],
    include_directories: [${ARG1}_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g'],
)

${ARG1}_inc_opt_o = ${ARG1}_exe.extract_objects(
    ${ARG1}_src,
)

${ARG1}_inc_no_opt_o = ${ARG1}_exe_no_opt.extract_objects(
    ${ARG1}_src,
)

# executable(
#     '${ARG1}_simple',
#     [${ARG1}_simple],
#     objects: [${ARG1}_inc_opt_o],
#     include_directories: [${ARG1}_inc, common_inc],
#     install: true,
# )

if bench.found()
    ${ARG1}_benchmark_test = ['bench.cpp']

    ${ARG1}_benchmark_google_opt_exe = executable(
        '${ARG1}_benchmark_google_opt',
        [${ARG1}_benchmark_test, common_src],
        objects: ${ARG1}_inc_opt_o,
        include_directories: ${ARG1}_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        '${ARG1}_benchmark_google_opt',
        ${ARG1}_benchmark_google_opt_exe,
        suite: '${ARG1}',
    )

    ${ARG1}_benchmark_google_no_opt_exe = executable(
        '${ARG1}_benchmark_google_no_opt',
        [${ARG1}_benchmark_test, common_src],
        objects: ${ARG1}_inc_no_opt_o,
        include_directories: ${ARG1}_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        '${ARG1}_benchmark_google_no_opt',
        ${ARG1}_benchmark_google_no_opt_exe,
        suite: '${ARG1}',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: ${ARG1}_main,
    output: '${ARG1}_main_no_opt.s',
    command: [
        cpp_prog,
        '-I' + meson.current_source_dir() + '/include/',
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
        '-S',
        '-masm=intel',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
    build_by_default: true,
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
EOF
) > ${ARG1}/meson.build

onlyMesonFunc && exit 0

(
cd ${ARG1}
cat << EOF
#include <benchmark/benchmark.h>
#include "lib.h"

// GEN_PROTO_BEGIN
// GEN_PROTO_END

struct SomeType {};

static void ${ARG1}_bench(benchmark::State& state) {
    using namespace ${ARG1};
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

(
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


(
cat << EOF
#ifndef MACRO_${ARG1}_LIB_H
#define MACRO_${ARG1}_LIB_H

#include <cstdint>

namespace ${ARG1} {

class A {
public:
};

}; // namespace ${ARG1}

#endif
EOF
) > ${ARG1}/include/lib.h

echo "subdir('${ARG1}')" >> meson.build