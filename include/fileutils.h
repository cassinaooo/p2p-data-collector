#ifndef __FILE_READER__
#define __FILE_READER__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long slurp(char const* path, char **buf, int add_nul);

#endif