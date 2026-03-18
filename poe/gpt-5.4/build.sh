#!/usr/bin/bash

mkdir -p build
gcc gpt-5.4.c -o build/auth
./build/auth