
rootdir = '..'
currentdir = '.'
rootinc = join_paths(rootdir, 'include/')
currentinc = join_paths(currentdir, 'include/')
class_member_funcion_inc = include_directories(currentinc)
class_member_funcion_main = ['src/main.cpp']
# class_member_funcion_simple = ['src/user_simple.cpp']
class_member_funcion_src = [
    'src/lib.cpp',
]

class_member_funcion_exe = executable(
    'class_member_funcion',
    [class_member_funcion_main, class_member_funcion_src],
    include_directories: [class_member_funcion_inc, common_inc],
    install: true,
)

class_member_funcion_inc_o = class_member_funcion_exe.extract_objects(
    class_member_funcion_src,
)

# executable(
#     'class_member_funcion_simple',
#     [class_member_funcion_simple],
#     objects: [class_member_funcion_inc_o],
#     include_directories: [class_member_funcion_inc, common_inc],
#     install: true,
# )

if bench.found()
    class_member_funcion_benchmark_test = ['bench.cpp']

    class_member_funcion_benchmark_google_opt_exe = executable(
        'class_member_funcion_benchmark_google_opt',
        [class_member_funcion_benchmark_test, common_src],
        objects: class_member_funcion_inc_o,
        include_directories: class_member_funcion_inc,
        dependencies: [bench, thread],
    )

    benchmark(
        'class_member_funcion_benchmark_google_opt',
        class_member_funcion_benchmark_google_opt_exe,
    )

    class_member_funcion_benchmark_google_no_opt_exe = executable(
        'class_member_funcion_benchmark_google_no_opt',
        [class_member_funcion_benchmark_test, common_src],
        objects: class_member_funcion_inc_o,
        include_directories: class_member_funcion_inc,
        dependencies: [bench, thread],
        cpp_args: ['-O0', '-g'],
    )

    benchmark(
        'class_member_funcion_benchmark_google_no_opt',
        class_member_funcion_benchmark_google_no_opt_exe,
    )
endif

gen_asm = custom_target(
    'gen_asm',
    input: class_member_funcion_main,
    output: 'class_member_funcion_main.s',
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
    input: class_member_funcion_main,
    output: 'class_member_funcion_main_opt.s',
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
    input: class_member_funcion_src,
    output: 'class_member_funcion_lib.s',
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
    input: class_member_funcion_src,
    output: 'class_member_funcion_lib_opt.s',
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
