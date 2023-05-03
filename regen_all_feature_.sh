#!/bin/bash

set -e

# other_script_output=$(./features_list.sh)

while IFS= read -r line; do
    ./new_feature.sh ${line} regen_meson
done <<< "$(./features_list.sh)"