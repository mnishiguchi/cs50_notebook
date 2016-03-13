/**
 * spell.c
 * cs50 week2 section
 *
 * asks the user for a string
 * then prints out each character on a new line.
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    //asks the user for a string
    printf("Please type a word, then press enter: \n");
    string s = GetString();
    
    //prints out each character on a new line.
    int sl = strlen(s);
    for (int i = 0; i < sl; i++)
    {
        printf("s[%2i]: %c\n", i, s[i]);
    }
    printf("length: %i\n\n", sl);
    return 0;
}

