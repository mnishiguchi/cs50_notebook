#include <cs50.h>
#include <stdio.h>

/**
* int PositiveInt(int num);
* a function I made to get a positive number from user.
*/

// prototype
int GetPositiveInt();

int main(void)
{
    printf("\nHello!!!\n\n");
    int num = GetPositiveInt();
    return 0;
}

int GetPositiveInt(void)
{
    do 
    {
        printf("Type a positive integer and press enter:  \n");
        num = GetInt();
    }
    while (num <= 0);
    printf("Thanks for %d\n\n", num);
    return num;
}

