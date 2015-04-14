#include "Hardlight.h"


bool HardLight::menu_init()
{

	Menu* mainMenu = menuManager->createMenu("Main Menu");
	Menu* newGame = menuManager->createMenu("New Game");
	Menu* settings = menuManager->createMenu("Settings");
	Menu* developer = menuManager->createMenu("Developer Options");
	Menu* powerups = menuManager->createMenu("Powerups");
	Menu* loadingScreen = menuManager->createMenu("Now Loading");

	vector<const char*> numPlayersBox;
	numPlayersBox.push_back("1");
	numPlayersBox.push_back("2");
	numPlayersBox.push_back("3");
	numPlayersBox.push_back("4");


	vector<const char*> zeroToTen;
	zeroToTen.push_back("0");
	zeroToTen.push_back("1");
	zeroToTen.push_back("2");
	zeroToTen.push_back("3");
	zeroToTen.push_back("4");
	zeroToTen.push_back("5");
	zeroToTen.push_back("6");
	zeroToTen.push_back("7");
	zeroToTen.push_back("8");
	zeroToTen.push_back("9");
	zeroToTen.push_back("10 (High end rig recommended)");

	//New game menu setup
	menuManager->setupRangeOption(newGame, "Number of Bots", zeroToTen, numBots);
	menuManager->setupRangeOption(newGame, "Number of Players", numPlayersBox, numPlayers);
	menuManager->setupOption(newGame, "powerups", "Configure Powerups", powerups);
	menuManager->setupOption(newGame, "launch", "Launch Game", game_launched);
	menuManager->setupOption(newGame, "devoptions", "Developer Options", developer);

	// Powerup menu
	menuManager->setupRangeOption(powerups, "Number of instant effect powerups on field", zeroToTen, numInstantPowerups);
	menuManager->setupRangeOption(powerups, "Number of manual trigger powerups on field", zeroToTen, numHoldPowerups);

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

	// Create the loading option
	bool bogus = false;	// this is never used. I just dont care anymore to make something new
	loadingMessage = menuManager->setupOption(loadingScreen, "loadingmessage", "Warming up!", bogus);

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
		menuManager->set_current_menu("Now Loading");
		menuManager->render();
		SDL_RenderPresent( gRenderer );

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

void HardLight::loading_update(const char * message)
{
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );
	loadingMessage->set_text(message);
	menuManager->render();
	SDL_RenderPresent( gRenderer );
}

