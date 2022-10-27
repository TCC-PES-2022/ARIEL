#!/usr/bin/env bash

mkdir -p build
cd build

cmake ..

make -j$(nproc)

# Return to root directory
cd ..
