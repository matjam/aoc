#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include "strutil.h"

#define BUF_LEN 100

int test();
int calculate(char *);
char *replace_numbers(char *);
int test_replace();

int main(int argc, char **argv)
{
    // if (argc != 2)
    // {
    //     fprintf(stderr, "please provide the input file\n");
    // }

    // if (argc == 2 && strcmp(argv[1], "test") == 0)
    // {
    //     return test();
    // }

    // if (argc == 2 && strcmp(argv[1], "test_replace") == 0)
    // {
    return test_replace();
    // }

    // return calculate(argv[1]);
}

int calculate(char *input_file)
{
    char *buf = calloc(BUF_LEN, sizeof(char));
    FILE *fp;
    int64_t running_total = 0; // probably doesn't need to be this big lol

    // just to be sure the buffer is truly clean.
    memset(buf, 0, BUF_LEN);

    fp = fopen(input_file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "error opening file: %s\n", errno);
        return EXIT_FAILURE;
    }

    // read each line in the file and make a running total.
    char *buf_p = fgets(buf, BUF_LEN - 1, fp);
    while (buf_p != NULL)
    {
        running_total += find_first(buf_p, BUF_LEN) * 10;
        running_total += find_last(buf_p, BUF_LEN);
        memset(buf, 0, BUF_LEN);
        buf_p = fgets(buf, BUF_LEN - 1, fp);
    }

    printf("total: %d", running_total);
}


typedef struct test_replace_case
{
    char *input;
    char *expected;
} test_replace_case_t;

int test_replace()
{
    test_replace_case_t cases[] = {
        {"two1nine", "219"},
        {"eightwothree", "823"},
        {"abcone2threexyz", "abc123xyz"},
        {"xtwone3four", "x2ne34"},
        {"4nineeightseven2", "49872"},
        {"zoneight234", "z1234"},
        {"7pqrstsixteen", "7pqrst6teen"},
        {NULL, NULL},
    };

    int failures = 0;

    for (int i = 0; cases[i].input != NULL; i++)
    {
        char *input = strdup(cases[i].input);
        char *result = replace_numbers(input);
        if (strcmp(result, cases[i].expected) != 0)
        {
            printf("failed %s got %s expected %s\n", cases[i].input, result, cases[i].expected);
            failures++;
        }
        free(input);
    }

    if (failures != 0)
    {
        return EXIT_FAILURE;
    }

    printf("tests passed\n");
    return EXIT_SUCCESS;
}

typedef struct test_case
{
    char *input;
    int expected_first;
    int expected_last;
} test_case_t;

int test()
{
    int failures = 0;

    test_case_t test_cases[] = {
        {"6qghmzchmtjktjkbseightczbjmsvmrk88cgctthsbz", 6, 8},
        {"12", 1, 2},
        {"aaa1aaa2aaa", 1, 2},
        {NULL, 0, 0},
    };

    for (int i = 0; test_cases[i].input != NULL; i++)
    {
        int first = find_first(test_cases[i].input);
        int last = find_last(test_cases[i].input);

        if (first != test_cases[i].expected_first || last != test_cases[i].expected_last)
        {
            printf("failed %s got %d,%d\n", test_cases[i].input, first, last);
            failures++;
        }
    }

    if (failures != 0)
    {
        return EXIT_FAILURE;
    }

    printf("tests passed\n");
    return EXIT_SUCCESS;
}