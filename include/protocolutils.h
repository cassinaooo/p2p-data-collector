#ifndef __PROTOCOL_UTILS__
#define __PROTOCOL_UTILS__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocoltypes.h"

Header *newheader();
void printheader(const Header * h);

Slice *newslice(int datasize, int sliceno, const char * slicename , const char * data);
void printslice(const Slice * s);

#endif