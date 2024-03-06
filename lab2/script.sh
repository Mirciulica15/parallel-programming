#!/bin/bash

# Debugging purposes
set -euxo pipefail

start=`date +%s`

lowerEnd=$1
upperEnd=$2

DIFF=`expr $upperEnd - $lowerEnd + 1`

echo $DIFF

INCREMENT_JOBS=`expr $DIFF / 4`

echo $INCREMENT_JOBS
FIRST_HOP=`expr $lowerEnd + $INCREMENT_JOBS`
SECOND_HOP=`expr $FIRST_HOP + $INCREMENT_JOBS`
THIRD_HOP=`expr $SECOND_HOP + $INCREMENT_JOBS`

./perfect-number-search.o $lowerEnd $INCREMENT_JOBS &
./perfect-number-search.o `expr $FIRST_HOP` `expr $SECOND_HOP - 1` &
./perfect-number-search.o `expr $SECOND_HOP` `expr $THIRD_HOP - 1` &
./perfect-number-search.o `expr $THIRD_HOP` $upperEnd &

# ./perfect-number-search.o $lowerEnd $upperEnd &

wait

end=`date +%s`
runtime=$((end-start))

echo RUNTIME: $runtime

# Example usage ./script.sh 1 2000000