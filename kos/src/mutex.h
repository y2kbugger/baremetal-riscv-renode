#ifndef MUTEX_H
#define MUTEX_H

#include <stdatomic.h>

struct Mutex
{
    atomic_flag locked;
};

void mutex_init(struct Mutex *m);
void mutex_lock(struct Mutex *m);
void mutex_unlock(struct Mutex *m);

#endif /* MUTEX_H */