#include <stdio.h>

/**Difference between suffix ++ and prefix ++*/

int main(void)
{
  //suffix ++
    int x = 5;
    printf("x = 5, x++ = %d\n", x++); //Print 5 then increment by one.
    
  //prefix ++
    int y = 5;
    printf("y = 5, ++y = %d\n", ++y); //Increment by one then print it.
    
    return 0;
}
