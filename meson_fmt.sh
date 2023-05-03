#!/bin/bash

set -e

function is-app-installed(){
    hash $1 2>&-
    return $?
}

is-app-installed muon || {
    echo "You don't have muon installed. Visit https://muon.build/"
    exit 1
}

find -name 'meson.build' -exec muon fmt -i {} \;
