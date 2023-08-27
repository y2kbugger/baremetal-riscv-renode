#include "./mutex.h"

void mutex_init(struct Mutex *m)
{
    atomic_flag_clear(&m->locked);
}

void mutex_lock(struct Mutex *m)
{
    while (atomic_flag_test_and_set(&m->locked))
        ; // spin-wait (do nothing)
}

void mutex_unlock(struct Mutex *m)
{
    atomic_flag_clear(&m->locked);
}