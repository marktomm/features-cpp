
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
    'virtual_base_class_opt',
    [virtual_base_class_main, virtual_base_class_src],
    include_directories: [virtual_base_class_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
)

virtual_base_class_exe_no_opt = executable(
    'virtual_base_class_no_opt',
    [virtual_base_class_main, virtual_base_class_src],
    include_directories: [virtual_base_class_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
)

virtual_base_class_inc_opt_o = virtual_base_class_exe.extract_objects(
    virtual_base_class_src,
)

virtual_base_class_inc_no_opt_o = virtual_base_class_exe_no_opt.extract_objects(
    virtual_base_class_src,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

virtual_base_class_exe_sanitize = executable(
    'virtual_base_class_opt_sanitize',
    [virtual_base_class_main, virtual_base_class_src],
    include_directories: [virtual_base_class_inc, common_inc],
    install: true,
    cpp_args: ['-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    # objects: [ virtual_base_class_inc_opt_o ],
)

virtual_base_class_exe_no_opt_sanitize = executable(
    'virtual_base_class_no_opt_sanitize',
    [virtual_base_class_main, virtual_base_class_src],
    include_directories: [virtual_base_class_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    # objects: [ virtual_base_class_inc_opt_o ],
)

# executable(
#     'virtual_base_class_simple',
#     [virtual_base_class_simple],
#     objects: [virtual_base_class_inc_opt_o],
#     include_directories: [virtual_base_class_inc, common_inc],
#     install: true,
# )

if bench.found()
    virtual_base_class_benchmark_test = ['bench.cpp']

    virtual_base_class_benchmark_google_opt_exe = executable(
        'virtual_base_class_benchmark_google_opt',
        [virtual_base_class_benchmark_test, common_src],
        objects: virtual_base_class_inc_opt_o,
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
        objects: virtual_base_class_inc_no_opt_o,
        include_directories: virtual_base_class_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'virtual_base_class_benchmark_google_no_opt',
        virtual_base_class_benchmark_google_no_opt_exe,
        suite: 'virtual_base_class',
    )

    custom_target(
        'bench_virtual_base_class',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite virtual_base_class && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            virtual_base_class_benchmark_google_no_opt_exe,
            virtual_base_class_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: virtual_base_class_main,
    output: 'virtual_base_class_main_no_opt.s',
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
    'gen_asm_lib_no_opt',
    input: virtual_base_class_src,
    output: 'virtual_base_class_lib_no_opt.s',
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
