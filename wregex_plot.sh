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

./gen_bench.sh ${ARG1} && ./_build.sh && ./regex_plot.sh ${ARG1} ${ARG2} opt && ./regex_plot.sh ${ARG1} ${ARG2}