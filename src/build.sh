#!/bin/bash
rm -r build
mkdir build
cd build
cmake ../src
make
bash