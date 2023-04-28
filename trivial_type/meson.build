
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
trivial_type_inc = include_directories(currentinc)
trivial_type_main = ['src/main.cpp']
# trivial_type_simple = ['src/user_simple.cpp']
trivial_type_src = [
    'src/lib.cpp',
]

trivial_type_exe = executable(
    'trivial_type',
    [trivial_type_main, trivial_type_src],
    include_directories: [trivial_type_inc, common_inc],
    install: true,
)

trivial_type_inc_o = trivial_type_exe.extract_objects(
    trivial_type_src,
)

# executable(
#     'trivial_type_simple',
#     [trivial_type_simple],
#     objects: [trivial_type_inc_o],
#     include_directories: [trivial_type_inc, common_inc],
#     install: true,
# )

if bench.found()
    trivial_type_benchmark_test = ['bench.cpp']

    trivial_type_benchmark_google_opt_exe = executable(
        'trivial_type_benchmark_google_opt',
        [trivial_type_benchmark_test, common_src],
        objects: trivial_type_inc_o,
        include_directories: trivial_type_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        'trivial_type_benchmark_google_opt',
        trivial_type_benchmark_google_opt_exe,
        suite: 'trivial_type',
    )

    trivial_type_benchmark_google_no_opt_exe = executable(
        'trivial_type_benchmark_google_no_opt',
        [trivial_type_benchmark_test, common_src],
        objects: trivial_type_inc_o,
        include_directories: trivial_type_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'trivial_type_benchmark_google_no_opt',
        trivial_type_benchmark_google_no_opt_exe,
        suite: 'trivial_type',
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: trivial_type_main,
    output: 'trivial_type_main.s',
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
    input: trivial_type_main,
    output: 'trivial_type_main_opt.s',
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
    input: trivial_type_src,
    output: 'trivial_type_lib.s',
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
    input: trivial_type_src,
    output: 'trivial_type_lib_opt.s',
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
