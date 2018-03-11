#ifndef __GENERAL_H
#define __GENERAL_H

#define _GNU_SOURCE
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

#include "platform.h"

#ifndef DEBUG
#include <stdio.h>
#define DEBUG	printf
#endif

#define ALIGN(x, n) (((x) + (n) - 1) & ~((n) - 1))
#undef MIN
#define MIN(x, y)  (((x) < (y)) ? (x) : (y))

#endif
