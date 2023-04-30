#!/bin/bash

set -e

test -z $1 && {
    echo "first arg must be subdir"
    exit 1
}

test -d $1 || {
    echo "subdir $1 missing"
    exit 1
}

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

APP_ROOT=.
SUB=$1
SUB=$(trimFwdSlashes ${SUB})
OUTPUT=${SUB}/amalgamation.cpp
REGEX='"dev.*\.h\|common/.*\.h\|include.*types.h"'
firstFile=true

fn() {
    if [[ firstFile == true ]]; then 
        firstFile=false
        echo "// ${1}" > ${OUTPUT}
    else
        echo "// ${1}" >> ${OUTPUT}
    fi
    test -f "${1}" && grep -v ${REGEX} $_ >> ${OUTPUT}
    echo "// ${1} end" >> ${OUTPUT}
}

fn ${SUB}/include/lib.h
fn ${SUB}/src/lib.cpp
fn ${SUB}/src/main.cpp
