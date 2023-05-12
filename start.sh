#!/bin/bash

set -e

./_clean.sh
./_build.sh
./benchmark.sh $1