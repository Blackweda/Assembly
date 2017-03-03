/*
 * SPO600 - Lab 5
 * This program adjusts the volume of a sequence of sound samples
 * using 3 approaches (naive, lookup, bitwise)
 * */

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdlib.h>

#define MAXSIZE 65536 // maximum size for signed 16 bit integer
#define HALF 32767 // half of max size for signed 16 bit integer
#define SAMPLESNUM 500000000

const float scale = 0.5; // volume scaling factor

// Creates our randomly generated audio sample 
void createAudioSample(int16_t* sample_)
{
    for(int i = 0; i <= SAMPLESNUM; i++)
    {
        sample_[i] = rand();
        //printf("sample %i = %i\n", i, sample_[i]);
    }
}

// First "naive" approach
// Volume up using multiply by volume scale factor
void naiveVolumeUp(int16_t* sample_, int16_t* newSample_)
{
    int16_t *x = __builtin_assume_aligned(sample_,16);
    int16_t *y = __builtin_assume_aligned(newSample_,16);

    for (int i = 0; i <= SAMPLESNUM; i++)
    {
        y[i] = x[i] * scale;
    }
}

// Use lookup table to adjust volume up
void lookupTableVolumeUp(int16_t* sample_, int16_t* newSample_)
{
    // Create Lookup table
    int16_t lookupTable[MAXSIZE];
    for (int counter = 0; counter < MAXSIZE; counter++)
    {
        lookupTable[counter] = ((counter - HALF )*scale);
        //printf("%i : %d\t",counter,lookupTable[counter]);
    }   

    // Increase
    for (int i = 0; i <= MAXSIZE; i++)
    {
        newSample_[i] = lookupTable[sample_[i] + HALF];
        //printf("sample_[%i] = %d, HALF = %i\n", i, sample_[i], HALF);
    }
}

// Use bit shifting to adjust volume by volume scale factor
// starter...
void bitwiseVolUp(int16_t* sample)
{
    int16_t bitwise[MAXSIZE];
    for (int i = 0; i <= MAXSIZE; i++)
    {
        bitwise[MAXSIZE] = sample[i] << 1; // (int32_t)volume*2^16
        //printf("bitwise %i = %i\n", i, bitwise[MAXSIZE]);
    }
}

// Calculates and prints elapsed time of execution t2 - t1
void printExecTime(struct timeval t1, struct timeval t2)
{
    unsigned long elapsed = ((t2.tv_sec - t1.tv_sec) * 1000)
                          + ((t2.tv_usec - t1.tv_usec) / 1000);

    printf("elapsed: %lums\n", elapsed);
}

void printSpecifiedRange(int16_t* sample_, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        printf("sample[%i]=%d\n", i, sample_[i]);
    }
}

int main()
{
    struct timeval t1, t2;
    int16_t* sample = malloc(SAMPLESNUM*sizeof(int16_t));
    int16_t* newSample = malloc(SAMPLESNUM*sizeof(int16_t));

    createAudioSample(sample);
    printf("\nAudio sample\n============\n");
    printSpecifiedRange(sample, 0, 7);

    printf("\nNaive volume up\n===============\n");
    gettimeofday(&t1, NULL); // starting time
    naiveVolumeUp(sample, newSample); // start naive test
    gettimeofday(&t2, NULL); // end time
    printExecTime(t1, t2);
    printSpecifiedRange(newSample, 0, 7);

    free(newSample);
    newSample = malloc(SAMPLESNUM*sizeof(int16_t));
    printf("\nLookup volume up\n================\n");
    gettimeofday(&t1, NULL); // starting time
    lookupTableVolumeUp(sample, newSample); // start lookup table approach 
    gettimeofday(&t2, NULL); // end time
    printExecTime(t1, t2);
    printSpecifiedRange(newSample, 0, 7);

    /*gettimeofday(&t1, NULL); // starting time
    bitwiseVolUp(sample); // start lookup table approach 
    gettimeofday(&t2, NULL); // end time
    printExecTime(t1, t2);*/

    return 0;
}
