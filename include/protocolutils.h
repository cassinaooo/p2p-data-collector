#ifndef __PROTOCOL_UTILS__
#define __PROTOCOL_UTILS__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocoltypes.h"

Header *newheader();
void printheader(const Header * h);

Slice *newslice(Header * header, int slice_no, const char * data);
void printslice(const Slice * s);

#endif