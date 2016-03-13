/**
 * insertionsort.c
 *
 * sorts the elements of an array in ascending order
 *
 * Masatoshi Nishiguchi
 */
          
/* Take each unsorted element,
 * and compare it to values in the sorted subarray from right to left
 * until you determine the appropriate sorted position for the element in question.
 * Shift sorted elements rightward as necessary to make space for n,
 * and insert the previously unsorted n into its appropriate position in the sorted subarray.
 */

#include <stdio.h>
   
int main(void)
{
    // sample data
    int values[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = (sizeof(values) / sizeof(int));
    printf("n = %d\n", n);
    
    // print the entire array before sorting
    for (int i = 0; i < n; i++)
    {
        printf("%3d", values[i]);
    }
    printf("\tbefore\n\n");


    // insertionsort(int values[], int n)
	int temp;
    
    // Scan unsorted elements one at at a time (from values[1] upwards)
	for (int i = 1; i < n; i++)
	{
		// memorize the value of an element to be sorted
		temp = values[i];  
		
		// compare the element to values in the sorted subarray to the left
		// Shift sorted values rightward as necessary to make space for insertion
  		int k = i;    
		while (k > 0 && values[k - 1] > temp)  // keep comparing to the left until finding a lesser value
		{
		    values[k] = values[k - 1];         // Shift sorted values rightward
		    k--;
		}
		
		values[k] = temp;                      // insertion
		
		// print the entire array after each step
        for (int i = 0; i < n; i++)
        {
            printf("%3d", values[i]);
        }
        printf("\n");
    }
}


