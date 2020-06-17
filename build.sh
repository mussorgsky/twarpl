#!/bin/bash

echo 'Compiling...'
g++ -std=c++17 -c Sources/main.cpp
g++ -std=c++17 -c Sources/DXFParser.cpp

echo 'Linking...'
mkdir -p Binaries
g++ -o Binaries/twarpl main.o DXFParser.o

echo 'Removing object files...'
rm -- *.o

echo 'Finished'
