
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
multi_inherit_inc = include_directories(currentinc)
multi_inherit_main = ['src/main.cpp']
multi_inherit_perf = ['src/perf.cpp']
multi_inherit_src = [
    'src/lib.cpp',
]

multi_inherit_exe = executable(
    'multi_inherit_opt',
    [multi_inherit_main, multi_inherit_src],
    include_directories: [multi_inherit_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

multi_inherit_exe_no_opt = executable(
    'multi_inherit_no_opt',
    [multi_inherit_main, multi_inherit_src],
    include_directories: [multi_inherit_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

multi_inherit_inc_opt_o = multi_inherit_exe.extract_objects(
    multi_inherit_src,
)

multi_inherit_main_opt_o = multi_inherit_exe.extract_objects(
    multi_inherit_main,
)

multi_inherit_inc_o = multi_inherit_inc_opt_o

multi_inherit_inc_no_opt_o = multi_inherit_exe_no_opt.extract_objects(
    multi_inherit_src,
)

multi_inherit_main_no_opt_o = multi_inherit_exe_no_opt.extract_objects(
    multi_inherit_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

multi_inherit_exe_sanitize = executable(
    'multi_inherit_opt_sanitize',
    include_directories: [multi_inherit_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        multi_inherit_main_opt_o, 
        multi_inherit_inc_opt_o, 
        common_inc_opt_o
    ],
)

multi_inherit_exe_no_opt_sanitize = executable(
    'multi_inherit_no_opt_sanitize',
    include_directories: [multi_inherit_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        multi_inherit_main_no_opt_o, 
        multi_inherit_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

multi_inherit_exe_perf = executable(
    'multi_inherit_opt_perf',
    [multi_inherit_perf],
    include_directories: [multi_inherit_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-pg'],
    dependencies: [bench, thread],
    objects: [
        multi_inherit_inc_opt_o, 
        common_inc_opt_o
    ],
)

multi_inherit_exe_no_opt_perf = executable(
    'multi_inherit_no_opt_perf',
    [multi_inherit_perf],
    include_directories: [multi_inherit_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-pg',],
    dependencies: [bench, thread],
    objects: [
        multi_inherit_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    multi_inherit_benchmark_test = ['bench.cpp']

    multi_inherit_benchmark_google_opt_exe = executable(
        'multi_inherit_benchmark_google_opt',
        [multi_inherit_benchmark_test],
        objects: [multi_inherit_inc_opt_o, common_inc_opt_o],
        include_directories: [multi_inherit_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'multi_inherit_benchmark_google_opt',
        multi_inherit_benchmark_google_opt_exe,
        suite: 'multi_inherit',
        timeout: 0,
    )

    multi_inherit_benchmark_google_no_opt_exe = executable(
        'multi_inherit_benchmark_google_no_opt',
        [multi_inherit_benchmark_test],
        objects: [multi_inherit_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [multi_inherit_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'multi_inherit_benchmark_google_no_opt',
        multi_inherit_benchmark_google_no_opt_exe,
        suite: 'multi_inherit',
        timeout: 0,
    )

    custom_target(
        'bench_multi_inherit',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite multi_inherit && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            multi_inherit_benchmark_google_no_opt_exe,
            multi_inherit_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: multi_inherit_main,
    output: 'multi_inherit_main_no_opt.s',
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
    input: multi_inherit_main,
    output: 'multi_inherit_main_opt.s',
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
    input: multi_inherit_src,
    output: 'multi_inherit_lib_no_opt.s',
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
    input: multi_inherit_src,
    output: 'multi_inherit_lib_opt.s',
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
    input: multi_inherit_benchmark_test,
    output: 'multi_inherit_benchmarks_no_opt.s',
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
    input: multi_inherit_benchmark_test,
    output: 'multi_inherit_benchmarks_opt.s',
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

