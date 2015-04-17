#include "Hardlight.h"


bool HardLight::menu_init()
{
	Menu* mainMenu = menuManager->createMenu("Main Menu");
	Menu* newGame = menuManager->createMenu("New Game");
	Menu* settings = menuManager->createMenu("Settings");
	Menu* powerups = menuManager->createMenu("Powerups");
	Menu* loadingScreen = menuManager->createMenu("Now Loading...");
	loadingScreen->set_background("../data/images/Menu/Controls.bmp");
	Menu* credits = menuManager->createMenu("Credits");
	Menu* objectives = menuManager->createMenu("Objectives");
	Menu* controls = menuManager->createMenu("Controls");
	controls->set_background("../data/images/Menu/Controls.bmp");
	objectives->set_background("../data/images/Menu/Objectives.bmp");
	credits->set_background("../data/images/Menu/Credits.bmp");

	// Create the loading option
	bool bogus = false;	// this is never used. I just dont care anymore to make something new
	loadingMessage = menuManager->setupOption(loadingScreen, "loadingmessage", "Warming up!", bogus);
	loadingMessage->set_selectable(false);

	//Setup Credits 
	Menu* albert = menuManager->createMenu("albert");
	Menu* kevin = menuManager->createMenu("kevin");
	Menu* sean = menuManager->createMenu("sean");
	Menu* rob = menuManager->createMenu("rob");
	Menu* henry = menuManager->createMenu("henry");

	vector<const char*> numPlayersBox;
	numPlayersBox.push_back("1");
	numPlayersBox.push_back("2");
	numPlayersBox.push_back("3");
	numPlayersBox.push_back("4");


	vector<const char*> zeroToSix;
	zeroToSix.push_back("0");
	zeroToSix.push_back("1");
	zeroToSix.push_back("2");
	zeroToSix.push_back("3");
	zeroToSix.push_back("4");
	zeroToSix.push_back("5");
	zeroToSix.push_back("6");

	//New game menu setup
	menuManager->setupRangeOption(newGame, "Number of Bots", zeroToSix, numBots);
	numPlayersMenu = numPlayers - 1;
	menuManager->setupRangeOption(newGame, "Number of Players", numPlayersBox, numPlayersMenu);
	classicOption = menuManager->setupOption(newGame, "classic", "Classic Camera", classic);
	menuManager->setupOption(newGame, "powerups", "Configure Powerups", powerups);
	menuManager->setupOption(newGame, "launch", "Launch Game", game_launched);
	newGame->set_selected(4);	// Set the default choice to be launch game

	// Powerup menu
	menuManager->setupRangeOption(powerups, "Number of instant effect powerups on field", zeroToSix, numInstantPowerups);
	menuManager->setupRangeOption(powerups, "Number of manual trigger powerups on field", zeroToSix, numHoldPowerups);

	// Create settings menu
	vector<const char*> resolutions;
	resolutions.push_back("1280 x 800");
	resolutions.push_back("1024 x 768");
	resolutions.push_back("800 x 600");
	resolutionIndex = 0;
	settings_update = false;
	menuManager->setupRangeOption(settings,"Resolution", resolutions, resolutionIndex);
	fullscreenOption = menuManager->setupOption(settings,"fullscreen", "Toggle Fullscreen", isFullscreen);
	menuManager->setupOption(settings, "apply", "Apply Changes", settings_update);

	// Main menu setup
	menuManager->setupOption(mainMenu, "newgame", "New Game", newGame);
	menuManager->setupOption(mainMenu, "controls", "Show Controls", controls);
	menuManager->setupOption(mainMenu, "objectives", "Objectives", objectives);
	menuManager->setupOption(mainMenu, "settings", "Settings", settings);
	menuManager->setupOption(mainMenu, "credits", "Credits", credits);
	menuManager->setupOption(mainMenu, "exitgame", "Exit Game", running);
	credits->set_selected(5);

	menuManager->set_current_menu("Main Menu");	// Set the initial landing menu

	// Create the pause menu
	pauseMenu = menuManager->createMenu("Pause Menu");
	restart_trigger = false;
	continue_trigger = false;
	halt_trigger = false;
	menuManager->setupOption(pauseMenu, "continue", "Continue Game", continue_trigger);
	menuManager->setupOption(pauseMenu, "restart", "Restart Game", restart_trigger);
	menuManager->setupOption(pauseMenu, "controls", "Show Controls", controls);
	menuManager->setupOption(pauseMenu, "objectives", "Objectives", objectives);
	menuManager->setupOption(pauseMenu, "mainMenu", "Exit to Main Menu", halt_trigger);
	menuManager->setupOption(pauseMenu, "exitgame", "Exit Game", running);


	return true;
}

void HardLight::menu_update()
{


	if(game_launched && !scene_built)
	{
		if(classic)
		{
			cams = 1;
			config->SetLong("tail", "width", 1);
		}

		menuManager->set_current_menu("Now Loading...");
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
			window_width = 1024;
			window_height = 768;
			break;
		case(2):
			window_width = 800;
			window_height = 600;
			break;
		default:
			window_width = 600;
			window_height = 400;
			break;
		}

		if(isFullscreen)
		{
			// Hack: Fullscreen bugs out when trying to switch back to sdl renderer so we're going to fake it with borderless high resolution instead
			SDL_DisplayMode current;
			if(SDL_GetDesktopDisplayMode(0, &current) == 0)
				printf("Could not get current monitor display mode"); 
			window_width = current.w;
			window_height = current.h;
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

	if(classic)
	{
		classicOption->set_text("Classic Camera: Activated");
	}
	else if(!classic)
	{
		classicOption->set_text("Classic Camera: Disactivated");
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

