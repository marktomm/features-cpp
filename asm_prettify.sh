#!/bin/bash

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
ARG3=$3

asmfile="builddir/${ARG1}/${ARG1}_$( [[ -n "${ARG2}" ]] && echo "${ARG2}" || echo "main" )_$( [[ -n "${ARG3}" && "${ARG3}" == 'opt' ]] && echo "" || echo "no_" )opt.s"

awk '{print NR, $0}' ${asmfile} | grep -vE '^[0-9]+\s+\.[^L].*[^:]$|^[0-9]+\s+#'