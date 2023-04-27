access_specifier_inc = include_directories('include')
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

    test(
        'access_specifier_benchmark_google_opt',
        access_specifier_benchmark_google_opt_exe,
        is_parallel: false,
    )

    access_specifier_benchmark_google_no_opt_exe = executable(
        'access_specifier_benchmark_google_no_opt',
        [access_specifier_benchmark_test, common_src],
        objects: access_specifier_inc_o,
        include_directories: access_specifier_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    test(
        'access_specifier_benchmark_google_no_opt',
        access_specifier_benchmark_google_no_opt_exe,
        is_parallel: false,
    )
endif
