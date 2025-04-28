#!/bin/bash
cmake . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=./ -B  my-build-tests
cmake --build my-build-tests -j
cp ./my-build-tests/tests/unit_tests ./
./unit_tests