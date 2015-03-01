//==============================================================================
#include "HardLight.h"

//==============================================================================
int HardLight::OnExecute()
{
	if(!OnInit()) return EXIT_FAILURE;
	if(!BuildScene()) return EXIT_FAILURE;

	for (int i = 0 ; i < config->GetInteger("game", "numBots", 0) ; i++)
	{
		Bike* new_bike = new Bot_Bike();
		if(!CreateVehicle(new_bike, PxVec3(-100+i*20,5,600))) return EXIT_FAILURE;
		Bike* new_bike = new Bike();
		if(!CreateVehicle(new_bike, PxVec3(0,50,600))) return EXIT_FAILURE;
		bikes.add_bot_bike(new_bike);
	}
	
	for (int i = 0 ; i < config->GetInteger("game", "numPlayers", 1) ; i++)
	{
		Bike* new_bike = new Player_Bike();
		bikes.add_player_bike(new_bike, controllers[i]);
		if(!CreateVehicle(new_bike, PxVec3(0,5,550))) return EXIT_FAILURE;
	//	bike = new_bike;
		Bike* new_bike = new Bike();
		if(!CreateVehicle(new_bike, PxVec3(0,30,600))) return EXIT_FAILURE;
		bikes.add_player_bike(new_bike, controllers[i]);
	}

	controller = new Player_Controller(bikes.get_player_bikes()[0], controllers[0]);

    SDL_Event Event;

    while(running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();
	
	return EXIT_SUCCESS;
}

//==============================================================================
