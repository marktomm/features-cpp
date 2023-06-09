
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
trivial_type_inc = include_directories(currentinc)
trivial_type_main = ['src/main.cpp']
trivial_type_perf = ['src/perf.cpp']
trivial_type_src = [
    'src/lib.cpp',
]

trivial_type_exe = executable(
    'trivial_type_opt',
    [trivial_type_main, trivial_type_src],
    include_directories: [trivial_type_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

trivial_type_exe_no_opt = executable(
    'trivial_type_no_opt',
    [trivial_type_main, trivial_type_src],
    include_directories: [trivial_type_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

trivial_type_inc_opt_o = trivial_type_exe.extract_objects(
    trivial_type_src,
)

trivial_type_main_opt_o = trivial_type_exe.extract_objects(
    trivial_type_main,
)

trivial_type_inc_o = trivial_type_inc_opt_o

trivial_type_inc_no_opt_o = trivial_type_exe_no_opt.extract_objects(
    trivial_type_src,
)

trivial_type_main_no_opt_o = trivial_type_exe_no_opt.extract_objects(
    trivial_type_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

trivial_type_exe_sanitize = executable(
    'trivial_type_opt_sanitize',
    include_directories: [trivial_type_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        trivial_type_main_opt_o, 
        trivial_type_inc_opt_o, 
        common_inc_opt_o
    ],
)

trivial_type_exe_no_opt_sanitize = executable(
    'trivial_type_no_opt_sanitize',
    include_directories: [trivial_type_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        trivial_type_main_no_opt_o, 
        trivial_type_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

trivial_type_exe_perf = executable(
    'trivial_type_opt_perf',
    [trivial_type_perf],
    include_directories: [trivial_type_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-pg'],
    dependencies: [bench, thread],
    objects: [
        trivial_type_inc_opt_o, 
        common_inc_opt_o
    ],
)

trivial_type_exe_no_opt_perf = executable(
    'trivial_type_no_opt_perf',
    [trivial_type_perf],
    include_directories: [trivial_type_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-pg',],
    dependencies: [bench, thread],
    objects: [
        trivial_type_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    trivial_type_benchmark_test = ['bench.cpp']

    trivial_type_benchmark_google_opt_exe = executable(
        'trivial_type_benchmark_google_opt',
        [trivial_type_benchmark_test],
        objects: [trivial_type_inc_opt_o, common_inc_opt_o],
        include_directories: [trivial_type_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'trivial_type_benchmark_google_opt',
        trivial_type_benchmark_google_opt_exe,
        suite: 'trivial_type',
        timeout: 0,
    )

    trivial_type_benchmark_google_no_opt_exe = executable(
        'trivial_type_benchmark_google_no_opt',
        [trivial_type_benchmark_test],
        objects: [trivial_type_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [trivial_type_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'trivial_type_benchmark_google_no_opt',
        trivial_type_benchmark_google_no_opt_exe,
        suite: 'trivial_type',
        timeout: 0,
    )

    custom_target(
        'bench_trivial_type',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite trivial_type && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            trivial_type_benchmark_google_no_opt_exe,
            trivial_type_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: trivial_type_main,
    output: 'trivial_type_main_no_opt.s',
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
    input: trivial_type_main,
    output: 'trivial_type_main_opt.s',
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
    input: trivial_type_src,
    output: 'trivial_type_lib_no_opt.s',
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
    input: trivial_type_src,
    output: 'trivial_type_lib_opt.s',
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
    input: trivial_type_benchmark_test,
    output: 'trivial_type_benchmarks_no_opt.s',
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
    input: trivial_type_benchmark_test,
    output: 'trivial_type_benchmarks_opt.s',
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

