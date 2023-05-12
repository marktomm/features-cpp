#!/bin/bash

set -e

./regex_plot.sh virtual_base_class/ "BM_[0A]" opt && ./regex_plot.sh virtual_base_class/ "BM_[0A]"
./regex_plot.sh trivial_type/ "BM_[0A]" opt && ./regex_plot.sh trivial_type/ "BM_[0A]" 
./regex_plot.sh try_catch_exception/ "BM_[^YX5]" opt && ./regex_plot.sh try_catch_exception/ "BM_[^YX5]"

 ./gen_bench.sh try_catch_exception/ && ./_build.sh && ./regex_plot.sh try_catch_exception/ "BM_[^IYWX5R]" opt && ./regex_plot.sh try_catch_exception/ "BM_[^IYXW5R]"