#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "parts.h"

typedef struct part1_test_case
{
    char *input;
    int expected_first;
    int expected_last;
} part1_test_case_t;

int part1_test()
{
    int failures = 0;

    part1_test_case_t test_cases[] = {
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

    printf("part1 tests passed\n");
    return EXIT_SUCCESS;
}
