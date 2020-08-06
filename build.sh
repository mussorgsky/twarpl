#!/bin/bash

echo 'Compiling...'
g++ -std=c++17 -c Sources/main.cpp
g++ -std=c++17 -c Sources/DXFParser.cpp
g++ -std=c++17 -c Sources/DXFEntity.cpp

echo 'Linking...'
mkdir -p Binaries
g++ -o Binaries/twarpl main.o DXFParser.o DXFEntity.o

echo 'Removing object files...'
rm -- *.o

echo 'Finished'
