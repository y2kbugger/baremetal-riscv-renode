//
// Copyright (c) 2010-2021 Antmicro
//
//  This file is licensed under the MIT License.
//  Full license text is available in 'LICENSE' file.
//

// These are generated by verilator during compilation
#include <verilated.h>
#include "Vtop.h"

// Other includes
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#if VM_TRACE
#include <verilated_fst_c.h>
#endif
// integration headers found in Renode's VerilatorPlugin
// These would be for integrating to external interfaces e.g. tx and rx for uarts etc
// #include "src/peripherals/uart.h"
#include "src/renode_bus.h"
// #include "src/buses/bus.h"
#include "src/buses/wishbone.h"

RenodeAgent *kos;
Vtop *top = new Vtop;
VerilatedFstC *tfp;

void eval()
{
#if VM_TRACE
    main_time++;
    tfp->dump(main_time);
#endif
    top->eval();
}

RenodeAgent *Init()
{
    Wishbone *bus = new Wishbone();

    // Init bus signals
    bus->wb_clk = &top->clk;
    bus->wb_rst = &top->rst;
    bus->wb_addr = (uint64_t *)&top->adr;
    bus->wb_rd_dat = (uint64_t *)&top->dat_miso;
    bus->wb_wr_dat = (uint64_t *)&top->dat_mosi;
    bus->wb_we = &top->we;
    bus->wb_sel = &top->wb_sel;
    bus->wb_stb = &top->stb;
    bus->wb_ack = &top->ack;
    bus->wb_cyc = &top->cyc;
    bus->granularity = 1;
    bus->addr_lines = 32;

    // Init eval function
    bus->evaluateModel = &eval;

    bus->reset();

    // Init peripheral
    kos = new RenodeAgent(bus);
    return kos;
}