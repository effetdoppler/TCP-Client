#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include "print_page.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: %s host...\n", argv[0]);
    print_page(argv[1]);
    return 0;
}