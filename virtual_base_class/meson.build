
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
virtual_base_class_inc = include_directories(currentinc)
virtual_base_class_main = ['src/main.cpp']
# virtual_base_class_simple = ['src/user_simple.cpp']
virtual_base_class_src = [
    'src/lib.cpp',
]

virtual_base_class_exe = executable(
    'virtual_base_class',
    [virtual_base_class_main, virtual_base_class_src],
    include_directories: [virtual_base_class_inc, common_inc],
    install: true,
)

virtual_base_class_inc_o = virtual_base_class_exe.extract_objects(
    virtual_base_class_src,
)

# executable(
#     'virtual_base_class_simple',
#     [virtual_base_class_simple],
#     objects: [virtual_base_class_inc_o],
#     include_directories: [virtual_base_class_inc, common_inc],
#     install: true,
# )

if bench.found()
    virtual_base_class_benchmark_test = ['bench.cpp']

    virtual_base_class_benchmark_google_opt_exe = executable(
        'virtual_base_class_benchmark_google_opt',
        [virtual_base_class_benchmark_test, common_src],
        objects: virtual_base_class_inc_o,
        include_directories: virtual_base_class_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        'virtual_base_class_benchmark_google_opt',
        virtual_base_class_benchmark_google_opt_exe,
        suite: 'virtual_base_class',
    )

    virtual_base_class_benchmark_google_no_opt_exe = executable(
        'virtual_base_class_benchmark_google_no_opt',
        [virtual_base_class_benchmark_test, common_src],
        objects: virtual_base_class_inc_o,
        include_directories: virtual_base_class_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'virtual_base_class_benchmark_google_no_opt',
        virtual_base_class_benchmark_google_no_opt_exe,
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: virtual_base_class_main,
    output: 'virtual_base_class_main.s',
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
    input: virtual_base_class_main,
    output: 'virtual_base_class_main_opt.s',
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
    input: virtual_base_class_src,
    output: 'virtual_base_class_lib.s',
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
    input: virtual_base_class_src,
    output: 'virtual_base_class_lib_opt.s',
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
