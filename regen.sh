#!/bin/bash

set -e

./regen_all_feature.sh 
rm -r builddir/
meson setup builddir
./_build.sh 