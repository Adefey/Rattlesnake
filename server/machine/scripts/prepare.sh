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

print_header "RUN clang-format"
check_log "clang-format -i -style=file ./project/Server/sources/*.cpp ./project/Machine/sources/*.cpp ./project/Server/test/*.cpp ./project/Machine/test/*.cpp ./project/Server/headers/*.hpp ./project/Machine/headers/*.hpp" "Can't open for reading"

