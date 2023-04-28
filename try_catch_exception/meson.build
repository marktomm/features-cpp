
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
try_catch_exception_inc = include_directories(currentinc)
try_catch_exception_main = ['src/main.cpp']
# try_catch_exception_simple = ['src/user_simple.cpp']
try_catch_exception_src = [
    'src/lib.cpp',
]

try_catch_exception_exe = executable(
    'try_catch_exception',
    [try_catch_exception_main, try_catch_exception_src],
    include_directories: [try_catch_exception_inc, common_inc],
    install: true,
)

try_catch_exception_inc_o = try_catch_exception_exe.extract_objects(
    try_catch_exception_src,
)

# executable(
#     'try_catch_exception_simple',
#     [try_catch_exception_simple],
#     objects: [try_catch_exception_inc_o],
#     include_directories: [try_catch_exception_inc, common_inc],
#     install: true,
# )

if bench.found()
    try_catch_exception_benchmark_test = ['bench.cpp']

    try_catch_exception_benchmark_google_opt_exe = executable(
        'try_catch_exception_benchmark_google_opt',
        [try_catch_exception_benchmark_test, common_src],
        objects: try_catch_exception_inc_o,
        include_directories: try_catch_exception_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        'try_catch_exception_benchmark_google_opt',
        try_catch_exception_benchmark_google_opt_exe,
        suite: 'try_catch_exception',
    )

    try_catch_exception_benchmark_google_no_opt_exe = executable(
        'try_catch_exception_benchmark_google_no_opt',
        [try_catch_exception_benchmark_test, common_src],
        objects: try_catch_exception_inc_o,
        include_directories: try_catch_exception_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'try_catch_exception_benchmark_google_no_opt',
        try_catch_exception_benchmark_google_no_opt_exe,
        suite: 'try_catch_exception',
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: try_catch_exception_main,
    output: 'try_catch_exception_main.s',
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
    input: try_catch_exception_main,
    output: 'try_catch_exception_main_opt.s',
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
    input: try_catch_exception_src,
    output: 'try_catch_exception_lib.s',
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
    input: try_catch_exception_src,
    output: 'try_catch_exception_lib_opt.s',
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
