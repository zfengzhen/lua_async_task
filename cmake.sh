#!/bin/sh
mkdir -p build
cd ./build/
rm * -rf
cmake ..
make
