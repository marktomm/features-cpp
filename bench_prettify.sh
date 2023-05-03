#!/bin/bash

set -e

# ./this_script some_feature_dir_name 
# some_feature_dir_name may have '/' symbol leading or preceding

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

ARG1=$1
ARG1=$(trimFwdSlashes ${ARG1})
ARG2=$2

runFile="builddir/${ARG1}/${ARG1}_benchmark_google_$( [[ -n "${ARG2}" && "${ARG2}" == 'opt' ]] && echo "" || echo "no_" )opt"

./gen_bench.sh ${ARG1}

./_build.sh

${runFile} | sed -E 's/(^.*[^0-9])[0-9]*$/\1/' || true

