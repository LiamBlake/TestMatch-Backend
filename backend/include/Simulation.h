#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <utility>

#include "Player.h"
#include "Cards.h" 
#include "MatchTime.h"



class PitchCondition {
  private:
    // some numbers internally describing the pitch
    

    MatchTime* time;


  public:
    // Default constructor - random pitch
    PitchCondition(MatchTime* c_time);

    PitchCondition(float somenumbers, MatchTime* c_time);

    bool toss_choice();

    // Getters for values needed for delivery simulation model
};



// Match details required in delivery model
struct MatchStats {

};


// An innings
class Innings {
  private:

    // Each team
    Team* team_bat;
  	Team* team_bowl;

    // General innings info
  	static int inns_no;

  	int overs;
    int balls;
  	int team_score;
  	int lead;
  	int wkts;

    bool open;

    MatchTime* time;
    PitchCondition* pitch;

    // Ball-by-ball detail
    Over** bbb_overs; 

    // Scorecards
  	BatterCard* batters [11];
  	BowlerCard* bowlers [11];

    // Status of batters in team
    // 0 - has not batted; 1 - at crease, not out; 2 - out
    int batter_status [11];

    // Status of bowlers in team
    // false - has not bowled; true - has bowled
    bool bowler_status [11];

    // Current batters
  	BatterCard* striker;
  	BatterCard* nonstriker;

    // Bowler of current over (bowl1) and previous over (bowl2)
    BatterCard* bowl1;
    BatterCard* bowl2; 

    Extras extras;
    FOW* fow;

    // Simulation models
    const static NUM_OUTCOMES = 17;
    static std::string unencode_outcome(int outcome);
    static double* MODEL_DELIVERY(BatStats bat, BowlStats bowl, MatchStats match);

  	// Private methods used in simulation process
    
    void simulate_delivery();
    void end_over();
  	bool check_declaration();

    /* Choose the next batter in after the fall of a wicket
    
       Returns a pointer to the BatterCard corresponding
    */
    BatterCard* next_batter();

    // Choose next bowler based off of last bowler (from end)
    BowlerCard* choose_bowler();

    // Select a fielder for an appropriate mode of dismissial
  	Player* select_catcher(bool run_out = false);


  public:
  	// Constructor
  	Innings(Team* c_team_bat, Team* c_team_bowl, int c_lead, MatchTime* c_time, PitchCondition* c_pitch);
  	
    void simulate();

    // Getters
    BatterCard** get_batters();
    BowlerCard** get_bowlers();

    bool is_open();

    // Destructor
    ~Innings();

};


class Match {

  private:
    Team* team1;    // Home team
    Team* team2;    // Away team

    int country;
    std::string venue;

    bool ready;
    bool toss_win;      // false = team1, true = team2
    bool toss_elect;    // false = bat, true = bowl

    // Pitch conditions
    PitchCondition pitch;

    MatchTime time;

    int innings;
    Innings** inns[4];

    // Private helper functions
    void simulate_toss();
    void innings_change(bool follow_on);

  public:
    Match(Team* home_team, Team* away_team, bool choose_XI = false);

    void pregame();
    void start();

    std::string print_pregame();
};

#endif