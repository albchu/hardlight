#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include <sstream>

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
	void render_scoreboard(Viewports::Viewport viewport, FTGLPixmapFont * font);
	vector<Bike*> get_scoreboard();
	vector<int> get_scoreboard_bike_id();
private:
	vector<Bike*> scoreboard;
	vector<int> scoreboard_bike_id;
	int player_number;
	int bot_number;
	BikeManager* bike_manager;
	unsigned int num_scoreboard_players;
};

#endif