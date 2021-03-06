/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * Helper functions for Problem Set 3.
 *
 */
            
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int max = n - 1;  // array index of maximum
    int min = 0;      // array index of minimum
    int mid;          // array index of midpoint
    
    while(min <= max)
    {
        // Check if the midpoint value is the one being searched for 
        mid = (min + max) / 2;
        if (values[mid] == value)
        {
            return true;
        }
        
        // If the searched-for value is smaller than current midpoint
        // update the max to just below the midpoint
        else if (values[mid] > value)
        {
            max = mid - 1;
        }
        
        // If the searched-for value is greater than current midpoint
        // update the min to just above the midpoint  
        else if (values[mid] < value)
        {
            min = mid + 1;
        }
    }
    
    return false;
}


/**
 * Sorts array of n values.
 */

// Inserion sort
void sort(int values[], int n)
{
    int temp;
        
    // Scan unsorted elements one at at a time (from values[1] upwards)
    for (int i = 1; i < n; i++)
    {
        // memorize the value of an element to be sorted
	    temp = values[i];  
		
	    // Compare the element to values in the sorted subarray to the left
	    // Shift sorted values rightward as necessary to make space for insertion
      	int pos = i;    
	    while (pos > 0 && values[pos - 1] > temp)  // Keep comparing to the left until finding a lesser value
	    {
		    values[pos] = values[pos - 1];         // Shift sorted values rightward
		    pos--;
	    }
	    		
	    values[pos] = temp;                      // Insertion
    }
}
