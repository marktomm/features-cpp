
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
    'poly',
    [poly_main, poly_src],
    include_directories: [poly_inc, common_inc],
    install: true,
)

poly_inc_o = poly_exe.extract_objects(
    poly_src,
)

# executable(
#     'poly_simple',
#     [poly_simple],
#     objects: [poly_inc_o],
#     include_directories: [poly_inc, common_inc],
#     install: true,
# )

if bench.found()
    poly_benchmark_test = ['bench.cpp']

    poly_benchmark_google_opt_exe = executable(
        'poly_benchmark_google_opt',
        [poly_benchmark_test, common_src],
        objects: poly_inc_o,
        include_directories: poly_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        'poly_benchmark_google_opt',
        poly_benchmark_google_opt_exe,
        suite: 'poly',
    )

    poly_benchmark_google_no_opt_exe = executable(
        'poly_benchmark_google_no_opt',
        [poly_benchmark_test, common_src],
        objects: poly_inc_o,
        include_directories: poly_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'poly_benchmark_google_no_opt',
        poly_benchmark_google_no_opt_exe,
        suite: 'poly',
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: poly_main,
    output: 'poly_main.s',
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
    input: poly_main,
    output: 'poly_main_opt.s',
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
    input: poly_src,
    output: 'poly_lib.s',
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
    input: poly_src,
    output: 'poly_lib_opt.s',
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
