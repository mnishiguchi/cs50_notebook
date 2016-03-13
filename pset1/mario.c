/**
 * cs50 pset1: mario
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * check50: passed
 *
 * display a half-pyramid according to user desired height
 */
 
#include <cs50.h>
#include <stdio.h>

int main(void)
{	
    // prompting the user for the half-pyramid’s height
    int h;
    printf("\nHello! Let's build a half-pyramid!!!\n");      

	do
	{
	    printf("Please type your desired height (an integer from 1 to 23 inclusive):  \n");
	    h = GetInt();
	}    
	while ((h < 0) || (23 < h));
	
	if (!h)
	{
	    return 0;
	}
	
    // piling up bricks line by line
	int space = h - 1;       // number of spaces on line 1
	int line, i;	
	
	for (line = 1; line <= h; line++)
	{
		for (i = space; i > 0; i--)
		{
			printf(" ");
		}
		for (i = space; i <= h; i++)
		{
			printf("#");
		}
		printf("\n");
		space--;       // updating the number of spaces for next line
	}	 
	return 0;
}
