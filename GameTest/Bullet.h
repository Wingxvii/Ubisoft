#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(int dir) {
		//check direction
		if (dir == -1) {
			pathTravel = 1.0f;
			color = Color::WHITE;
		}
		else {
			pathTravel = 0.0f;
			color = Color::MAGENTA;
		}

		//setup
		speed = 0.01f;
		this->dir = dir;
		active = true;
		type = BULLET;

		maxRad = 12;
		minRad = 3;
	}

	//traveling speed
	float speed;
	Color color;

	//update
	void Update() override {

		//update position
		if (pathTravel < 0.0f || pathTravel > 1.0f) {
			active = false;
		}
		else {
			pathTravel += speed * dir;
		}

		//update size relative
		radius = minRad + (pathTravel * (maxRad - minRad));
	};

	//draw
	void Draw(Vec2 location) override {

		Vec2::DrawLine(location + Vec2(radius, 0), location + Vec2(-radius, 0), color);
		Vec2::DrawLine(location + Vec2(0, radius), location + Vec2(0, -radius), color);
		Vec2::DrawLine(location + Vec2(radius, radius), location + Vec2(-radius, -radius), color);
		Vec2::DrawLine(location + Vec2(radius, -radius), location + Vec2(-radius, radius), color);

	}

	//colision handling
	void Collided(Entity* other) override {
		if (other->type == BULLET) {
			active = false;
			other->active = false;
		}

	}

};

