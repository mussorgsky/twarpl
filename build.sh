#!/bin/bash

echo 'Compiling...'
g++ -std=c++17 -c Sources/main.cpp

echo 'Linking...'
mkdir -p Binaries
g++ -o Binaries/twarpl main.o

echo 'Removing object files...'
rm -- *.o

echo 'Finished'
