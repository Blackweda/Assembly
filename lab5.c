/*
 * SPO600 - Lab 5.1
 * This program adjusts the volume of a sequence of sound samples
 * using 3 approaches (naive, lookup, bitwise)
 * */

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdlib.h>

unsigned int const max = 500000000; // sound samples
float const scaleForNaive = 1.5; // volume scaling factor
float const scaleForLookup = 0.5;
const unsigned int size = 65536; // maximum size of signed 16 bit integer  
const unsigned int sizeHalf = 32767;
const signed int min = -32768;
const unsigned int mult3Table[11] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3 }; // look-up table

// Creates our randomly generated audio sample 
void createAudioSample(int16_t* sample_)
{
    for(int i = 0; i <= max; i++)
    {
        sample_[i] = rand();
        //printf("sample %i = %i\n", i, sample_[i]);
    }
}

// First "naive" approach
// Volume up using multiply by volume scale factor
void naiveVolumeUp(int16_t* sample_)
{
    for (int i = 0; i <= max; i++)
    {
        sample_[i] *= scaleForNaive;
        //printf("naive %i = %i\n", i, sample_[i]);
    }
}

// Use lookup table to adjust volume up
void lookupTableVolumUp(int16_t* sample_)
{
    // Create Lookup table
    int16_t lookupTable[size];
    for (int mult = 0, counter = 0; counter <= size; counter++)
    {
        lookupTable[counter] = (uint16_t)((counter - sizeHalf )*scaleForLookup);
        //printf("%i: %d\n",counter,lookupTable[counter]);
    }   

    // Increase
    for (int i=0; i <= size; i++)
    {
        sample_[i] = lookupTable[sample_[i]+sizeHalf];
    }
}

// Use bit shifting to adjust volume by volume scale factor
// starter...
void bitwiseVolUp(int16_t* sample)
{
    int16_t bitwise[size];
    for (int i = 0; i <= size; i++)
    {
        bitwise[size] = sample[i] << 1; // (int32_t)volume*2^16
        printf("bitwise %i = %i\n", i, bitwise[size]);
    }
}

// Calculates and prints elapsed time of execution t2 - t1
void printExecTime(struct timeval t1, struct timeval t2)
{
    double elapsed = ((t2.tv_sec-t1.tv_sec) * 1000) // calculate function execution time 
                + ((t2.tv_usec - t1.tv_usec) / 1000);

    printf("elapsed: %dms\n", elapsed);
}

void printSpecifiedRange(int16_t* sample, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        printf("sample[%i]=%d\n",i,sample[i]);
    }
}

int main()
{
    struct timeval t1, t2;
    double elapsed;
    float volScaleFact;
    int16_t* sample = malloc(max*sizeof(int16_t));

    createAudioSample(sample);
    //printf("sample 15: %d\n", sample[14]);
    printf("\nAudio sample\n============\n");
    printSpecifiedRange(sample,0,7);

    gettimeofday(&t1, NULL); // starting time
    naiveVolumeUp(sample); // start naive test
    printf("sample 15: %d\n", sample[14]);
    gettimeofday(&t2, NULL); // end time
    printf("\nNaive volume up\n===============\n");
    printExecTime(t1, t2);
    printSpecifiedRange(sample,0,7);

    gettimeofday(&t1, NULL); // starting time
    lookupTableVolumUp(sample); // start lookup table approach 
    printf("sample 15: %d\n", sample[14]);
    gettimeofday(&t2, NULL); // end time
    printf("\nLookup volume up\n================\n");
    printExecTime(t1, t2);
    printSpecifiedRange(sample,0,7);

    /*gettimeofday(&t1, NULL); // starting time
    bitwiseVolUp(sample); // start lookup table approach 
    gettimeofday(&t2, NULL); // end time
    printExecTime(t1, t2);*/

    return 0;
}
