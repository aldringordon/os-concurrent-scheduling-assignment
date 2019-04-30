#!/bin/bash
echo Compiling sys.c
gcc -c sys.c
gcc sys.o -o sys
echo Compile Complete
