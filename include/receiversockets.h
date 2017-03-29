#ifndef __RECEIVER_SOCKETS__
#define __RECEIVER_SOCKETS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int newlistensocket(char *port);
int newrecvsocket(int sockfd);

#endif