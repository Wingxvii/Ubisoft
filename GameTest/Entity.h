#pragma once

#include "Vec2.h"

//this stores any entity that can be stored in a path
class Entity
{
public:
	Entity() {};

	//amount traveled along path
	float pathTravel = 0.f;

	void Draw(Vec2 location) {
		//draw at location

	}


};
