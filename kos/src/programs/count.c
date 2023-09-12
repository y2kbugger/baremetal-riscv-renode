#include <stdio.h>
#include <string.h>
#include "../baremetal.h"

void count_forever()
{
    // disable_timer();
    unsigned int i = 0;
    int lineLength = 0;

    struct _reent reentStruct;
    _REENT_INIT_PTR(&reentStruct);
    while (1)
    {
        char buffer[20] = {};
        // snprintf(buffer, sizeof(buffer), "%u", i);
        _snprintf_r(&reentStruct, buffer, sizeof(buffer), "%u", i);
        int numLength = strlen(buffer);

        if (lineLength + numLength > 72)
        {
            printf("\n");
            lineLength = 0;
        }
        else
        {
            printf(" ");
            lineLength += 1;
        }

        printf("%u", i);
        lineLength += numLength;

        i++;
    }
    return;
}
