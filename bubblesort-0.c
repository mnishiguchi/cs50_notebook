/**
 * bubblesort-0.c
 *
 * Masatoshi Nishiguchi
 * 
 * sorts the elements of an array in ascending order.
 * This is not an efficient version of bubblesort
 * because it scans already-sorted elements every loop.
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
    printf("\n");
    
    
    // bubblesort-0
    int swap_count;
    int temp;
        
    do
    {
        swap_count = 0;
        for (int i = 0; i < (n - 1); i++)
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
