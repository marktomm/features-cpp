#!/bin/bash

set -e

# other_script_output=$(./feature_list.sh)

while IFS= read -r line; do
    ./new_feature.sh ${line} regen_meson
done <<< "$(./feature_list.sh)"