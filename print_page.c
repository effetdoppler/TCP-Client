#define _GNU_SOURCE

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

const size_t BUFFER_SIZE = 32;

void rewrite(int fd, const void *buf, size_t count)
{
    // TODO
    ssize_t res = write(fd, buf, count);
    //If the return value of write() is smaller than its third argument, you must call write() a
    //gain in order to have the rest of the data written. Repeat this until all the data has been sent
    if (res != count)
    {
        char * buff  = buf;
        while(res != count)
        {
            // If an error occurs, exit the program with an error message
            if (res == -1)
                err(EXIT_FAILURE, "write function has failed");
                res = write(fd, buf, count);
            buff = buff + res;
            count = count - res;
            res = write(fd, buff, count);
        }
    }
}

char *build_query(const char *host, size_t *len)
{
    // TODO
    char* req;
    int res = asprintf(&req, "GET http://www.%s/ HTTP/1.0\r\n\r\n", host);
    //If the request cannot be generated, the program should exit immediately with an error message.
    if (res == -1)
        err(EXIT_FAILURE, "the request cannot be generated");
    //This argument must return the length of the request that will be generated
    *len = res;
    return req;
    
}

void print_page(const char *host)
{
    char buffer[BUFFER_SIZE];

    // TODO
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
    char *req = build_query(host, &len);

    
    /* Obtain address(es) matching host/port */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = NULL;
    hints.ai_protocol = NULL;          /* Any protocol */
    s = getaddrinfo(host, "80", &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
            continue;
        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) == -1)
        {
            close(sfd);
            continue;
        }
        rewrite(sfd, req, len);
        while (1)
        {
            ssize_t a = read(sfd, buffer, BUFFER_SIZE);
            if(a == -1)
                err(EXIT_FAILURE, "could not read from the socket");
            if(a == 0)
                break;
            rewrite(STDOUT_FILENO, buffer, a);
        }
        close(sfd);
        break;
    }
   
    
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
    }
    freeaddrinfo(result);           /* No longer needed */
}

