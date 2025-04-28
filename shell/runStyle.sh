#!/bin/bash
cpplint --config .cppRules $(find . -type f \( -name "*.cpp" -or -name "*.h" \) ! -path "./cmake-build*" ! -path "./my-build-debug*")
