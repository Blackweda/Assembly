/*
 * Lab 6 - Vectorization lab
 * This program creates two 1000-element integer arrays and fills them 
 * with random numbers, then sums those two arrays to a third array, 
 * and finally sums the third array to a long int and prints the result
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

int main()
{
    int a[SIZE];
    int b[SIZE];
    int sumArr[SIZE];
    long int totalSum;

    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand();
        b[i] = rand();
        sumArr[i] = a[i] + b[i];
        totalSum += sumArr[i];
    }

    printf("Total long int sum = %d\n", totalSum );

    return 0;
}
