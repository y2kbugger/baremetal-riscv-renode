#include <stdint.h>

typedef struct
{
    uint32_t Load;
    uint32_t Value;
    uint32_t Control;
    uint32_t Flag;
} Timer;

enum ControlRegister
{
    Enable = (1 << 0),
    InterruptEnable = (1 << 1),
    ChainMode = (1 << 2),
};

volatile Timer *const timer = (Timer *)(0x60002800 + 0x100);
// PeriodicInteruptTimer has initial no-op  region followed by 8 timers of size 0x10
// We are only using one here.
//
// See: renode/src/Infrastructure/src/Emulator/Peripherals/Peripherals/Timers/PeriodicInterruptTimer.cs
//
//    if (offset < 0x100) { return; }
//    var timer_no = (int) ((offset - 0x100) / 0x10);
//    var noffset = (long) (offset - 0x100 - 0x10*timer_no);

void init_timer()
{
    timer->Load = 450;
    timer->Flag = 0;
    timer->Control = Enable | InterruptEnable | ChainMode;
}

void clear_timer()
{
    timer->Flag = 0;
}

void disable_timer()
{
    timer->Control = 0;
}