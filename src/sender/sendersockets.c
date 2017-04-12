#include <protocolutils.h>
#include "sendersockets.h"


/**
 *
 * !!!! NAO IMPLEMENTADO, NAO FUNCIONANDO !!!!
 *
 * especifica a quantidade maxima de saltos que devem ser realizados entre hosts para o
 * transito de pacotes enviados utilizando o socket descrito por sock
 *
 * pretendo setar pra um, para que a existencia de um outro dispositivo na rede
 * para debugar i.e notebook do experimentador, nao interfira na transmissao dos dados
 * servindo como uma ponte entre os hosts
 *
 * @param sock, socket file descriptor
 * @param ttl, numero maximo de saltos que os pacotes podem realizar
 */

// TODO

void setttl(int sock, uint8_t ttl){
    int ret = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(uint8_t));
    if (ret != 0)
        printf("Failed to setsockopt(): %s\n", strerror(errno));
}


/**
    returns a socket ready to make send calls
    to a specific port in a host
**/

int newsendsocket(char *port, char *host){
    int status;
    int sockfd;

    struct addrinfo hints;
    struct addrinfo *res;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty

    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    // port is the second argument of getaddrinfo, NULL defaults to the host IP address
    if ((status = getaddrinfo(host, port, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // res now points to a linked list of 1 or more struct addrinfos

    // ... do everything until you don't need res anymore ....

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

//    setttl(sockfd, 1);

    if(sockfd < 0){
        // error checking
        fprintf(stderr, "getaddrinfo error: %s\n", strerror(sockfd));
        exit(1);        
    }

    // connect!

    while(connect(sockfd, res->ai_addr, res->ai_addrlen) < 0){
        debug("Cant connect just yet, waiting 5 seconds before trying again.\n");
        sleep(5);
    }

    debug("Connect succes!\n");

    freeaddrinfo(res); // free the linked-list

    return sockfd;
}



