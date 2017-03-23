#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocoltypes.h"
#include "protocolutils.c"

Header *newheader();
void printheader(const Header * h);

Slice *newslice(Header * header, int slice_no, const char * data);
void printslice(const Slice * s);