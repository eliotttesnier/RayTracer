#!/bin/bash
echo "Building with CUDA support (Release mode)..."
cmake . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=./ -B my-build-cuda
cmake --build my-build-cuda -j
echo "Build completed. Run with: ./my-build-cuda/raytracer configs/config.cfg"
