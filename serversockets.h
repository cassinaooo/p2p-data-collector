#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "serversockets.c"

int newlistensocket(char *port);
int newrecvsocket(int sockfd);