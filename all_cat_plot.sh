#!/bin/bash

set -e

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

ARG1=${1}
ARG1=$(trimFwdSlashes ${ARG1})
EARG1=$(printf '%q' "$ARG1")
ARG2=${2}


while IFS= read -r line; do
    echo "Init ${line}/${line}_${ARG2}_${EARG1}.png"
    ./builddir/${line}/${line}_benchmark_google_$( [[ -n "${ARG2}" && "${ARG2}" == 'opt' ]] && echo "" || echo "no_" )opt --benchmark_filter="${ARG1}" --benchmark_format=csv 2>&1  | ./plot.sh ${line} ${ARG2} && mv ${line}/bench.png ${line}/${line}_${ARG2}_${EARG1}.png || echo "${line}/${line}_${ARG2}_${EARG1}.png skip"
done <<< "$(./feature_list.sh)"
line=benchmarks
./builddir/${line}/${line}_benchmark_google_$( [[ -n "${ARG2}" && "${ARG2}" == 'opt' ]] && echo "" || echo "no_" )opt --benchmark_filter="${ARG1}" --benchmark_format=csv 2>&1  | ./plot.sh ${line} ${ARG2} && mv ${line}/bench.png ${line}/${line}_${ARG2}_${EARG1}.png || echo "${line}/${line}_${ARG2}_${EARG1}.png skip"

