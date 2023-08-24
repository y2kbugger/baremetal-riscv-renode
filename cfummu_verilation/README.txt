mkdir build
cd build
source ../../activate-toolchains.sh
cmake -DCMAKE_BUILD_TYPE=Release -DUSER_RENODE_DIR="$BAREMETAL_RISCV_RENODE" -DLIBOPENLIBM=$BAREMETAL_RISCV_RENODE/renode-verilator-integration/lib/libopenlibm-Linux-x86_64.a ".."
make libVtop