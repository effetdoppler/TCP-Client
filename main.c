#include <stdio.h>
#include <unistd.h>
#include "print_page.h"

int main(int argc, char **argv)
{
    
    if (argc > 1)
        print_page(argv[1]);
    return 0;
}