# features-cpp

build requirements: meson, gcc, binutils (objdump), libasan

```shell
meson setup builddir
./start.sh
```

base requirements

formatting requirements: clang-format, muon

documentation requirements: doxygen, graphviz,

profiling nice-to-haves: heaptrack, valgrind

# ouput: join.sh

Create one file code listing for feature main code

```shell
./join.sh poly
ls poly/amalgamation.cpp
```

# output: asm_prettify.sh

Get assmebly

```shell
./asm_prettify.sh poly lib opt
./asm_prettify.sh poly main opt
```

# dev: new_feature.sh

Add new feature dir and code boilerplate

```shell
./new_feature.sh feature_name
# creates dir feature_name
# running ./start.sh will build it
```

```shell
./new_feature.sh feature_name regen_meson
# regenerates meson.build file in feature subdir
# this is required only after changes in new_feaure.sh
# to rebuild meson.build for all features run
./regen_all_features.sh
```

# dev: meson_fmt.sh

Syntax check and format meson.build files

# output: parsing for docs

```shell
sort bench_output.txt | sed -E 's/(^.*[^0-9])[0-9]*$/\1/'
```

# output: google benchmark compare two bechmark runs

required: pip3

```shell
cd benchmark/tools
pip3 install -r requirements.txt
./compare.py benchmarks  ../../builddir/poly/poly_benchmark_google_no_opt ../../builddir/poly/poly_benchmark_google_no_opt
```
