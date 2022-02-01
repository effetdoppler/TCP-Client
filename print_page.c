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
}

char *build_query(const char *host, size_t *len)
{
    // TODO
}

void print_page(const char *host)
{
    char buffer[BUFFER_SIZE];

    // TODO
}