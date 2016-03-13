/**
 * insertionsort.c
 *
 * sorts the elements of an array in ascending order
 *
 * Masatoshi Nishiguchi
 */
          
/* Take each unsorted element, n,
 * and compare it to values in the sorted subarray from right to left
 * until you determine the appropriate sorted position for n.
 * Shift sorted elements rightward as necessary to make space for n,
 * and insert the previously unsorted n into its appropriate position in the sorted subarray.
 */

#include <stdio.h>

void insertionsort(int values[], int n)
{
	int temp;
    
    // Scan unsorted elements one at at a time
	for (int i = 0; i < (n - 1); i++)
	{
		temp = array[i];    // temporary storage for the element being sorted
		
		// Shift the elements in the sorted sub-array 
		// in order to make appropriate insertion space
		int k = i;
		while (k > 0 && array[k - 1] > temp)
		{
		    k--;
		    values[k] = temp;
		}
    }
}
		
		
		


