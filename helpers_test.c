/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 *
 * Masatoshi Nishiguchi
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
        // check if the midpoint value is the one being searched for 
        mid = (min + max) / 2;
        if (values[mid] == value)
        {
            return true;
        }
        
        // if the searched-for value is smaller than current midpoint
        // update the max to just below the midpoint
        else if (values[mid] > value)
        {
            max = mid - 1;
        }
        
        // if the searched-for value is greater than current midpoint
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

// bubble sort
void sort(int values[], int n)
{
    int swap_count;
    int temp;
    do
    {
        swap_count = 0;
        for (int i = 0; i < n ; i++)
        {
            if (values[i] > values[i + 1])
            {
                temp = values[i];
                values[i] = values[i + 1];
                values[i + 1] = temp;
                
                swap_count++;
                // print the entire array after each step
                for (int i = 0; i < n; i++)
                {
                    printf("%3d", values[i]);
                }
                printf("\n");
            }
        }
    }
    while(swap_count > 0); 
} 
