#!/bin/sh
rm -rf build
cmake -H. -Bbuild
cd build
make all
./updater
cd ..
