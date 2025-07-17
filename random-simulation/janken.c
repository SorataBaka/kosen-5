#include "janken.h"
double WEIGHTS[FEATURE_COUNT][CLASS_COUNT] = {{0.0}};
double REWARD_MATRIX[3][3] = {
    //           ROCK     PAPER     SCISSORS
    /* ROCK */ {0.0, -30.0, +10.0},
    /* PAPER */ {+30.0, 0.0, -20.0},
    /* SCISSORS*/ {-10.0, +20.0, 0.0}};

void simulateJanken(long long int rounds, Options opts)
{
  const double step = opts.step; /* granularity of the grid   */
  long long int distIndex = 0;   /* which distribution row    */

  if (opts.has_outfile)
  {
    fprintf(opts.outfile,
            "rock_prob,scissors_prob,paper_prob,"
            "distribution_index,total_wins,total_earnings,average_earnings\n");
  }

  for (double p_rock = 0.0; p_rock <= 1.0 + 1e-9; p_rock += step)
  {
    for (double p_paper = 0.0; p_paper <= 1.0 - p_rock + 1e-9; p_paper += step)
    {

      double p_scissors = 1.0 - p_rock - p_paper;
      if (p_scissors < -1e-9) /* numerical guard            */
        continue;

      Distribution dist = {p_rock, p_paper, p_scissors};

      long long int wins = 0;
      long long int balance = 0;

      int opponent_count[3] = {0, 0, 0}; // Count of opponent moves

      /* --- simulate `rounds` games for this distribution --- */
      HandPosition lastMove = ROCK; // Assume starting move is ROCK
      for (long long int i = 0; i < rounds; ++i)
      {

        Round round = generateRound(dist, opponent_count, i + 1, lastMove);
        RoundResult result = checkRound(round);
        LOG("Round %lld: Player1: %d, Player2: %d, Result: %d\n",
            i + 1, round.player1, round.player2, result.winlose);
        opponent_count[round.player1]++;
        lastMove = round.player1;

        if (result.winningPosition == ROCK)
          balance += 10 * result.winlose;
        else if (result.winningPosition == PAPER)
          balance += 30 * result.winlose;
        else if (result.winningPosition == SCISSORS)
          balance += 20 * result.winlose;

        if (result.winlose == 1)
          ++wins;
      }

      double avg = (double)balance / rounds;
      ++distIndex;

      LOG("%.2f,%.2f,%.2f,%lld,%lld,%lld,%.4f\n",
          dist.rock, dist.scissors, dist.paper,
          distIndex, wins, balance, avg);

      if (opts.has_outfile)
      {
        fprintf(opts.outfile, "%.2f,%.2f,%.2f,%lld,%lld,%lld,%.4f\n",
                dist.rock, dist.scissors, dist.paper,
                distIndex, wins, balance, avg);
      }
    }
  }
}

Round generateRound(Distribution distribution, const int opponent_count[3], int total_opponent_moves, HandPosition lastMove)
{
  Round round = {0};

  double features[FEATURE_COUNT] = {0.0};
  buildFeatureVector(features, lastMove, opponent_count, total_opponent_moves);

  double output_probs[CLASS_COUNT] = {0.0};
  predict(features, output_probs);

  HandPosition predictedMove = predictBestMove(output_probs);
  round.player2 = predictedMove;

  double selfRandom = generateFloatWithinRange(0, 1);

  double rockBoundary = distribution.rock;
  double paperBoundary = distribution.rock + distribution.paper;

  if (selfRandom < rockBoundary)
  {
    round.player1 = ROCK;
  }
  else if (selfRandom < paperBoundary)
  {
    round.player1 = PAPER;
  }
  else
  {
    round.player1 = SCISSORS;
  }

  trainWeights(features, round.player1, 0.01); // Learning rate can be adjusted

  return round;
}
RoundResult checkRound(Round round)
{

  RoundResult result = {0};
  HandPosition p1 = round.player1;
  HandPosition p2 = round.player2;

  if (p1 == p2)
  {
    // Tie
    result.winlose = 0;
    // winningPosition can be left invalid or set to a sentinel
  }
  else if ((p1 == ROCK && p2 == SCISSORS) ||
           (p1 == SCISSORS && p2 == PAPER) ||
           (p1 == PAPER && p2 == ROCK))
  {
    // Player 1 wins
    result.winlose = 1;
    result.winningPosition = p1;
  }
  else
  {
    // Player 1 loses
    result.winlose = -1;
    result.winningPosition = p2;
  }
  return result;
}

HandPosition getBestMoveAgainst(HandPosition opponentMove)
{
  switch (opponentMove)
  {
  case ROCK:
    return PAPER; // Paper beats Rock
  case PAPER:
    return SCISSORS; // Scissors beat Paper
  case SCISSORS:
    return ROCK; // Rock beats Scissors
  default:
    return ROCK; // Default to Rock if invalid input
  }
}

void buildFeatureVector(double features[FEATURE_COUNT], HandPosition ownLastMove, const int opponent_count[3], int total_opponent_moves)
{
  // Reset the feature vector
  for (int i = 0; i < FEATURE_COUNT; ++i)
    features[i] = 0.0;

  // Set the own last move feature
  features[ownLastMove] = 1.0;

  // Set the opponent's move distribution features
  features[1] = (double)opponent_count[ROCK] / total_opponent_moves;
  features[2] = (double)opponent_count[PAPER] / total_opponent_moves;
  features[3] = (double)opponent_count[SCISSORS] / total_opponent_moves;
}

void predict(const double features[FEATURE_COUNT], double output_probs[CLASS_COUNT])
{
  double logits[CLASS_COUNT] = {0.0};

  // Calculate logits using the weights and features
  for (int i = 0; i < FEATURE_COUNT; i++)
  {
    for (int j = 0; j < CLASS_COUNT; j++)
    {
      logits[j] += WEIGHTS[i][j] * features[i];
    }
  }

  // Apply softmax to convert logits to probabilities
  softmax(logits, output_probs);
}
void softmax(const double logits[CLASS_COUNT], double output_probs[CLASS_COUNT])
{
  double max_logit = logits[0];
  for (int i = 1; i < CLASS_COUNT; i++)
  {
    if (logits[i] > max_logit)
    {
      max_logit = logits[i];
    }
  }

  double sum = 0.0;
  for (int i = 0; i < CLASS_COUNT; i++)
  {
    output_probs[i] = exp(logits[i] - max_logit);
    sum += output_probs[i];
  }
  for (int i = 0; i < CLASS_COUNT; i++)
  {
    output_probs[i] /= sum; // Normalize to get probabilities
  }
}
HandPosition predictBestMove(const double probs[CLASS_COUNT])
{
  double max_prob = probs[0];
  HandPosition best_move = ROCK;

  for (int i = 1; i < CLASS_COUNT; i++)
  {
    if (probs[i] > max_prob)
    {
      max_prob = probs[i];
      best_move = (HandPosition)i;
    }
  }

  return best_move;
}
void trainWeights(const double features[FEATURE_COUNT], HandPosition actualOpponentMove, double learning_rate)
{
  double probs[CLASS_COUNT];
  predict(features, probs); // Predict probabilities of ROCK, PAPER, SCISSORS

  // For each possible move, calculate expected reward gradient
  for (int move = 0; move < CLASS_COUNT; move++)
  {
    double reward = REWARD_MATRIX[move][actualOpponentMove];

    for (int f = 0; f < FEATURE_COUNT; f++)
    {
      // Gradient ascent: reward-weighted logit gradient
      WEIGHTS[f][move] += learning_rate * reward * (1.0 - probs[move]) * features[f];
    }
  }
}