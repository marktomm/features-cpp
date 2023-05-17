
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
rvo_inc = include_directories(currentinc)
rvo_main = ['src/main.cpp']
rvo_perf = ['src/perf.cpp']
rvo_src = [
    'src/lib.cpp',
]

rvo_exe = executable(
    'rvo_opt',
    [rvo_main, rvo_src],
    include_directories: [rvo_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

rvo_exe_no_opt = executable(
    'rvo_no_opt',
    [rvo_main, rvo_src],
    include_directories: [rvo_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

rvo_inc_opt_o = rvo_exe.extract_objects(
    rvo_src,
)

rvo_main_opt_o = rvo_exe.extract_objects(
    rvo_main,
)

rvo_inc_o = rvo_inc_opt_o

rvo_inc_no_opt_o = rvo_exe_no_opt.extract_objects(
    rvo_src,
)

rvo_main_no_opt_o = rvo_exe_no_opt.extract_objects(
    rvo_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

rvo_exe_sanitize = executable(
    'rvo_opt_sanitize',
    include_directories: [rvo_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        rvo_main_opt_o, 
        rvo_inc_opt_o, 
        common_inc_opt_o
    ],
)

rvo_exe_no_opt_sanitize = executable(
    'rvo_no_opt_sanitize',
    include_directories: [rvo_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        rvo_main_no_opt_o, 
        rvo_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

rvo_exe_perf = executable(
    'rvo_opt_perf',
    [rvo_perf],
    include_directories: [rvo_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-pg'],
    dependencies: [bench, thread],
    objects: [
        rvo_inc_opt_o, 
        common_inc_opt_o
    ],
)

rvo_exe_no_opt_perf = executable(
    'rvo_no_opt_perf',
    [rvo_perf],
    include_directories: [rvo_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-pg',],
    dependencies: [bench, thread],
    objects: [
        rvo_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    rvo_benchmark_test = ['bench.cpp']

    rvo_benchmark_google_opt_exe = executable(
        'rvo_benchmark_google_opt',
        [rvo_benchmark_test],
        objects: [rvo_inc_opt_o, common_inc_opt_o],
        include_directories: [rvo_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'rvo_benchmark_google_opt',
        rvo_benchmark_google_opt_exe,
        suite: 'rvo',
        timeout: 0,
    )

    rvo_benchmark_google_no_opt_exe = executable(
        'rvo_benchmark_google_no_opt',
        [rvo_benchmark_test],
        objects: [rvo_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [rvo_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'rvo_benchmark_google_no_opt',
        rvo_benchmark_google_no_opt_exe,
        suite: 'rvo',
        timeout: 0,
    )

    custom_target(
        'bench_rvo',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite rvo && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            rvo_benchmark_google_no_opt_exe,
            rvo_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: rvo_main,
    output: 'rvo_main_no_opt.s',
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
    input: rvo_main,
    output: 'rvo_main_opt.s',
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
    input: rvo_src,
    output: 'rvo_lib_no_opt.s',
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
    input: rvo_src,
    output: 'rvo_lib_opt.s',
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
    input: rvo_benchmark_test,
    output: 'rvo_benchmarks_no_opt.s',
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
    input: rvo_benchmark_test,
    output: 'rvo_benchmarks_opt.s',
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

