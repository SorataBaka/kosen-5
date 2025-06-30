#include "janken.h"

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

  /* iterate over all (p_rock , p_paper , p_scissors) with step = 0.10 */
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

      /* --- simulate `rounds` games for this distribution --- */
      for (long long int i = 0; i < rounds; ++i)
      {
        Round round = generateRound(dist);
        RoundResult result = checkRound(round);

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

Round generateRound(Distribution distribution)
{
  Round round = {0};
  double selfRandom = generateFloatWithinRange(0, 1);

  round.player2 = generateWithinRange(0, 2);

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