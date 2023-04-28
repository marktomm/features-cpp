#!/bin/bash

set -e

./_clean.sh
./_build.sh
./_benchmark.sh $1