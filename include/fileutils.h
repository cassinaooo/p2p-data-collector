#ifndef __FILE_READER__
#define __FILE_READER__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

long slurp(char const* path, char **buf, int add_nul);
void split(char const* filename, char const* slice_bytes);
void strfromlong(long ulong_value, char * str);

#endif