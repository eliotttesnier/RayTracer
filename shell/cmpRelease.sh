#!/bin/bash
cmake . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=./ -B  my-build-release
cmake --build my-build-release -j
