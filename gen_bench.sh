#!/bin/bash

set -e

trimFwdSlashes() {
  a1="${1#/}"       # Remove leading /
  a1="${a1%/}"     # Remove preceding /
  echo "${a1}"
}

ARG1=$1
ARG1=$(trimFwdSlashes ${ARG1})
(
    cd ${ARG1}
    cppFile=src/lib.cpp
    toFile=include/lib.h
    protoCpp=$(mktemp)
    # void fn(\n // will fail
    grep -E '^[[:blank:]]*(inline[[:blank:]]+)?(virtual[[:blank:]]+)?(explicit[[:blank:]]+)?(static[[:blank:]]+)?(const[[:blank:]]+)?(constexpr[[:blank:]]+)?[a-zA-Z_][a-zA-Z0-9_]*[[:blank:]]+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^{}]*\)\s*(const)?[[:blank:]]*\{|^std::vector<[a-zA-Z0-9_]*> .*\(.*{|^std::size_t .*\(.*{|^std::function<.*> .*\(.*{' "${cppFile}" | grep -v '^static'| sed -E 's/(.*\)) *\{.*/\1;/' | sort -k 2,1 > ${protoCpp}

    tempFile=$(mktemp)

    inputData=$(cat ${protoCpp})

    awk -v data="${inputData}" '
    BEGIN { insert_data=0 }
    /\/\/ GEN_PROTO_BEGIN/ { print; printf("%s\n", data); insert_data=1; next }
    /\/\/ GEN_PROTO_END/ { insert_data=0 }
    !insert_data { print }
    ' "${toFile}" > "${tempFile}"
    
    mv "${tempFile}" "${toFile}"
)

(
    cd ${ARG1}
    cppFile=bench.cpp
    protoCpp=$(mktemp)
    # void fn(\n // will fail
    grep -E '^[[:blank:]]*(inline[[:blank:]]+)?(virtual[[:blank:]]+)?(explicit[[:blank:]]+)?(static[[:blank:]]+)?(const[[:blank:]]+)?(constexpr[[:blank:]]+)?[a-zA-Z_][a-zA-Z0-9_]*[[:blank:]]+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^{}]*\)\s*(const)?[[:blank:]]*\{' "${cppFile}" | sed -E 's/(.*\)) *\{.*/\1;/' | grep -F 'BM_' | sort -k 2,1 > ${protoCpp}

    tempFile=$(mktemp)

    inputData=$(cat ${protoCpp})

    awk -v data="${inputData}" '
    BEGIN { insert_data=0 }
    /\/\/ GEN_PROTO_BEGIN/ { print; printf("%s\n", data); insert_data=1; next }
    /\/\/ GEN_PROTO_END/ { insert_data=0 }
    !insert_data { print }
    ' "${cppFile}" > "${tempFile}"

    mv "${tempFile}" "${cppFile}"
)

(
    cd ${ARG1}
    cppFile=bench.cpp
    protoCpp=$(mktemp)
    # void fn(\n // will fail
    grep -E '^[[:blank:]]*(inline[[:blank:]]+)?(virtual[[:blank:]]+)?(explicit[[:blank:]]+)?(static[[:blank:]]+)?(const[[:blank:]]+)?(constexpr[[:blank:]]+)?[a-zA-Z_][a-zA-Z0-9_]*[[:blank:]]+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^{}]*\)\s*(const)?[[:blank:]]*\{' "${cppFile}" | sed -E 's/(.*\)) *\{.*/\1;/' | grep -F 'BM_' | sed -E 's/.*(BM_[^(]*).*/BENCHMARK(\1);/' | sort -k1.14 > ${protoCpp}
    sed -Ei 's/(^.*[a-z0-9_]Manual.*\));/\1->UseManualTime();/' ${protoCpp}

    tempFile=$(mktemp)

    inputData=$(cat ${protoCpp})

    awk -v data="${inputData}" '
    BEGIN { insert_data=0 }
    /\/\/ GEN_BENCHMARK_BEGIN/ { print; printf("%s\n", data); insert_data=1; next }
    /\/\/ GEN_BENCHMARK_END/ { insert_data=0 }
    !insert_data { print }
    ' "${cppFile}" > "${tempFile}"

    mv "${tempFile}" "${cppFile}"
)