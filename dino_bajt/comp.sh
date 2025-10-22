#!/bin/bash

g++ -o brut brut.cpp
g++ -o sol sol.cpp
g++ -o gen gen.cpp

for ((i = 1; i <= 100000; i++)); do
    echo "Test $i"
    ./gen > test.in # Pass the test number `i` as the seed
    ./brut < test.in > brut.out
    ./sol < test.in > sol.out

    if diff -q brut.out sol.out > /dev/null; then
        echo "OK"
    else
        echo "Mismatch found!"
        echo "Input:"
        cat test.in
        echo "Brute Output:"
        cat brut.out
        echo "Optimized Output:"
        cat sol.out
        exit 1
    fi
done

echo "All tests passed!"