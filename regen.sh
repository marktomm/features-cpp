#!/bin/bash

set -e

./regen_all_features.sh 
rm -r builddir/
meson setup builddir
./_build.sh 