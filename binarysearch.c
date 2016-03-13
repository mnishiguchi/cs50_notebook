/**
 * binarysearch.c
 *
 * Masatoshi Nishiguchi
 *
 * Returns true if value is in array of n values, else false.
 * Requirement: the array must be sorted in ascending order in advance.
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
        // update max to just below the midpoint
        else if (value < values[mid])
        {
            max = mid - 1;
        }
        
        // if the searched-for value is greater than current midpoint
        // update min to just above the midpoint  
        else if (values[mid] < value)
        {
            min = mid + 1;
        }
    }
    
    return false;
}

