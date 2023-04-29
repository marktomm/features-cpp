#!/bin/bash

set -e

ARG1=$1

onlySuite=$([[ -n "${ARG1}" ]] && echo 0 || echo 1)
onlySuiteFunc() {
  return $onlySuite
}

onlySuiteFunc && meson test -C builddir --benchmark --suite $1
# onlySuiteFunc && meson compile -C builddir bench_$1
onlySuiteFunc || meson test -C builddir --benchmark