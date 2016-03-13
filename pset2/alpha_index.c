/**
 * alpha_index.c
 * print out alphabetical index
 */

#include <stdio.h>

int main(void)
{
    char upper[26];
    for(int i = 0; i < 26; i++)
    {
        upper[i] = 'A' + i;
        printf("%c  index: %2d  ascii: %3d\n", upper[i], i, upper[i]);
    }
    printf("\n");
    
    char lower[26];
    for(int i = 0; i < 26; i++)
    {
        lower[i] = 'a' + i;
        printf("%c  index: %2d  ascii: %3d\n", lower[i], i, lower[i]);
    }
}
