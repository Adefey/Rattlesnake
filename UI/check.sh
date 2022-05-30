#!/usr/bin/bash

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
check_log "clang-format -i -style=file ./Headers/*.h ./Sources/*.cpp" "Can't open for reading"

print_header "RUN cppcheck"
check_log "cppcheck --enable=all --inconclusive --language=c++ --error-exitcode=1 ./Headers/*.h ./Sources/*.cpp --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=useStlAlgorithm" "\(information\)"

print_header "RUN cpplint"
check_log "cpplint --extensions=cpp,hpp,h --filter=-build/header_guard,-legal/copyright,-build/include_subdir,-build/include_order,-runtime/explicit,-whitespace/blank_line,-whitespace/comments,-whitespace/indent,-runtime/string,-runtime/references ./Headers/*.h ./Sources/*.cpp" "Can't open for reading"

print_header "SUCCESS"

