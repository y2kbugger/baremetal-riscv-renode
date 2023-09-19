#include <stdint.h>
#include <stdbool.h>

void init_uart();

bool uart_has_data();

int _write(int fd, char *buf, int count); // for use in last ditch crash reporting
