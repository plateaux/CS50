/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: Implement binary searching algorithm
    int low = 0, high = n;
    bool searchingHaystack = true;
    int j = 0;
    
    while (searchingHaystack)
    {
        int guess = (low+high) / 2;

        if(values[guess] == value)
        {
            searchingHaystack = false;
            return true;
        }
        
        if(values[guess] > value)
        {
            high = guess;
        }
        
        if (values[guess] < value)
        {
            low = guess;
        }
        
        j += 1;
        
        if (j>n)
        {
            searchingHaystack = false;
        }
    }
    
    return false;
}
        
    
/* Old Search Code
    for (int i = 0; i < n; i++)
    {
        if (values[i]==value)
        {
        return true;
        }
    }
    return false;
}

*/

/*
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //O(n^2) sorting algorithm
    for(int j = 0; j < n; j++)
    {
    
        for(int i = 0; i < n-1; i++)
        {
            if(values[i] > values[i+1])
            {
                int temp = 0;
                temp = values[i+1];
                values[i+1] = values[i];
                values[i] = temp;
            }
        }
    }
    
}
