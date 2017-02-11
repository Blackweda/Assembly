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
    printf("\nNaive volume up\n===============\n");

    for (int i = 0; i <= SAMPLESNUM; i++)
    {
        //printf("%i: %d * %f = ", i, sample_[i], scale);
        newSample_[i] = sample_[i] * scale;
    }
}

// Use lookup table to adjust volume up
void lookupTableVolumeUp(int16_t* sample_, int16_t* newSample_)
{
    printf("\nLookup volume up\n================\n");

    // Create Lookup table
    int16_t lookupTable[MAXSIZE];
    for (int mult = 0, counter = 0; counter <= MAXSIZE; counter++)
    {
        lookupTable[counter] = (uint16_t)((counter - HALF )*scale);
        //printf("%i = %d\n",counter,lookupTable[counter]);
    }   

    // Increase
    for (int i = 0; i <= MAXSIZE; i++)
    {
        //printf("sample_[%i] = %d, HALF = %i\n", i, sample_[i], HALF);
        newSample_[i] = lookupTable[sample_[i]+HALF];
        //printf("%i ", i);
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
        printf("bitwise %i = %i\n", i, bitwise[MAXSIZE]);
    }
}

// Calculates and prints elapsed time of execution t2 - t1
void printExecTime(struct timeval t1, struct timeval t2)
{
    double elapsed = ((t2.tv_sec-t1.tv_sec) * 1000) // calculate function execution time 
                + ((t2.tv_usec - t1.tv_usec) / 1000);

    printf("elapsed: %dms\n", elapsed);
}

void printSpecifiedRange(int16_t* sample_, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        printf("sample[%i]=%d\n",i,sample_[i]);
    }
}

int main()
{
    struct timeval t1, t2;
    double elapsed;
    float volScaleFact;
    int16_t* sample = malloc(SAMPLESNUM*sizeof(int16_t));

    createAudioSample(sample);
    printf("\nAudio sample\n============\n");
    printSpecifiedRange(sample,0,7);

    int16_t* newSample = malloc(SAMPLESNUM*sizeof(int16_t));
    gettimeofday(&t1, NULL); // starting time
    naiveVolumeUp(sample, newSample); // start naive test
    gettimeofday(&t2, NULL); // end time
    printExecTime(t1, t2);
    printSpecifiedRange(newSample,0,7);

    gettimeofday(&t1, NULL); // starting time
    lookupTableVolumeUp(sample, newSample); // start lookup table approach 
    gettimeofday(&t2, NULL); // end time
    printExecTime(t1, t2);
    printSpecifiedRange(newSample,0,7);

    /*gettimeofday(&t1, NULL); // starting time
    bitwiseVolUp(sample); // start lookup table approach 
    gettimeofday(&t2, NULL); // end time
    printExecTime(t1, t2);*/

    return 0;
}
