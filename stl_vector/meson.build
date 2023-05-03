
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
stl_vector_inc = include_directories(currentinc)
stl_vector_main = ['src/main.cpp']
# stl_vector_simple = ['src/user_simple.cpp']
stl_vector_src = [
    'src/lib.cpp',
]

stl_vector_exe = executable(
    'stl_vector_opt',
    [stl_vector_main, stl_vector_src],
    include_directories: [stl_vector_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

stl_vector_exe_no_opt = executable(
    'stl_vector_no_opt',
    [stl_vector_main, stl_vector_src],
    include_directories: [stl_vector_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_opt_o],
)

stl_vector_inc_opt_o = stl_vector_exe.extract_objects(
    stl_vector_src,
)

stl_vector_main_opt_o = stl_vector_exe.extract_objects(
    stl_vector_main,
)

stl_vector_inc_o = stl_vector_inc_opt_o

stl_vector_inc_no_opt_o = stl_vector_exe_no_opt.extract_objects(
    stl_vector_src,
)

stl_vector_main_no_opt_o = stl_vector_exe_no_opt.extract_objects(
    stl_vector_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

stl_vector_exe_sanitize = executable(
    'stl_vector_opt_sanitize',
    include_directories: [stl_vector_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [stl_vector_main_opt_o, stl_vector_inc_opt_o, common_inc_opt_o],
)

stl_vector_exe_no_opt_sanitize = executable(
    'stl_vector_no_opt_sanitize',
    include_directories: [stl_vector_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [stl_vector_main_no_opt_o, stl_vector_inc_no_opt_o, common_inc_opt_o],
)

if bench.found()
    stl_vector_benchmark_test = ['bench.cpp']

    stl_vector_benchmark_google_opt_exe = executable(
        'stl_vector_benchmark_google_opt',
        [stl_vector_benchmark_test],
        objects: [stl_vector_inc_opt_o, common_inc_opt_o],
        include_directories: [stl_vector_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'stl_vector_benchmark_google_opt',
        stl_vector_benchmark_google_opt_exe,
        suite: 'stl_vector',
        timeout: 0,
    )

    stl_vector_benchmark_google_no_opt_exe = executable(
        'stl_vector_benchmark_google_no_opt',
        [stl_vector_benchmark_test],
        objects: [stl_vector_inc_no_opt_o, common_inc_opt_o],
        include_directories: [stl_vector_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'stl_vector_benchmark_google_no_opt',
        stl_vector_benchmark_google_no_opt_exe,
        suite: 'stl_vector',
        timeout: 0,
    )

    custom_target(
        'bench_stl_vector',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite stl_vector && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            stl_vector_benchmark_google_no_opt_exe,
            stl_vector_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: stl_vector_main,
    output: 'stl_vector_main_no_opt.s',
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
    input: stl_vector_main,
    output: 'stl_vector_main_opt.s',
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
    input: stl_vector_src,
    output: 'stl_vector_lib_no_opt.s',
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
    input: stl_vector_src,
    output: 'stl_vector_lib_opt.s',
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
