#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

enum EntityTypes
{
	GROUND		= 1 << 0,
	WHEEL		= 1 << 1,
	BIKE		= 1 << 2,
	WALL		= 1 << 3,
	UNDECLARED	= 1 << 4,
	SKYBOX		= 1 << 5,
	PICKUP		= 1 << 6,
	FLOOR		= 1 << 7,
	MENU_PANEL	= 1 << 8,
	CAMERA		= 1 << 9
};

enum BikeSubTypes
{
	BOT_BIKE,
	PLAYER_BIKE
};

#endif
