#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "parts.h"
#include "common.h"

int part1(char *input_file)
{
    int64_t running_total = 0; // probably doesn't need to be this big lol
    char *buf = calloc(BUF_LEN, sizeof(char));
    FILE *fp;

    fp = fopen(input_file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "error opening file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // read each line in the file and make a running total.
    char *buf_p = fgets(buf, BUF_LEN - 1, fp);
    while (buf_p != NULL)
    {
        running_total += find_first(buf_p) * 10;
        running_total += find_last(buf_p);
        memset(buf_p, 0, BUF_LEN);

        buf_p = fgets(buf, BUF_LEN - 1, fp);
    }

    printf("part1 total: %lld\n", running_total);
    return EXIT_SUCCESS;
}

// find_first will find the first number in a string
char find_first(char *s)
{
    char v = 0;
    int s_len = strlen(s);

    for (int i = 0; i < s_len; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            v = s[i] - 48; // cos ascii
            break;
        }
    }

    return v;
}

// find_last does the same in reverse
char find_last(char *s)
{
    char v = 0;
    int s_len = strlen(s);

    for (int i = s_len - 1; i > -1; i--)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            v = s[i] - 48; // cos ascii
            break;
        }
    }

    return v;
}