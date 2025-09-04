#!/bin/bash

echo "Building the MapReduce system..."
mkdir -p build
cd build
cmake ..
make

if [ $? -eq 0 ]; then
    echo "Build successful! Testing different MapReduce operations..."
    echo

    echo "=== 1. Department Maximum Test ==="
    echo "Input file: ../samples/department_max_1.txt ../samples/department_max_2.txt ../samples/department_max_3.txt"
    ./MapReduce departmax ../samples/department_max_1.txt ../samples/department_max_2.txt ../samples/department_max_3.txt

    echo "=== 2. Word Count Test ==="
    echo "Input file: ../samples/word_count_1.txt ../samples/word_count_2.txt ../samples/word_count_3.txt"
    ./MapReduce wordcount ../samples/word_count_1.txt ../samples/word_count_2.txt ../samples/word_count_3.txt
else
    echo "Build failed!"
    exit 1
fi
