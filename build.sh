#!/bin/bash
set -e

echo 'Compiling...'
g++ -std=c++17 -c Sources/main.cpp
g++ -std=c++17 -c Sources/DXFParser.cpp
g++ -std=c++17 -c Sources/DXFEntity.cpp
g++ -std=c++17 -O3 -c Sources/PlotterKinematics.cpp

echo 'Linking...'
mkdir -p Binaries
g++ main.o DXFParser.o DXFEntity.o PlotterKinematics.o -o Binaries/twarpl

echo 'Removing object files...'
rm -- *.o

echo 'Finished'
