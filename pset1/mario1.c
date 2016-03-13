/**
 * cs50 pset1: mario
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * display a half-pyramid according to user desired height
 */
 
#include <cs50.h>
#include <stdio.h>

int main(void)
{	
// prompting the user for the half-pyramid’s height
    printf("\nHello, cs50! Let's build a half-pyramid!!!\n");
    printf("Please type your desired height, then press enter (an integer from 1 to 23 inclusive):  \n");
	int hgt = GetInt();

// checking user-input and prompting if necessary		
	while ((hgt <= 0) || (23 < hgt))
	{
		printf("\nInvalid height: %d \n", hgt);
		printf("Please re-enter your desired height, then press enter (an integer from 1 to 23 inclusive):  \n");
		hgt = GetInt();
	}
    printf("\nHeight: %d\n", hgt);
		
// piling up bricks line by line
	int sp = hgt - 1;       // number of spaces on line 1
	int ln, i;	
	
	for (ln = 1; ln <= hgt; ln++)
	{
		for (i = sp; i > 0; i--)
		{
			printf(" ");
		}
		for (i = sp; i <= hgt; i++)
		{
			printf("#");
		}
		printf("\n");
		sp--;       // updating the number of spaces for next line
	}	 
	return 0;
}
