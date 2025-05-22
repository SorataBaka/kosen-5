#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#define __USE_XOPEN
#include <math.h>
#include <string.h>
#include "pcm.h"

#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fatal(s, ...)   \
  {                     \
    debug(__VA_ARGS__); \
    exit(s);            \
  }

int main(int argc, char *argv[])
{
  int fileCount = argc;
  if (fileCount < 4)
    fatal(1, "Insufficient file amount\n");
  // Count the total length and initialize a new wav variable with that length.
  unsigned int totalSamples = 0;
  unsigned int sampleRate = 44100;
  int channelCount = 2;
  int bitCount = 16;

  for (int i = 1; i < fileCount - 1; i++)
  {
    FILE *fp = fopen(argv[i], "r");
    Wav *wav = pcmRead(fp);
    if (fp == NULL || wav == NULL)
      fatal(1, "Failed to load file or wav");
    totalSamples += wav->len;
    sampleRate = wav->fmt.fs;
    channelCount = wav->fmt.ch;
    bitCount = wav->fmt.bit;
    printf("Reading file %s with duration %.02f minutes\n", argv[i], (double)wav->len / wav->fmt.fs / 60);
  }
  printf("\nCreating new wav format with: \n");
  printf("\tSample Count: %u\n", totalSamples);
  printf("\tChannel Count: %d\n", channelCount);
  printf("\tBit Count: %d\n", bitCount);
  printf("\tSample Rate: %u\n\n", sampleRate);
  printf("Output duration will be %.02f minutes\n", (double)totalSamples / sampleRate / 60);

  Wav *newWav = pcmInit(bitCount, channelCount, sampleRate, totalSamples);
  unsigned int newWavIndex = 0;
  for (int i = 1; i < fileCount - 1; i++)
  {
    printf("Writing file %s\n", argv[i]);
    FILE *fp = fopen(argv[i], "r");
    Wav *wav = pcmRead(fp);
    if (fp == NULL || wav == NULL)
      fatal(1, "Failed to load file or wav");
    for (int readFileIndex = 0; readFileIndex < wav->len; readFileIndex++)
    {
      newWav->val[0][newWavIndex] = wav->val[0][readFileIndex];
      if (channelCount >= 2 && wav->fmt.ch >= 2)
      {
        newWav->val[1][newWavIndex] = wav->val[1][readFileIndex];
      }
      newWavIndex++;
    }
  }
  printf("Writing to %s\nDONE\n", argv[argc - 1]);
  pcmSave(argv[argc - 1], newWav);
  return 0;
}
