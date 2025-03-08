#!/usr/bin/env bash

input="$(pwd)/.vscode/input.txt";

# echo "Running $1";

g++-14 -std=c++17 $1 -o main.bin;
./main.bin <$input;
rm main.bin;