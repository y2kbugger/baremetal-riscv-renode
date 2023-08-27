#include "./mutex.h"
#include "./uart.h"
#include "./timer.h"

void mutex_init(struct Mutex *m)
{
    atomic_flag_clear(&m->locked);
}

void mutex_lock(struct Mutex *m)
{
    disable_timer();
    // puts("Locking mutex\n");
    while (atomic_flag_test_and_set(&m->locked))
        ; // spin-wait (do nothing)
    // puts("done Locking mutex\n");
}

void mutex_unlock(struct Mutex *m)
{
    // puts("Unlocking mutex\n");
    atomic_flag_clear(&m->locked);
    // puts("done Unlocking mutex\n");
    init_timer();
}