#!/bin/bash
randomcpu=$(( RANDOM % $(nproc) ))

echo "generating C source"
python3 gen.py && \
gcc -O0 bench.c -o bench.o && \
echo "running program" && \
OUT=$(perf stat -e cycles,instructions taskset -c ${randomcpu} ./bench.o 2>&1)
cycles=$(echo "$OUT" | grep 'cycles' | awk '{print $1}' | sed 's/,//g')
instructions=$(echo "$OUT" | grep 'instructions' | awk '{print $1}' | sed 's/,//g')
cpi=$(awk -v cycles="$cycles" -v instructions="$instructions" 'BEGIN { printf "%.4f", cycles / instructions }')
echo "CPU Cycles: $cycles"
echo "Instructions: $instructions"
echo "Cycles per Instruction (CPI): $cpi"
