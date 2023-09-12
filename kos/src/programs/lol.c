#include <stdio.h>

#include "../baremetal.h"

void lol()
{
    printf("hahahahahahaha\n");
    end_this_process();
}

void laugh_forever()
{
    while (1)
    {
        for (int i = 0; i < 36; i++)
            printf("ha");
        printf("\n");
    }
}
