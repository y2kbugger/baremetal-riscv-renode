#ifndef BAREMETAL_H
#define BAREMETAL_H

#include "process.h"

extern struct Process *current_process;
extern struct Process *next_process;

void handel_interrupt();
void end_this_process();

#endif /* BAREMETAL_H */
