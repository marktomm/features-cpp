
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
non_standard_member_vars_inc = include_directories(currentinc)
non_standard_member_vars_main = ['src/main.cpp']
# non_standard_member_vars_simple = ['src/user_simple.cpp']
non_standard_member_vars_src = [
    'src/lib.cpp',
]

non_standard_member_vars_exe = executable(
    'non_standard_member_vars',
    [non_standard_member_vars_main, non_standard_member_vars_src],
    include_directories: [non_standard_member_vars_inc, common_inc],
    install: true,
)

non_standard_member_vars_inc_o = non_standard_member_vars_exe.extract_objects(
    non_standard_member_vars_src,
)

# executable(
#     'non_standard_member_vars_simple',
#     [non_standard_member_vars_simple],
#     objects: [non_standard_member_vars_inc_o],
#     include_directories: [non_standard_member_vars_inc, common_inc],
#     install: true,
# )

if bench.found()
    non_standard_member_vars_benchmark_test = ['bench.cpp']

    non_standard_member_vars_benchmark_google_opt_exe = executable(
        'non_standard_member_vars_benchmark_google_opt',
        [non_standard_member_vars_benchmark_test, common_src],
        objects: non_standard_member_vars_inc_o,
        include_directories: non_standard_member_vars_inc,
        dependencies: [bench, thread],
    )

    test(
        'non_standard_member_vars_benchmark_google_opt',
        non_standard_member_vars_benchmark_google_opt_exe,
        is_parallel: false,
    )

    non_standard_member_vars_benchmark_google_no_opt_exe = executable(
        'non_standard_member_vars_benchmark_google_no_opt',
        [non_standard_member_vars_benchmark_test, common_src],
        objects: non_standard_member_vars_inc_o,
        include_directories: non_standard_member_vars_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    test(
        'non_standard_member_vars_benchmark_google_no_opt',
        non_standard_member_vars_benchmark_google_no_opt_exe,
        is_parallel: false,
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: non_standard_member_vars_main,
    output: 'non_standard_member_vars_main.s',
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
