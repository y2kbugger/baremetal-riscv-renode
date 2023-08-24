#
# REPLACE ALL UNCOMMENTED <...> PLACEHOLDERS
#
cmake_minimum_required(VERSION 3.8)

# Name of the project
project("cfu_mmu")

# Verilog files to be verilated
set(VTOP "cfummu.v")

# C/C++ source files to be compiled
set(CSOURCES "sim_main.cpp")

# Additional compiling, linking or verilating arguments (respectively)
#set(COMP_ARGS <ARGS>)
#set(LINK_ARGS <ARGS>)
#set(VERI_ARGS <ARGS>)

# CMake file doing the hard job
include(../renode-verilator-integration/cmake/configure-and-verilate.cmake)
