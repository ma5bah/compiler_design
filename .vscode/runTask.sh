#!/usr/bin/env bash

input="$(pwd)/.vscode/input.txt";
output="$(pwd)/.vscode/output.txt";
if [[ $1==".cpp" ]]
then
    if echo "$(uname -s)" | grep "Darwin"; then    
        g++-14 -std=c++17 $1 -o main.bin;
    else
        g++ -std=c++17 $1 -o main.bin;
    fi
    ./main.bin <$input > $output;
    rm main.bin
else
    echo "Wrong file selected." > $output
    echo "Script exiting.";
    exit -1;
fi
