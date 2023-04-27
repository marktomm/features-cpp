#!/bin/bash

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

ARG1=$1
ARG1=$(trimFwdSlashes ${ARG1})
ARG2=$2
ARG3=$3

asmfile="builddir/${ARG1}/${ARG1}_$( [[ -n "${ARG3}" ]] && echo "${ARG3}" || echo "main" )${ARG2}.s"

awk '{print NR, $0}' ${asmfile}
