#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "sendsocket.c"

int newsendsocket(char *port, char *host);