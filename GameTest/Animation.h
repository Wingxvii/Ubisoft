#pragma once
#include "Vec2.h"
#include <map>
#include <utility>
#include "app\app.h"


class Animation {

	static int explosionTimer;
	static CSimpleSprite* explosion;

public:
	
	static bool explosionActive;

	//init animation
	static void Init() {
		explosionActive = false;
		explosionTimer = 0;
		explosion = App::CreateSprite(".\\explotion.bmp", 7, 1);
		float speed = 2.0f / 7.0f;
		explosion->CreateAnimation(0, speed, { 0,1,2,3,4,5,6 });
		explosion->SetScale(1.0f);
	}	

	//update call
	static void Update(float deltaTime) {
		if (explosionActive) {
			explosionTimer -= deltaTime;
			explosion->Update(deltaTime);

			if (explosionTimer <= 0) {
				explosionActive = false;
				//move to void
				explosion->SetPosition(-1000,-1000);

			}
		}
	}

	//draw
	static void Draw() {
		if (explosionActive) {
			explosion->Draw();
		}
	}

	//start play explotion
	static void PlayExplotion(Vec2 location) {
		explosion->SetPosition(location._x, location._y);
		explosion->SetAnimation(0);
		explosionActive = true;
		explosionTimer = 2000.0f;
	}
};


//init static variables
int Animation::explosionTimer = 0;
CSimpleSprite* Animation::explosion = 0;
bool Animation::explosionActive = false;
