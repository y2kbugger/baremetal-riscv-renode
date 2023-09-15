#include <stdio.h>
#include <string.h>
#include "../baremetal.h"

void count_forever()
{
    unsigned int i = 0;
    int lineLength = 0;

    while (1)
    {
        char buffer[20] = {};
        snprintf(buffer, sizeof(buffer), "%u", i);
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

        printf("%s", buffer);
        lineLength += numLength;

        i++;
    }
    return;
}
