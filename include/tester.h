#ifndef __TESTE__
#define __TESTE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "fileutils.h"
#include "protocolutils.h"

Header *testheadercreation();
void testslicecreation(Header *h);
void protocolutilstest();
void filereadertest();
void splitfile();
void test();

#endif