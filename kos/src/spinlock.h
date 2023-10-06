#ifndef SPINLOCK_H
#define SPINLOCK_H

struct spinlock
{
    volatile int locked;
};

void lock(struct spinlock *lock);
void unlock(struct spinlock *lock);

#endif /* SPINLOCK_H */