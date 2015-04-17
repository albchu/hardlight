#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	int player_number = 0;
	int bot_number = 0;
	BikeManager* bike_manager = NULL;
	unsigned int num_scoreboard_players = 0;
}

Scoreboard::Scoreboard(BikeManager* b_mngr)
{
	bike_manager = b_mngr;
	player_number = 1;
	bot_number = 1;
	// copy vector of all bikes

	for(unsigned int i = 0; i < bike_manager->get_all_bikes().size(); i++)
	{
		scoreboard.push_back(bike_manager->get_all_bikes()[i]);
		if(bike_manager->get_all_bikes()[i]->get_subtype() == PLAYER_BIKE)
		{
			scoreboard_bike_id.push_back(player_number);
			player_number++;
		}
		else
		{
			scoreboard_bike_id.push_back(bot_number);
			bot_number++;
		}
	}

	num_scoreboard_players = scoreboard.size();
	if(num_scoreboard_players > 5)
	{
		num_scoreboard_players = 5;
	}
}

void Scoreboard::update_scoreboard()
{
	// Bubblesort
	bool swapped = true;
	unsigned int j_sort = 0;
	Bike* tmp;
	int tmp_id;
	while (swapped) 
	{
		swapped = false;
		j_sort++;

		for (unsigned int i_sort = 0; i_sort < scoreboard.size() - j_sort; i_sort++) 
		{
			if (scoreboard[i_sort]->get_player_score() < scoreboard[i_sort + 1]->get_player_score()) 
			{
				tmp = scoreboard[i_sort];
				scoreboard[i_sort] = scoreboard[i_sort + 1];
				scoreboard[i_sort + 1] = tmp;
				tmp_id = scoreboard_bike_id[i_sort];
				scoreboard_bike_id[i_sort] = scoreboard_bike_id[i_sort + 1];
				scoreboard_bike_id[i_sort + 1] = tmp_id;
				swapped = true;
			}
		}
	}
}

void Scoreboard::render_scoreboard(Viewports::Viewport viewport, FTBitmapFont * font)
{
	// render the scoreboard to the viewport
	unsigned int letter_size = viewport.height/4/num_scoreboard_players;
	font->FaceSize(letter_size);
	for(unsigned int i = 0; i < num_scoreboard_players; i++)
	{
		FTPoint scoreboard_position(viewport.x+(viewport.width/2*0), (viewport.y+viewport.height) - ((i+1)*letter_size));
		stringstream player_score_string;
		if(scoreboard[i]->get_subtype() == PLAYER_BIKE)
		{
			player_score_string << "Player " << scoreboard_bike_id[i] << ": ";
		}
		else
		{
			player_score_string << "Bot " << scoreboard_bike_id[i] << ": ";
		}
		player_score_string << scoreboard[i]->get_player_score();
		font->Render(player_score_string.str().c_str(), -1, scoreboard_position);
	}


}

vector<Bike*> Scoreboard::get_scoreboard()
{
	return scoreboard;
}

vector<int> Scoreboard::get_scoreboard_bike_id()
{
	return scoreboard_bike_id;
}