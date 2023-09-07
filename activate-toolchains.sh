#!/bin/bash

if [ "$0" = "$BASH_SOURCE" ]; then
    echo "Error: Source this script, don't run it"
    exit 1
fi

# only source once
if [ -n "$BAREMETAL_RISCV_RENODE" ]; then echo "Already ran"; return; fi
export BAREMETAL_RISCV_RENODE=$(realpath $(dirname "$BASH_SOURCE"))

PATH="$BAREMETAL_RISCV_RENODE/renode:$BAREMETAL_RISCV_RENODE/riscv-gnu-toolchain-output/bin:$PATH"

PS1="<BAREMETAL> $PS1"
