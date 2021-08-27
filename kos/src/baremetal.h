#ifndef BAREMETAL_H
#define BAREMETAL_H

#include "process.h"

extern volatile struct Process *current_process;
extern volatile struct Process *next_process;
void end_this_process();

#endif /* BAREMETAL_H */
