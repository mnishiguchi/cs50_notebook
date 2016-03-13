/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in (0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 *
 * commented by Masatoshi Nishiguchi
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // Check the number of command-line arguments the user inputs.
    // If it's invalid, display the usage.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // Convert the user-input numerical character into an integer.
    // (number of pseudorandom numbers)
    int n = atoi(argv[1]);

    // If the user provides a seed value, convert it into an integer and use it as a seed.
    // Otherwise, use the current time as a seed.
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // Print as many pseudorandom numbers as specified by the user.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    return 0;
}
