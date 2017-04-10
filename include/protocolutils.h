#ifndef __PROTOCOL_UTILS__
#define __PROTOCOL_UTILS__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "protocoltypes.h"
#include "fileutils.h"

Header *newheader(const char * clientname, const char * filename,
                  const __off_t filesize, const long int checksum);

void printheader(const Header * h);

unsigned int cksum(const char *filename);

void debug(const char *fmt, ...);

void error(char *fmt, ...);

Header *decodeHeader(const char *str);

void encodeHeader(Header *h, char *buf);

#endif