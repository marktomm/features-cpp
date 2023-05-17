
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
basics_inc = include_directories(currentinc)
basics_main = ['src/main.cpp']
basics_perf = ['src/perf.cpp']
basics_src = [
    'src/lib.cpp',
]

basics_exe = executable(
    'basics_opt',
    [basics_main, basics_src],
    include_directories: [basics_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

basics_exe_no_opt = executable(
    'basics_no_opt',
    [basics_main, basics_src],
    include_directories: [basics_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

basics_inc_opt_o = basics_exe.extract_objects(
    basics_src,
)

basics_main_opt_o = basics_exe.extract_objects(
    basics_main,
)

basics_inc_o = basics_inc_opt_o

basics_inc_no_opt_o = basics_exe_no_opt.extract_objects(
    basics_src,
)

basics_main_no_opt_o = basics_exe_no_opt.extract_objects(
    basics_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

basics_exe_sanitize = executable(
    'basics_opt_sanitize',
    include_directories: [basics_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        basics_main_opt_o, 
        basics_inc_opt_o, 
        common_inc_opt_o
    ],
)

basics_exe_no_opt_sanitize = executable(
    'basics_no_opt_sanitize',
    include_directories: [basics_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        basics_main_no_opt_o, 
        basics_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

basics_exe_perf = executable(
    'basics_opt_perf',
    [basics_perf],
    include_directories: [basics_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-pg'],
    dependencies: [bench, thread],
    objects: [
        basics_inc_opt_o, 
        common_inc_opt_o
    ],
)

basics_exe_no_opt_perf = executable(
    'basics_no_opt_perf',
    [basics_perf],
    include_directories: [basics_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-pg',],
    dependencies: [bench, thread],
    objects: [
        basics_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    basics_benchmark_test = ['bench.cpp']

    basics_benchmark_google_opt_exe = executable(
        'basics_benchmark_google_opt',
        [basics_benchmark_test],
        objects: [basics_inc_opt_o, common_inc_opt_o],
        include_directories: [basics_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'basics_benchmark_google_opt',
        basics_benchmark_google_opt_exe,
        suite: 'basics',
        timeout: 0,
    )

    basics_benchmark_google_no_opt_exe = executable(
        'basics_benchmark_google_no_opt',
        [basics_benchmark_test],
        objects: [basics_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [basics_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'basics_benchmark_google_no_opt',
        basics_benchmark_google_no_opt_exe,
        suite: 'basics',
        timeout: 0,
    )

    custom_target(
        'bench_basics',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite basics && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            basics_benchmark_google_no_opt_exe,
            basics_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: basics_main,
    output: 'basics_main_no_opt.s',
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
    input: basics_main,
    output: 'basics_main_opt.s',
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
    input: basics_src,
    output: 'basics_lib_no_opt.s',
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
    input: basics_src,
    output: 'basics_lib_opt.s',
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
    input: basics_benchmark_test,
    output: 'basics_benchmarks_no_opt.s',
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
    input: basics_benchmark_test,
    output: 'basics_benchmarks_opt.s',
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

