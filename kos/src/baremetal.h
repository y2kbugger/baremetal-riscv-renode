#ifndef BAREMETAL_H
#define BAREMETAL_H

#include "process.h"

extern struct Process *current_process;
extern struct Process *next_process;

void disable_interrupt(int irq_num);
void enable_interrupt(int irq_num);
void handel_interrupt();
void stop_this_process();
void end_this_process();
void yield_from_this_process();

#endif /* BAREMETAL_H */
