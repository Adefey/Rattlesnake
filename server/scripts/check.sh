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
check_log "cppcheck --enable=all --inconclusive --error-exitcode=1 ./include/* ./sources_machine/* ./sources_server_application/* ./test/* --suppress=missingIncludeSystem" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy ./include/* ./sources_machine/* ./sources_server_application/* ./test/* -warnings-as-errors=* -extra-arg=-std=c++2a -- -Iproject/headers" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=cpp,hpp --filter=-build/header_guard ../include/* ./sources_machine/* ./sources_server_application/* ./test/*" "Can't open for reading"

print_header "SUCCESS"
