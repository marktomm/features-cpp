#!/bin/bash

ARG1=$1

asmfile=builddir/${ARG1}/${ARG1}_main.s

awk '{print NR, $0}' ${asmfile}
