#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}


print_header "RUN cppcheck"
check_log "cppcheck --enable=all --inconclusive --error-exitcode=1 ./project/Server/sources/*.cpp ./project/Machine/sources/*.cpp ./project/Server/test/*.cpp ./project/Machine/test/*.cpp ./project/Server/headers/*.hpp ./project/Machine/headers/*.hpp --suppress=missingIncludeSystem" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy ./project/Server/sources/*.cpp ./project/Machine/sources/*.cpp ./project/Server/test/*.cpp ./project/Machine/test/*.cpp ./project/Server/headers/*.hpp ./project/Machine/headers/*.hpp -warnings-as-errors=* -extra-arg=-std=c11 -- -Iproject/headers" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=c,h,cpp,hpp --filter=-build/header_guard ./project/Server/sources/*.cpp ./project/Machine/sources/*.cpp ./project/Server/test/*.cpp ./project/Machine/test/*.cpp ./project/Server/headers/*.hpp ./project/Machine/headers/*.hpp" "Can't open for reading"

print_header "SUCCESS"
