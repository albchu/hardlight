#include "Hardlight.h"


bool HardLight::menu_init()
{

	Menu* mainMenu = menuManager->createMenu("Main Menu");
	Menu* newGame = menuManager->createMenu("New Game");
	Menu* settings = menuManager->createMenu("Settings");
	//Menu* exitGame = menuManager->createMenu("Exit Game");
	Menu* developer = menuManager->createMenu("Developer Options");

	//New game menu setup
	//menuManager->setupOption(newGame, "Select Number of Players", mainMenu);	// UPDATE PLZ
	//menuManager->setupOption(newGame, "Select Number of Bots", mainMenu);	// UPDATE PLZ
	menuManager->setupOption(newGame, "devoptions", "Developer Options", developer);
	menuManager->setupOption(newGame, "launch", "Launch Game", game_launched);

	// Dev options setup
	bool godmode = false;
	MenuOption* godModeOption = menuManager->setupOption(developer, "devoptions", "Godmode Off", godmode);

	//Main menu setup
	vector<const char*> pickbox;
	pickbox.push_back("Choice 1");
	pickbox.push_back("Choice 2");
	pickbox.push_back("Choice 3");
	selectedIndex = 0;

	menuManager->setupRangeOption(mainMenu, "Some Pickbox", pickbox, selectedIndex);
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
