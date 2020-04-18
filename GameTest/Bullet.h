#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet() {
		pathTravel = 1.0f;
		speed = -0.01f;
		color = Color::WHITE;
		active = true;
	}

	//traveling speed
	float speed;
	Color color;

	//size
	float maxRad = 12;
	float minRad = 3;

	void Update() override {

		//update position
		if (pathTravel > 0.0f) {
			pathTravel += speed;
		}
		else {
			active = false;
		}

		//update size relative
		radius = minRad + (pathTravel * (maxRad - minRad));
	};

	void Draw(Vec2 location) override {

		Vec2::DrawLine(location + Vec2(radius, 0), location + Vec2(-radius, 0), color);
		Vec2::DrawLine(location + Vec2(0, radius), location + Vec2(0, -radius), color);
		Vec2::DrawLine(location + Vec2(radius, radius), location + Vec2(-radius, -radius), color);
		Vec2::DrawLine(location + Vec2(radius, -radius), location + Vec2(-radius, radius), color);

	}

	void Collided(Type other) override {
		//do nothing
	}

};

