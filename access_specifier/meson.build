
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
access_specifier_inc = include_directories(currentinc)
access_specifier_main = ['src/main.cpp']
# access_specifier_simple = ['src/user_simple.cpp']
access_specifier_src = [
    'src/lib.cpp',
]

access_specifier_exe = executable(
    'access_specifier_opt',
    [access_specifier_main, access_specifier_src],
    include_directories: [access_specifier_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
)

access_specifier_exe_no_opt = executable(
    'access_specifier_no_opt',
    [access_specifier_main, access_specifier_src],
    include_directories: [access_specifier_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
)

access_specifier_inc_opt_o = access_specifier_exe.extract_objects(
    access_specifier_src,
)

access_specifier_inc_no_opt_o = access_specifier_exe_no_opt.extract_objects(
    access_specifier_src,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

access_specifier_exe_sanitize = executable(
    'access_specifier_opt_sanitize',
    [access_specifier_main, access_specifier_src],
    include_directories: [access_specifier_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    # objects: [ access_specifier_inc_opt_o ],
)

access_specifier_exe_no_opt_sanitize = executable(
    'access_specifier_no_opt_sanitize',
    [access_specifier_main, access_specifier_src],
    include_directories: [access_specifier_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    # objects: [ access_specifier_inc_opt_o ],
)

# executable(
#     'access_specifier_simple',
#     [access_specifier_simple],
#     objects: [access_specifier_inc_opt_o],
#     include_directories: [access_specifier_inc, common_inc],
#     install: true,
# )

if bench.found()
    access_specifier_benchmark_test = ['bench.cpp']

    access_specifier_benchmark_google_opt_exe = executable(
        'access_specifier_benchmark_google_opt',
        [access_specifier_benchmark_test, common_src],
        objects: access_specifier_inc_opt_o,
        include_directories: access_specifier_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        'access_specifier_benchmark_google_opt',
        access_specifier_benchmark_google_opt_exe,
        suite: 'access_specifier',
        timeout: 0,
    )

    access_specifier_benchmark_google_no_opt_exe = executable(
        'access_specifier_benchmark_google_no_opt',
        [access_specifier_benchmark_test, common_src],
        objects: access_specifier_inc_no_opt_o,
        include_directories: access_specifier_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'access_specifier_benchmark_google_no_opt',
        access_specifier_benchmark_google_no_opt_exe,
        suite: 'access_specifier',
        timeout: 0,
    )

    custom_target(
        'bench_access_specifier',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite access_specifier && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            access_specifier_benchmark_google_no_opt_exe,
            access_specifier_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: access_specifier_main,
    output: 'access_specifier_main_no_opt.s',
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
    input: access_specifier_main,
    output: 'access_specifier_main_opt.s',
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
    input: access_specifier_src,
    output: 'access_specifier_lib_no_opt.s',
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
    input: access_specifier_src,
    output: 'access_specifier_lib_opt.s',
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
