#!/bin/bash
cmake . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=./ -B my-build-debug
cmake --build my-build-debug -j
