#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "parts.h"

typedef struct part2_test_case
{
    char *input;
    char *expected;
} part2_test_case_t;

int part2_test()
{
    part2_test_case_t cases[] = {
        {"two1nine", "2wo19ine"},
        {"eightwothree", "8igh2wo3hree"},
        {"abcone2threexyz", "abc1ne23hreexyz"},
        {"xtwone3four", "x2w1ne34our"},
        {"4nineeightseven2", "49ine8ight7even2"},
        {"zoneight234", "z1n8ight234"},
        {"7pqrstsixteen", "7pqrst6ixteen"},
        {"eighthree", "8igh3hree"},
        {"sevenine", "7eve9ine"},
        {NULL, NULL},
    };

    int failures = 0;

    for (int i = 0; cases[i].input != NULL; i++)
    {
        char *input = strdup(cases[i].input);
        replace_numbers(input);

        if (strcmp(input, cases[i].expected) != 0)
        {
            printf("failed %s got %s expected %s\n", cases[i].input, input, cases[i].expected);
            failures++;
        }
        free(input);
    }

    if (failures != 0)
    {
        return EXIT_FAILURE;
    }

    printf("part2 tests passed\n");
    return EXIT_SUCCESS;
}
