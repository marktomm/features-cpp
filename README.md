# features-cpp

build requirements: meson and gcc

```shell
./start.sh
```

developemnt requirements: clang-format, muon, doxygen, graphviz

# join.sh

Create one file code listing for feature main code

# output: asm_prettify.sh

Get assmebly

# dev: new_feature.sh

Add feature dir boilerplate

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
