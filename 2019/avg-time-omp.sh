#!/usr/bin/env bash
set -euo pipefail


for i in $( seq 1 $1 ); do
    #only works when each execution is <1s
    { time ./$2; } |& grep real >>.omp_temp_test_times;
done;
awk -F"[ms]" '{ sum+=$2 } END { print sum/NR }' <.omp_temp_test_times;
rm .omp_temp_test_times ;
