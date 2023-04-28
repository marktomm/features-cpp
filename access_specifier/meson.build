
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
    'access_specifier',
    [access_specifier_main, access_specifier_src],
    include_directories: [access_specifier_inc, common_inc],
    install: true,
)

access_specifier_inc_o = access_specifier_exe.extract_objects(
    access_specifier_src,
)

# executable(
#     'access_specifier_simple',
#     [access_specifier_simple],
#     objects: [access_specifier_inc_o],
#     include_directories: [access_specifier_inc, common_inc],
#     install: true,
# )

if bench.found()
    access_specifier_benchmark_test = ['bench.cpp']

    access_specifier_benchmark_google_opt_exe = executable(
        'access_specifier_benchmark_google_opt',
        [access_specifier_benchmark_test, common_src],
        objects: access_specifier_inc_o,
        include_directories: access_specifier_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        'access_specifier_benchmark_google_opt',
        access_specifier_benchmark_google_opt_exe,
    )

    access_specifier_benchmark_google_no_opt_exe = executable(
        'access_specifier_benchmark_google_no_opt',
        [access_specifier_benchmark_test, common_src],
        objects: access_specifier_inc_o,
        include_directories: access_specifier_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'access_specifier_benchmark_google_no_opt',
        access_specifier_benchmark_google_no_opt_exe,
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: access_specifier_main,
    output: 'access_specifier_main.s',
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
    'gen_asm_lib',
    input: access_specifier_src,
    output: 'access_specifier_lib.s',
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
