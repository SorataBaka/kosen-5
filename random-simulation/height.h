#ifndef HEIGHT_H
#define HEIGHT_H
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "help.h"

#define IS_FEMALE(h)  (((int)(h) & 1) == 0)
#define IS_MALE(h)    (((int)(h) & 1) == 1)

typedef enum Human{
  W5,
  M5,
  W4,
  M4,
  W3,
  M3,
  W2,
  M2,
  W1,
  M1,
} Human;


void simulateHeight(long long int repeat, Options opts);
Human* generateRow();
int checkRow(Human * queue, int minTaller);
static inline int height_key(Human h);

#endif