#!/bin/sh

cd build
cmake ..
cd ..
cmake --build build/ -j4