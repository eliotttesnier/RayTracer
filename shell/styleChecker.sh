#!/bin/bash

# Define the log file
LOG_FILE="coding-style-cpp-reports.log"
> "$LOG_FILE"  # Clear the log file before writing

# Define the cpplint filter to only check specific errors
FILTERS="+whitespace/line_length,+whitespace/operators,+whitespace/tab,+whitespace/empty_if_body,-readability/braces,+readability/casting,+build/include_order"

NOFILTERS="-readability/namespace,-legal/copyright,-build/include_subdir,-whitespace/braces,-runtime/string,-whitespace/parens,-whitespace/indent_namespace"

LINELENGTH=95

# Run cpplint on all .cpp and .hpp files, excluding tests/ and bonus/
find . -type f \( -name "*.cpp" \) ! -path "*/tests/*" ! -path "*/bonus/*" ! -path "*/temp/*" | while read -r file; do
    cpplint --filter="$FILTERS,$NOFILTERS" --linelength=$LINELENGTH "$file" 2>> "$LOG_FILE"
done

# Inform user of completion
echo "Coding style check completed. See $LOG_FILE for details."
