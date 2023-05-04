
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
lambda_fns_inc = include_directories(currentinc)
lambda_fns_main = ['src/main.cpp']
# lambda_fns_simple = ['src/user_simple.cpp']
lambda_fns_src = [
    'src/lib.cpp',
]

lambda_fns_exe = executable(
    'lambda_fns_opt',
    [lambda_fns_main, lambda_fns_src],
    include_directories: [lambda_fns_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

lambda_fns_exe_no_opt = executable(
    'lambda_fns_no_opt',
    [lambda_fns_main, lambda_fns_src],
    include_directories: [lambda_fns_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

lambda_fns_inc_opt_o = lambda_fns_exe.extract_objects(
    lambda_fns_src,
)

lambda_fns_main_opt_o = lambda_fns_exe.extract_objects(
    lambda_fns_main,
)

lambda_fns_inc_o = lambda_fns_inc_opt_o

lambda_fns_inc_no_opt_o = lambda_fns_exe_no_opt.extract_objects(
    lambda_fns_src,
)

lambda_fns_main_no_opt_o = lambda_fns_exe_no_opt.extract_objects(
    lambda_fns_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

lambda_fns_exe_sanitize = executable(
    'lambda_fns_opt_sanitize',
    include_directories: [lambda_fns_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [lambda_fns_main_opt_o, lambda_fns_inc_opt_o, common_inc_opt_o],
)

lambda_fns_exe_no_opt_sanitize = executable(
    'lambda_fns_no_opt_sanitize',
    include_directories: [lambda_fns_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [
        lambda_fns_main_no_opt_o,
        lambda_fns_inc_no_opt_o,
        common_inc_no_opt_o,
    ],
)

if bench.found()
    lambda_fns_benchmark_test = ['bench.cpp']

    lambda_fns_benchmark_google_opt_exe = executable(
        'lambda_fns_benchmark_google_opt',
        [lambda_fns_benchmark_test],
        objects: [lambda_fns_inc_opt_o, common_inc_opt_o],
        include_directories: [lambda_fns_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'lambda_fns_benchmark_google_opt',
        lambda_fns_benchmark_google_opt_exe,
        suite: 'lambda_fns',
        timeout: 0,
    )

    lambda_fns_benchmark_google_no_opt_exe = executable(
        'lambda_fns_benchmark_google_no_opt',
        [lambda_fns_benchmark_test],
        objects: [lambda_fns_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [lambda_fns_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'lambda_fns_benchmark_google_no_opt',
        lambda_fns_benchmark_google_no_opt_exe,
        suite: 'lambda_fns',
        timeout: 0,
    )

    custom_target(
        'bench_lambda_fns',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite lambda_fns && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            lambda_fns_benchmark_google_no_opt_exe,
            lambda_fns_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: lambda_fns_main,
    output: 'lambda_fns_main_no_opt.s',
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
    input: lambda_fns_main,
    output: 'lambda_fns_main_opt.s',
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
    input: lambda_fns_src,
    output: 'lambda_fns_lib_no_opt.s',
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
    input: lambda_fns_src,
    output: 'lambda_fns_lib_opt.s',
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
