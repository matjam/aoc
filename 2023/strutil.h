#ifndef __UTIL_H_
#define __UTIL_H_

#include <string.h>

char find_first(char *);
char find_last(char *);
bool replace_numbers(char *input);

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

// Loops through the input and replaces any string literal numbers with
// a single character number, so "five" becomes "5" in a string.
// For example, "abcfiveabc" would become "abc5abc".
//
// input is modified in place.
bool replace_numbers(char *input)
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

    int i = 0;

    // iterate through each character, looking for the above 10 numbers.
    while (input[i] != NULL)
    {
        for (int x = 0; x < 10; x++)
        { // we can assume base 10 right? ...
            size_t num_len = strlen(numbers[x]);
            if (strncmp(input + i, numbers[x], num_len) == 0)
            {
                // found a number string at index i, and it is x. We need
                // to write that number into the input at the current location
                // and then shift all the rest of the characters left removing
                // the remainder of the number.
                input[i] = char(x + 48);

                // get a pointer to the string after the number.
                char *rest_of_string = input + num_len;

                // copy the substring over the string, including the terminator.
                // egads, strcpy. But I control all the strings, so its fine right.
                strcpy(input + i + 1, rest_of_string);

                // break out of the inner loop so we can keep processing the string
                break;
            }
        }

        i++;
    }

    return input;
}

#endif