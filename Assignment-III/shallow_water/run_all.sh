#!/bin/bash
export OMP_NUM_THREADS=${OMP_NUM_THREADS:-8}
echo "OMP_NUM_THREADS=$OMP_NUM_THREADS"
for bin in sw_*; do
    ./"$bin"
done
