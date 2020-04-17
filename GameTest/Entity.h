#pragma once

#include "Path.h"

//this stores any entity that can be stored in a path
class Entity
{
	Path* parent;

	//amount traveled along path
	float pathTravel = 0.f;

};

