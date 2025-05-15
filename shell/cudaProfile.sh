#!/bin/bash
# Script to profile CUDA kernel execution using nvprof

if [ ! -f "./my-build-cuda/raytracer" ]; then
    echo "Error: CUDA build not found. Run buildWithCUDA.sh first."
    exit 1
fi

echo "Running CUDA profiling..."
nvprof --profile-from-start off ./my-build-cuda/raytracer configs/config.cfg

# For more detailed profiling, uncomment:
# nvprof --analysis-metrics -o profile.nvprof ./my-build-cuda/raytracer configs/config.cfg
# echo "Detailed profiling data written to profile.nvprof"
