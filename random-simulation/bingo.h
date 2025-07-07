#ifndef BINGO_H
#define BINGO_H
#include "help.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>

#define SIDE 5
typedef int BingoCard[SIDE][SIDE];

void simulateBingo(long long int repeat, Options opts);
BingoCard *generateHand();
void simulateCalls(BingoCard *card);
int validateCard(const BingoCard *card);

#endif