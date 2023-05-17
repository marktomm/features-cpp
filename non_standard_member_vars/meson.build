
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
non_standard_member_vars_inc = include_directories(currentinc)
non_standard_member_vars_main = ['src/main.cpp']
non_standard_member_vars_perf = ['src/perf.cpp']
non_standard_member_vars_src = [
    'src/lib.cpp',
]

non_standard_member_vars_exe = executable(
    'non_standard_member_vars_opt',
    [non_standard_member_vars_main, non_standard_member_vars_src],
    include_directories: [non_standard_member_vars_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

non_standard_member_vars_exe_no_opt = executable(
    'non_standard_member_vars_no_opt',
    [non_standard_member_vars_main, non_standard_member_vars_src],
    include_directories: [non_standard_member_vars_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

non_standard_member_vars_inc_opt_o = non_standard_member_vars_exe.extract_objects(
    non_standard_member_vars_src,
)

non_standard_member_vars_main_opt_o = non_standard_member_vars_exe.extract_objects(
    non_standard_member_vars_main,
)

non_standard_member_vars_inc_o = non_standard_member_vars_inc_opt_o

non_standard_member_vars_inc_no_opt_o = non_standard_member_vars_exe_no_opt.extract_objects(
    non_standard_member_vars_src,
)

non_standard_member_vars_main_no_opt_o = non_standard_member_vars_exe_no_opt.extract_objects(
    non_standard_member_vars_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

non_standard_member_vars_exe_sanitize = executable(
    'non_standard_member_vars_opt_sanitize',
    include_directories: [non_standard_member_vars_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        non_standard_member_vars_main_opt_o, 
        non_standard_member_vars_inc_opt_o, 
        common_inc_opt_o
    ],
)

non_standard_member_vars_exe_no_opt_sanitize = executable(
    'non_standard_member_vars_no_opt_sanitize',
    include_directories: [non_standard_member_vars_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        non_standard_member_vars_main_no_opt_o, 
        non_standard_member_vars_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

non_standard_member_vars_exe_perf = executable(
    'non_standard_member_vars_opt_perf',
    [non_standard_member_vars_perf],
    include_directories: [non_standard_member_vars_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-pg'],
    dependencies: [bench, thread],
    objects: [
        non_standard_member_vars_inc_opt_o, 
        common_inc_opt_o
    ],
)

non_standard_member_vars_exe_no_opt_perf = executable(
    'non_standard_member_vars_no_opt_perf',
    [non_standard_member_vars_perf],
    include_directories: [non_standard_member_vars_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-pg',],
    dependencies: [bench, thread],
    objects: [
        non_standard_member_vars_inc_no_opt_o, 
        common_inc_no_opt_o
    ],
)

if bench.found()
    non_standard_member_vars_benchmark_test = ['bench.cpp']

    non_standard_member_vars_benchmark_google_opt_exe = executable(
        'non_standard_member_vars_benchmark_google_opt',
        [non_standard_member_vars_benchmark_test],
        objects: [non_standard_member_vars_inc_opt_o, common_inc_opt_o],
        include_directories: [non_standard_member_vars_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'non_standard_member_vars_benchmark_google_opt',
        non_standard_member_vars_benchmark_google_opt_exe,
        suite: 'non_standard_member_vars',
        timeout: 0,
    )

    non_standard_member_vars_benchmark_google_no_opt_exe = executable(
        'non_standard_member_vars_benchmark_google_no_opt',
        [non_standard_member_vars_benchmark_test],
        objects: [non_standard_member_vars_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [non_standard_member_vars_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'non_standard_member_vars_benchmark_google_no_opt',
        non_standard_member_vars_benchmark_google_no_opt_exe,
        suite: 'non_standard_member_vars',
        timeout: 0,
    )

    custom_target(
        'bench_non_standard_member_vars',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite non_standard_member_vars && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            non_standard_member_vars_benchmark_google_no_opt_exe,
            non_standard_member_vars_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: non_standard_member_vars_main,
    output: 'non_standard_member_vars_main_no_opt.s',
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
    input: non_standard_member_vars_main,
    output: 'non_standard_member_vars_main_opt.s',
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
    input: non_standard_member_vars_src,
    output: 'non_standard_member_vars_lib_no_opt.s',
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
    input: non_standard_member_vars_src,
    output: 'non_standard_member_vars_lib_opt.s',
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
    input: non_standard_member_vars_benchmark_test,
    output: 'non_standard_member_vars_benchmarks_no_opt.s',
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
    input: non_standard_member_vars_benchmark_test,
    output: 'non_standard_member_vars_benchmarks_opt.s',
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

