#ifndef JANKEN_H
#define JANKEN_H
#include "help.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef enum HandPosition
{
  ROCK,
  PAPER,
  SCISSORS,
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

#define FEATURE_COUNT 6
#define CLASS_COUNT 3
void simulateJanken(long long int rounds, Options opts);

Round generateRound(Distribution distribution, const int opponent_count[3], int total_opponent_moves, HandPosition lastMove);
RoundResult checkRound(Round round);

void buildFeatureVector(double features[FEATURE_COUNT], HandPosition ownLastMove, const int opponent_count[3], int total_opponone_moves);

void predict(const double features[FEATURE_COUNT], double output_probs[CLASS_COUNT]);
void softmax(const double logits[CLASS_COUNT], double output_probs[CLASS_COUNT]);
HandPosition predictBestMove(const double probs[CLASS_COUNT]);

void trainWeights(const double features[FEATURE_COUNT], HandPosition actualOpponentMove, double learning_rate);

HandPosition getBestMoveAgainst(HandPosition opponentMove);

#endif