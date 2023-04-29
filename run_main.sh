#!/bin/bash

set -e

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

ARG1=$1
ARG1=$(trimFwdSlashes ${ARG1})
ARG2=$2

runFile="builddir/${ARG1}/${ARG1}_$( [[ -n "${ARG2}" && "${ARG2}" == 'opt' ]] && echo "" || echo "no_" )opt"

./_build.sh

${runFile}