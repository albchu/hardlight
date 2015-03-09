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
	TAIL_SEGMENT= 1 << 6,
	PICKUP		= 1 << 7,
	FLOOR		= 1 << 8
};

#endif
