#ifndef __SENDER_SOCKETS__
#define __SENDER_SOCKETS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int newsendsocket(char *port, char *host);

#endif