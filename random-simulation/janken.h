#ifndef JANKEN_H
#define JANKEN_H
#include "help.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum HandPosition
{
  ROCK,
  PAPER,
  SCISSORS
} HandPosition;

typedef struct Round
{
  HandPosition player1;
  HandPosition player2;
} Round;

typedef struct RoundResult
{
  int winlose;
  HandPosition winningPosition;
} RoundResult;

typedef struct Distribution
{
  double rock;
  double paper;
  double scissors;
} Distribution;

void simulateJanken(long long int rounds, Options opts);
Round generateRound(Distribution distribution);
RoundResult checkRound(Round round);

#endif