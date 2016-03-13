/**
 * intArray.c
 * cs50 week2 section
 *
 * creates an array with the integers one through five
 * and then prints out each integer on a new line.
 */

#include <stdio.h>

int main(void)
{
    int n[] = {1, 2, 3, 4, 5};

    
    for (int i = 0; i < 5; i++)
    {
        printf("n[%i] : %i\n", i, n[i]);
        printf("%i bytes\n", sizeof n[i]);
    }
    return 0;
}





