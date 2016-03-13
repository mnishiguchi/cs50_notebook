/**
 * bubblesort-1.c
 *
 * Masatoshi Nishiguchi
 * 
 * sorts the elements of an array in ascending order.
 * This is more efficient than bubblesort-0.c because 
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
    printf("\tbefore\n");


    // bubblesort-1
    int swap_count;
    int temp = 0;
    
    for (int i = 0; i < n ; i++)
    {
        // exclude already-sorted elements, left side of values[i] each step
        // scan from right to left
        swap_count = 0;
        for (int k = (n - 1); k > i; k--)
        {
            if (values[k - 1] > values[k])
            {
                temp = values[k];
                values[k] = values[k - 1];
                values[k - 1] = temp;
                
                swap_count++;
            }
            
            // print the entire array after each step
            for (int i = 0; i < n; i++)
            {
                printf("%3d", values[i]);
            }
            printf("\n"); 
        }
        
        // "No swap" means that the array is already sorted
        if (swap_count == 0)
            break;
    }
}
