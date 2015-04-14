#include "Hardlight.h"


bool HardLight::menu_init()
{

	Menu* mainMenu = menuManager->createMenu("Main Menu");
	Menu* newGame = menuManager->createMenu("New Game");
	Menu* settings = menuManager->createMenu("Settings");
	Menu* developer = menuManager->createMenu("Developer Options");

	//New game menu setup
	vector<const char*> numPlayersBox;
	numPlayersBox.push_back("1");
	numPlayersBox.push_back("2");
	numPlayersBox.push_back("3");
	numPlayersBox.push_back("4");

	vector<const char*> numBotsBox;
	numBotsBox.push_back("0");
	numBotsBox.push_back("1");
	numBotsBox.push_back("2");
	numBotsBox.push_back("3");
	numBotsBox.push_back("4");
	numBotsBox.push_back("5");
	numBotsBox.push_back("6");
	numBotsBox.push_back("7");
	numBotsBox.push_back("8");
	numBotsBox.push_back("9");
	numBotsBox.push_back("10 (High end rig recommended)");

	menuManager->setupRangeOption(newGame, "Number of Bots", numBotsBox, numBots);
	menuManager->setupRangeOption(newGame, "Number of Players", numPlayersBox, numPlayers);
	menuManager->setupOption(newGame, "launch", "Launch Game", game_launched);
	menuManager->setupOption(newGame, "devoptions", "Developer Options", developer);

	// Dev options setup
	bool godmode = false;
	MenuOption* godModeOption = menuManager->setupOption(developer, "devoptions", "Godmode Off", godmode);

	//Main menu setup
	menuManager->setupOption(mainMenu, "newgame", "New Game", newGame);
	menuManager->setupOption(mainMenu, "settings", "Settings", settings);
	menuManager->setupOption(mainMenu, "exitgame", "Exit Game", running);

	menuManager->set_current_menu("Main Menu");	// Set the initial landing menu

	//Create the pause menu
	pauseMenu = menuManager->createMenu("Pause Menu");

	restart_trigger = false;
	continue_trigger = false;
	menuManager->setupOption(pauseMenu, "restart", "Restart Game", restart_trigger);
	menuManager->setupOption(pauseMenu, "continue", "Continue Game", continue_trigger);
	menuManager->setupOption(pauseMenu, "exitgame", "Exit Game", running);

	return true;
}

void HardLight::menu_update()
{
	if(game_launched && !scene_built)
	{
		BuildScene();
		scene = GAME;	// Instantly load into game
		menu_active = false;	// Turn off menu
	}

	if(restart_trigger)
	{
		reset();
		menu_active = false;	// Turn off menu
		restart_trigger = false;
	}

	if(continue_trigger)
	{
		scene = GAME;	// Instantly load into game
		menu_active = false;	// Turn off menu
		continue_trigger = false;	// Turn off command until its triggered again through the menu
	}
}
