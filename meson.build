project(
    'features-cpp',
    'cpp',
    default_options: [
        'strip=true',
        'c_std=c11',
        'cpp_std=c++17',
        'optimization=3',
        'warning_level=3',
        'werror=true',
        'cpp_args=-Wshadow -Wconversion -Wpedantic',
        'debug=false',
    ],
)

# common_inc = include_directories('common/', './')
common_inc = []
common_src = []

bench = dependency('benchmark', required: false)
thread = dependency('threads')

subdir('access_specifier')