#ifndef __PROTOCOL_UTILS__
#define __PROTOCOL_UTILS__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocoltypes.h"

Header *newheader(const char * clientname, const char * filename, const int numberofslices,const int slicemaxlen);

void printheader(const Header * h);

void newslice(Slice *new, const int slicenumber, const int totalslices, const char * slicename , const char * data, int datasize);
void printslice(const Slice * s);

#endif