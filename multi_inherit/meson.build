
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
multi_inherit_inc = include_directories(currentinc)
multi_inherit_main = ['src/main.cpp']
# multi_inherit_simple = ['src/user_simple.cpp']
multi_inherit_src = [
    'src/lib.cpp',
]

multi_inherit_exe = executable(
    'multi_inherit',
    [multi_inherit_main, multi_inherit_src],
    include_directories: [multi_inherit_inc, common_inc],
    install: true,
)

multi_inherit_inc_o = multi_inherit_exe.extract_objects(
    multi_inherit_src,
)

# executable(
#     'multi_inherit_simple',
#     [multi_inherit_simple],
#     objects: [multi_inherit_inc_o],
#     include_directories: [multi_inherit_inc, common_inc],
#     install: true,
# )

if bench.found()
    multi_inherit_benchmark_test = ['bench.cpp']

    multi_inherit_benchmark_google_opt_exe = executable(
        'multi_inherit_benchmark_google_opt',
        [multi_inherit_benchmark_test, common_src],
        objects: multi_inherit_inc_o,
        include_directories: multi_inherit_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        'multi_inherit_benchmark_google_opt',
        multi_inherit_benchmark_google_opt_exe,
        suite: 'multi_inherit',
    )

    multi_inherit_benchmark_google_no_opt_exe = executable(
        'multi_inherit_benchmark_google_no_opt',
        [multi_inherit_benchmark_test, common_src],
        objects: multi_inherit_inc_o,
        include_directories: multi_inherit_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'multi_inherit_benchmark_google_no_opt',
        multi_inherit_benchmark_google_no_opt_exe,
        suite: 'multi_inherit',
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: multi_inherit_main,
    output: 'multi_inherit_main.s',
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
    input: multi_inherit_main,
    output: 'multi_inherit_main_opt.s',
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
    'gen_asm_lib',
    input: multi_inherit_src,
    output: 'multi_inherit_lib.s',
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
    input: multi_inherit_src,
    output: 'multi_inherit_lib_opt.s',
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
