
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
poly_inc = include_directories(currentinc)
poly_main = ['src/main.cpp']
# poly_simple = ['src/user_simple.cpp']
poly_src = [
    'src/lib.cpp',
]

poly_exe = executable(
    'poly_opt',
    [poly_main, poly_src],
    include_directories: [poly_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

poly_exe_no_opt = executable(
    'poly_no_opt',
    [poly_main, poly_src],
    include_directories: [poly_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_no_opt_o],
)

poly_inc_opt_o = poly_exe.extract_objects(
    poly_src,
)

poly_main_opt_o = poly_exe.extract_objects(
    poly_main,
)

poly_inc_o = poly_inc_opt_o

poly_inc_no_opt_o = poly_exe_no_opt.extract_objects(
    poly_src,
)

poly_main_no_opt_o = poly_exe_no_opt.extract_objects(
    poly_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

poly_exe_sanitize = executable(
    'poly_opt_sanitize',
    include_directories: [poly_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [poly_main_opt_o, poly_inc_opt_o, common_inc_opt_o],
)

poly_exe_no_opt_sanitize = executable(
    'poly_no_opt_sanitize',
    include_directories: [poly_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [poly_main_no_opt_o, poly_inc_no_opt_o, common_inc_no_opt_o],
)

if bench.found()
    poly_benchmark_test = ['bench.cpp']

    poly_benchmark_google_opt_exe = executable(
        'poly_benchmark_google_opt',
        [poly_benchmark_test],
        objects: [poly_inc_opt_o, common_inc_opt_o],
        include_directories: [poly_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'poly_benchmark_google_opt',
        poly_benchmark_google_opt_exe,
        suite: 'poly',
        timeout: 0,
    )

    poly_benchmark_google_no_opt_exe = executable(
        'poly_benchmark_google_no_opt',
        [poly_benchmark_test],
        objects: [poly_inc_no_opt_o, common_inc_no_opt_o],
        include_directories: [poly_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'poly_benchmark_google_no_opt',
        poly_benchmark_google_no_opt_exe,
        suite: 'poly',
        timeout: 0,
    )

    custom_target(
        'bench_poly',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite poly && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            poly_benchmark_google_no_opt_exe,
            poly_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: poly_main,
    output: 'poly_main_no_opt.s',
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
    input: poly_main,
    output: 'poly_main_opt.s',
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
    input: poly_src,
    output: 'poly_lib_no_opt.s',
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
    input: poly_src,
    output: 'poly_lib_opt.s',
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
