#!/bin/bash

# Debugging purposes
set -euxo pipefail

dd if=/dev/urandom of=sample.txt bs=64M count=4 iflag=fullblock

start=`date +%s`

./entropy-of-random-file.o &

wait

end=`date +%s`
runtime=$((end-start))

echo RUNTIME: $runtime

# Example usage ./entropy-of-big-file.sh