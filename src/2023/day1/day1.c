#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

#include "common.h"
#include "parts.h"

int test()
{
    part1_test();
    part2_test();
}

int main(int argc, char **argv)
{
    // because when you run under the debugger, you get a bunch of parameters we need
    // to loop until we find a parameter we know, or just run the main.

    for (int c = 0; c < argc; c++)
    {
        if (strcmp(argv[1], "test") == 0)
        {
            return test();
        }
    }

    part1("day1/input.txt");
    part2("day1/input.txt");

    return EXIT_SUCCESS;
}
