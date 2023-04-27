#!/bin/bash

# ./this_script some_name
# ls -la some_name

set -e

ARG1=$1

mkdir ${ARG1} ${ARG1}/src ${ARG1}/include

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
    '${ARG1}',
    [${ARG1}_main, ${ARG1}_src],
    include_directories: [${ARG1}_inc, common_inc],
    install: true,
)

${ARG1}_inc_o = ${ARG1}_exe.extract_objects(
    ${ARG1}_src,
)

# executable(
#     '${ARG1}_simple',
#     [${ARG1}_simple],
#     objects: [${ARG1}_inc_o],
#     include_directories: [${ARG1}_inc, common_inc],
#     install: true,
# )

if bench.found()
    ${ARG1}_benchmark_test = ['bench.cpp']

    ${ARG1}_benchmark_google_opt_exe = executable(
        '${ARG1}_benchmark_google_opt',
        [${ARG1}_benchmark_test, common_src],
        objects: ${ARG1}_inc_o,
        include_directories: ${ARG1}_inc,
        dependencies: [bench, thread],
    )

    test(
        '${ARG1}_benchmark_google_opt',
        ${ARG1}_benchmark_google_opt_exe,
        is_parallel: false,
    )

    ${ARG1}_benchmark_google_no_opt_exe = executable(
        '${ARG1}_benchmark_google_no_opt',
        [${ARG1}_benchmark_test, common_src],
        objects: ${ARG1}_inc_o,
        include_directories: ${ARG1}_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    test(
        '${ARG1}_benchmark_google_no_opt',
        ${ARG1}_benchmark_google_no_opt_exe,
        is_parallel: false,
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: ${ARG1}_main,
    output: '${ARG1}_main.s',
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
EOF
) > ${ARG1}/meson.build

(
cd ${ARG1}
cat << EOF
#include <benchmark/benchmark.h>
#include "lib.h"

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

// Run the benchmark
BENCHMARK_MAIN();
EOF
) > ${ARG1}/bench.cpp

(
cat << EOF
#include "lib.h"

int main() { 
    using namespace ${ARG1};
    return 0; 
}
EOF
) > ${ARG1}/src/main.cpp

(
cat << EOF
#include "lib.h"
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