#ifndef HW2_IO_H
#define HW2_IO_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "lib/static/serial_ranking.h"

#define MAX_REQUEST_SIZE 80

bool input_request(char *request);
void print_top(struct top_five *top);

#endif //HW2_IO_H
