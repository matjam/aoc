#include "parts.h"
#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

// Loops through the input and replaces any string literal numbers with
// a single character number, so "five" becomes "5" in a string.
// For example, "abcfiveabc" would become "abc5abc".
//
// input is modified in place.
int part2(char *input_file)
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
        replace_numbers(buf_p);
        running_total += find_first(buf_p) * 10;
        running_total += find_last(buf_p);
        memset(buf_p, 0, BUF_LEN);

        buf_p = fgets(buf, BUF_LEN - 1, fp);
    }

    printf("total: %lld\n", running_total);
    return EXIT_SUCCESS;
}

void replace_numbers(char *input)
{
    char *numbers[] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };

    // general strategy is this;
    //
    // 1. allocate a new string buffer
    // 2. iterate through every index of the input string looking for a match of numbers.
    // 3. if we find one, we write that number to the buffer.
    // 4. if we don't find a match, we write the current character to the buffer.
    // 5. overwrite the input with the temp buffer and free it.
    //
    // We will see if this approach gets us there.

    char *tmp_buf = calloc(BUF_LEN, sizeof(char));

    int input_len = strlen(input);
    int tmp_i = 0;

    for (int i = 0; i < input_len; i++)
    {
        bool found = false;
        for (int num_i = 0; num_i < 10; num_i++)
        {
            if (strncmp(numbers[num_i], input + i, strlen(numbers[num_i])) == 0)
            {
                // write the number
                tmp_buf[tmp_i] = (char)num_i + 48;
                tmp_i++;
                found = true;
                break;
            }
        }

        // found nothing
        if (!found)
        {
            // copy a single character
            tmp_buf[tmp_i] = input[i];
            tmp_i++;
        }

        if (tmp_i > BUF_LEN - 1)
        {
            fprintf(stderr, "overflowed tmp_buf in replace_numbers");
            return;
        }
    }

    strcpy(input, tmp_buf);
    free(tmp_buf);
}