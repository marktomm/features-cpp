#!/bin/bash

ARG1=$1
ARG2=$2
ARG3=$3

asmfile="builddir/${ARG1}/${ARG1}_$( [[ -n "${ARG3}" ]] && echo "${ARG3}" || echo "main" )${ARG2}.s"

awk '{print NR, $0}' ${asmfile}
