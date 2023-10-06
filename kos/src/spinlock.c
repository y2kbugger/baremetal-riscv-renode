#include "spinlock.h"

void lock(struct spinlock *lock)
{
    while (__atomic_test_and_set(&lock->locked, __ATOMIC_ACQUIRE))
        ;
}

void unlock(struct spinlock *lock)
{
    __atomic_clear(&lock->locked, __ATOMIC_RELEASE);
}