// This class holds pointers to all bikes
#ifndef _BIKES_H
#define _BIKES_H

#include "Bike.h"
#include <vector>

using namespace std;

class Bikes
{
public:
	vector<Bike*> get_all_bikes();
	vector<Bike*> get_user_bikes();
	vector<Bike*> get_bot_bikes();

private:
	vector<Bike*> user_bikes;
	vector<Bike*> bot_bikes;
};

#endif