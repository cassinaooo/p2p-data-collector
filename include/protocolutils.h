#ifndef __PROTOCOL_UTILS__
#define __PROTOCOL_UTILS__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocoltypes.h"

Header *newheader(const char * clientname, const char * filename, const int filesize, const unsigned int checksum);
void printheader(const Header * h);

#endif