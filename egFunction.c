#include <cs50.h>
#include <stdio.h>

/**
 *Examples of how functions work
 */

//Function
int square(int x)
{
    return x * x;
}

int main(void)
{
//Example 1
    int six_squared = square(6);
    printf("6 squared is %d\n", six_squared);
    
//Example 2    
    int a = 7;
    int a_squared = square(a);
    printf("%d squared is %d\n", a, a_squared);
    
 //Example 3   
    printf("10 squared is ");
    printf("%d\n", square(10)); //Nesting a function in another function
 
 //Keybord input
    int b;
    printf("Give me an integer you want to square:  \n");
    scanf("%d",&b);
    printf("%d squared is %d\n", b, square(b));
    
    return 0;
}
