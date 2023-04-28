#!/bin/bash

set -e

# WARN: ls -la output is not guaranteed
ls -la | grep '^d' | grep -v '\.$\|\.\.$\|\.[^ ]*$\|builddir\|benchmark' | awk '{print $9}'