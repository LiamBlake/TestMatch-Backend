
#include <string>
#include <stdlib.h>
#include <cmath>

#include "Simulation.h"
#include "Player.h"
#include "Cards.h"
#include "Utility.h"
#include "MatchTime.h"


/* Innings implementations */
int Innings::inns_no = 0;

// Constructor
Innings::Innings(Team c_team_bat, Team c_team_bowl, int c_lead, int c_day, float c_day) {

  team_bat = c_team_bat;
  team_bowl = c_team_bowl;

  lead = c_lead;

  wkts = 0;

  inns_no++;

}

// Private methods used in simulation process
void Innings::simulate_delivery() {

  BatterCard* batter = batters[striker];
  BowlerCard* bowler = bowlers[bowl_1];


  int runs;

  if (runs % 2 == 1 && runs != 5) {
    // Rotate strike
  }


  // Add additional time, sampled from modified normal distribution
  

  // Check time of day

  // Check for declaration
  if (check_declaration()) {
    inns_open = false;
    // Do innings close stuff
  }

}

    // Check for declaration
bool check_declaration() {
  // TODO: implement declaration checking
  return false;
  // AIS: never declare, may lead to some slightly absurd innings
}

// Choose next bowler based off of last bowler (from end)
Player* choose_bowler(BowlerCard* last_bowler) {

};

// Select a fielder for an appropriate mode of dismissial
Player* Innings::select_fielder() {
  // TODO: spice this up
  // AIS: choose a random fielder (who isn't the bowler)
  // Uniform distribution, with bias towards wicketkeeper

  const double WK_PROB = 0.4;

  double r = ((double) rand() / (RAND_MAX));

  if (r < WK_PROB) {
    // Caught by wicketkeeper
    return team_bat->players[team_bat->wicket_keeper];
  } else {
    // Randomly choose one of the 9 remaining fielders
    // Cast WK_PROB < r < 1 to integer 
    int index = (int) floor((r - WK_PROB) * 10 / (1 - WK_PROB));  

  }


}

  	
    void simulate();



// Getters
BatterCard** Innings::get_batters() {
  return batters;
}

BowlerCard** Innings::get_bowlers() {
  return bowlers;
}





/*
  Match implementations
*/
Match::Match(Team* home_team, Team* away_team, bool choose_XI) {
  team1 = home_team;
  team2 = away_team;

  // Choose batting order if requested
  if (choose_XI) {
    // Do nothing as of yet
  }

  // Time object - default constructor to day 1, start time
  time = MatchTime();


  ready = false;

}

void Match::simulate_toss() {

  // Winner of toss is chosen randomly - 0.5 probability either way
  double r = ((double) rand() / (RAND_MAX)) + 1;
  toss_win = (r < 0.5);


  // TODO: Implement toss election based on pitch conditions
  toss_elect = false;

}


void Match::pregame() {
  // Toss
  simulate_toss();


  // Prepare innings
  bool team_order = toss_win;

  if (team_order) {
    inns[0] = new Innings(team1, team2, 0, &time, &pitch);
  } else {

  }

  ready = true;
}
