#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include <FTGL/ftgl.h>

#include "Vehicle\Bike.h"
#include "Vehicle\BikeManager.h"

using namespace glm;
using namespace std;

class Scoreboard
{
public:
	Scoreboard();
	Scoreboard(BikeManager* b_mngr);
	void update_scoreboard();
	void render_scoreboard();
	vector<Bike*> get_scoreboard();
	vector<int> get_scoreboard_bike_id();
private:
	vector<Bike*> scoreboard;
	vector<int> scoreboard_bike_id;
	int player_number;
	int bot_number;
	BikeManager* bike_manager;
};

#endif