#pragma once

#include "Vec2.h"
enum Type {
	NONE,
	BULLET,

	TOTAL,
};


//this stores any entity that can be stored in a path
class Entity
{
public:

	//amount traveled along path
	float pathTravel = 0.f;

	//path collision radius
	int radius = 0.f;

	//max and min sizes
	int maxRad;
	int minRad;

	//activity
	bool active = false;

	//type
	Type type = NONE;

	//direction of travel
	int dir;

	virtual void Update() = 0;

	virtual void Draw(Vec2) = 0;

	virtual void Collided(Entity*) = 0;
};
