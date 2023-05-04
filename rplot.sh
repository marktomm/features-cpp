#!/bin/bash

set -e 

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

ARG1=${1}
ARG1=$(trimFwdSlashes ${ARG1})
ARG2=${2}

isBenchmarks=$([[ -n "${ARG1}" && "${ARG1}" == 'benchmarks' ]] && echo 0 || echo 1)
isBenchmarksFunc() {
    return ${isBenchmarks}
}

isBenchmarksFunc || ./gen_bench.sh ${ARG1}
./_build.sh

./builddir/${ARG1}/${ARG1}_benchmark_google_$( [[ -n "${ARG2}" && "${ARG2}" == 'opt' ]] && echo "" || echo "no_" )opt --benchmark_filter='BM_[01]' --benchmark_format=csv 2>&1  | ./plot.sh ${ARG1} ${ARG2} && mv ${ARG1}/bench.png ${ARG1}/${ARG1}_opt_01.png || true
./builddir/${ARG1}/${ARG1}_benchmark_google_$( [[ -n "${ARG2}" && "${ARG2}" == 'opt' ]] && echo "" || echo "no_" )opt --benchmark_filter='BM_[AB]' --benchmark_format=csv 2>&1  | ./plot.sh ${ARG1} ${ARG2} && mv ${ARG1}/bench.png ${ARG1}/${ARG1}_opt_ab.png || true
./builddir/${ARG1}/${ARG1}_benchmark_google_$( [[ -n "${ARG2}" && "${ARG2}" == 'opt' ]] && echo "" || echo "no_" )opt --benchmark_filter='BM_[Y]' --benchmark_format=csv 2>&1  | ./plot.sh ${ARG1} ${ARG2} && mv ${ARG1}/bench.png ${ARG1}/${ARG1}_opt_y.png || true
