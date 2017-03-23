/*
    returns the socket file descriptor in wich the
    server will accept connections
*/

int newlistensocket(char *port){
    int sockfd;
    int status;

    struct addrinfo hints;
    struct addrinfo *res;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty

    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // port is the second argument of getaddrinfo, NULL defaults to the host IP address
    if ((status = getaddrinfo(NULL, port, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // res now points to a linked list of 1 or more struct addrinfos

    // ... do everything until you don't need res anymore ....

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(sockfd < 0){
        fprintf(stderr, "socket error: %s\n", strerror(sockfd));
        exit(1);        
    }
    
    // bind it to the port we passed in to getaddrinfo():
    status = bind(sockfd, res->ai_addr, res->ai_addrlen);

    if(status < 0){
        fprintf(stderr, "bind error: %s\n", strerror(status));
        exit(1);
    }

    freeaddrinfo(res); // free the linked-list

    return sockfd;
}

/*
    returns the socket file descriptor connected to a
    client that can be used to recv() data
    uses the sockfd from newlistensocket()
*/

int newrecvsocket(int sockfd){
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int new_fd;

    addr_size = sizeof their_addr;

    // blocks until a connection is made
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

    if(new_fd < 0){
        fprintf(stderr, "accept error: %s\n", strerror(new_fd));
        exit(1);
    }

    return new_fd;
}