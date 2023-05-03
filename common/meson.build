
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
common_inc = include_directories(currentinc)
common_main = ['src/main.cpp']
# common_simple = ['src/user_simple.cpp']
common_src = [
    'src/lib.cpp',
]

common_exe = executable(
    'common_opt',
    [common_main, common_src],
    include_directories: [common_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
)

common_exe_no_opt = executable(
    'common_no_opt',
    [common_main, common_src],
    include_directories: [common_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
)

common_inc_opt_o = common_exe.extract_objects(
    common_src,
)

common_main_opt_o = common_exe.extract_objects(
    common_main,
)

common_inc_o = common_inc_opt_o

common_inc_no_opt_o = common_exe_no_opt.extract_objects(
    common_src,
)

common_main_no_opt_o = common_exe_no_opt.extract_objects(
    common_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

common_exe_sanitize = executable(
    'common_opt_sanitize',
    include_directories: [common_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [common_main_opt_o, common_inc_opt_o, common_inc_opt_o],
)

common_exe_no_opt_sanitize = executable(
    'common_no_opt_sanitize',
    include_directories: [common_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [common_main_no_opt_o, common_inc_no_opt_o, common_inc_opt_o],
)

if bench.found()
    common_benchmark_test = ['bench.cpp']

    common_benchmark_google_opt_exe = executable(
        'common_benchmark_google_opt',
        [common_benchmark_test],
        objects: [common_inc_opt_o, common_inc_opt_o],
        include_directories: [common_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'common_benchmark_google_opt',
        common_benchmark_google_opt_exe,
        suite: 'common',
        timeout: 0,
    )

    common_benchmark_google_no_opt_exe = executable(
        'common_benchmark_google_no_opt',
        [common_benchmark_test],
        objects: [common_inc_no_opt_o, common_inc_opt_o],
        include_directories: [common_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'common_benchmark_google_no_opt',
        common_benchmark_google_no_opt_exe,
        suite: 'common',
        timeout: 0,
    )

    custom_target(
        'bench_common',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite common && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            common_benchmark_google_no_opt_exe,
            common_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: common_main,
    output: 'common_main_no_opt.s',
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
    input: common_main,
    output: 'common_main_opt.s',
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
    input: common_src,
    output: 'common_lib_no_opt.s',
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
    input: common_src,
    output: 'common_lib_opt.s',
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
