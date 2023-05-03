
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
    'try_catch_exception_opt',
    [try_catch_exception_main, try_catch_exception_src],
    include_directories: [try_catch_exception_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    objects: [common_inc_opt_o],
)

try_catch_exception_exe_no_opt = executable(
    'try_catch_exception_no_opt',
    [try_catch_exception_main, try_catch_exception_src],
    include_directories: [try_catch_exception_inc, common_inc],
    dependencies: [bench, thread],
    install: true,
    cpp_args: ['-O0', '-g'],
    objects: [common_inc_opt_o],
)

try_catch_exception_inc_opt_o = try_catch_exception_exe.extract_objects(
    try_catch_exception_src,
)

try_catch_exception_main_opt_o = try_catch_exception_exe.extract_objects(
    try_catch_exception_main,
)

try_catch_exception_inc_o = try_catch_exception_inc_opt_o

try_catch_exception_inc_no_opt_o = try_catch_exception_exe_no_opt.extract_objects(
    try_catch_exception_src,
)

try_catch_exception_main_no_opt_o = try_catch_exception_exe_no_opt.extract_objects(
    try_catch_exception_main,
)

asandep = cpp.find_library('asan', dirs: '/usr/lib/x86_64-linux-gnu')

try_catch_exception_exe_sanitize = executable(
    'try_catch_exception_opt_sanitize',
    include_directories: [try_catch_exception_inc, common_inc],
    install: true,
    cpp_args: ['-O3', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [try_catch_exception_main_opt_o, try_catch_exception_inc_opt_o, common_inc_opt_o],
)

try_catch_exception_exe_no_opt_sanitize = executable(
    'try_catch_exception_no_opt_sanitize',
    include_directories: [try_catch_exception_inc, common_inc],
    install: true,
    cpp_args: ['-O0', '-g', '-fsanitize=address'],
    dependencies: [asandep, bench, thread],
    link_args: ['-Wl,--start-group', '-lasan', '-Wl,--end-group'],
    objects: [try_catch_exception_main_no_opt_o, try_catch_exception_inc_no_opt_o, common_inc_opt_o],
)

if bench.found()
    try_catch_exception_benchmark_test = ['bench.cpp']

    try_catch_exception_benchmark_google_opt_exe = executable(
        'try_catch_exception_benchmark_google_opt',
        [try_catch_exception_benchmark_test],
        objects: [try_catch_exception_inc_opt_o, common_inc_opt_o],
        include_directories: [try_catch_exception_inc, common_inc],
        dependencies: [bench, thread],
    )

    benchmark(
        'try_catch_exception_benchmark_google_opt',
        try_catch_exception_benchmark_google_opt_exe,
        suite: 'try_catch_exception',
        timeout: 0,
    )

    try_catch_exception_benchmark_google_no_opt_exe = executable(
        'try_catch_exception_benchmark_google_no_opt',
        [try_catch_exception_benchmark_test],
        objects: [try_catch_exception_inc_no_opt_o, common_inc_opt_o],
        include_directories: [try_catch_exception_inc, common_inc],
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'try_catch_exception_benchmark_google_no_opt',
        try_catch_exception_benchmark_google_no_opt_exe,
        suite: 'try_catch_exception',
        timeout: 0,
    )

    custom_target(
        'bench_try_catch_exception',
        command: [
            'sh',
            '-c', 'meson test --benchmark -C @BUILD_ROOT@ --suite try_catch_exception && cat @BUILD_ROOT@/meson-logs/testlog.txt',
        ],
        depends: [
            try_catch_exception_benchmark_google_no_opt_exe,
            try_catch_exception_benchmark_google_opt_exe,
        ],
        output: 'dummy_output.txt',
    )
endif

gen_asm = custom_target(
    'gen_asm_no_opt',
    input: try_catch_exception_main,
    output: 'try_catch_exception_main_no_opt.s',
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
    input: try_catch_exception_main,
    output: 'try_catch_exception_main_opt.s',
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
    input: try_catch_exception_src,
    output: 'try_catch_exception_lib_no_opt.s',
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
    input: try_catch_exception_src,
    output: 'try_catch_exception_lib_opt.s',
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
