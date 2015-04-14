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
	numPlayersMenu = numPlayers + 1;
	menuManager->setupRangeOption(newGame, "Number of Players", numPlayersBox, numPlayersMenu);
	menuManager->setupOption(newGame, "powerups", "Configure Powerups", powerups);
	menuManager->setupOption(newGame, "launch", "Launch Game", game_launched);
	menuManager->setupOption(newGame, "devoptions", "Developer Options", developer);

	// Powerup menu
	menuManager->setupRangeOption(powerups, "Number of instant effect powerups on field", zeroToTen, numInstantPowerups);
	menuManager->setupRangeOption(powerups, "Number of manual trigger powerups on field", zeroToTen, numHoldPowerups);

	// Dev options setup
	bool godmode = false;
	MenuOption* godModeOption = menuManager->setupOption(developer, "devoptions", "Godmode Off", godmode);

	// Main menu setup
	menuManager->setupOption(mainMenu, "newgame", "New Game", newGame);
	menuManager->setupOption(mainMenu, "settings", "Settings", settings);
	menuManager->setupOption(mainMenu, "exitgame", "Exit Game", running);

	menuManager->set_current_menu("Main Menu");	// Set the initial landing menu

	// Create the loading option
	bool bogus = false;	// this is never used. I just dont care anymore to make something new
	loadingMessage = menuManager->setupOption(loadingScreen, "loadingmessage", "Warming up!", bogus);

	// Create the pause menu
	pauseMenu = menuManager->createMenu("Pause Menu");
	restart_trigger = false;
	continue_trigger = false;
	halt_trigger = false;
	menuManager->setupOption(pauseMenu, "restart", "Restart Game", restart_trigger);
	menuManager->setupOption(pauseMenu, "continue", "Continue Game", continue_trigger);
	menuManager->setupOption(pauseMenu, "mainMenu", "Exit to Main Menu", halt_trigger);
	menuManager->setupOption(pauseMenu, "exitgame", "Exit Game", running);

	// Create settings menu
	vector<const char*> resolutions;
	resolutions.push_back("1280 x 800");
	resolutions.push_back("600 x 400");
	resolutionIndex = 0;
	settings_update = false;
	menuManager->setupRangeOption(settings,"Resolution", resolutions, resolutionIndex);
	fullscreenOption = menuManager->setupOption(settings,"fullscreen", "Toggle Fullscreen", isFullscreen);
	menuManager->setupOption(settings, "apply", "Apply Changes", settings_update);

	return true;
}

void HardLight::menu_update()
{
	if(game_launched && !scene_built)
	{
		menuManager->set_current_menu("Now Loading");
		menuManager->render();
		SDL_RenderPresent( gRenderer );

		numPlayers = numPlayersMenu + 1;

		reset();
		scene = GAME;	// Instantly load into game
		menu_active = false;	// Turn off menu

	}

	if(isFullscreen)
	{
		fullscreenOption->set_text("Fullscreen: On");

	}
	else if (!isFullscreen)
	{
		fullscreenOption->set_text("Fullscreen: Off");
	}

	if(settings_update)
	{
		switch(resolutionIndex)
		{
		case(0):
			window_width = 1280;
			window_height = 800;
			break;
		case(1):
			window_width = 600;
			window_height = 400;
			break;
		default:
			window_width = 600;
			window_height = 400;
			break;
		}

		if(isFullscreen)
		{
			// Hack: Fullscreen bugs out when trying to switch back to sdl renderer so we're going to fake it with borderless high resolution instead
			window_width = 1920;
			window_height = 1200;
			SDL_SetWindowBordered(window, SDL_FALSE);
		}
		else
		{
			SDL_SetWindowBordered(window, SDL_TRUE);
		}

		SDL_SetWindowSize(window, window_width, window_height);

		menuManager->set_width(window_width);
		menuManager->set_height(window_height);

		settings_update = false;
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

	if(halt_trigger)
	{
		menuManager->set_current_menu("Main Menu");	// Set the initial landing menu as the current menu
		game_launched = false;
		halt_trigger = false;
		scene_built = false;
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

