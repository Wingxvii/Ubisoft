#pragma once
#include "Entity.h"
#include "Bullet.h"

class Path {

public:
	Path(Vec2 outerLParam, Vec2 outerRParam, Vec2 innerLParam, Vec2 innerRParam) {
		outerL = outerLParam;
		outerR = outerRParam;
		innerL = innerLParam;
		innerR = innerRParam;

		outer = Vec2::Lerp(outerL, outerR, 0.5f);
		inner = Vec2::Lerp(innerL, innerR, 0.5f);
		hasPlayer = false;
		hasOtherPlayer = false;
	}
	//clean up entities
	~Path() {
		while (!entities.empty()) {
			delete entities.back();
			entities.pop_back();
		}

	}

	//currently has player
	bool hasPlayer;

	//currently has contesting player
	bool hasOtherPlayer;

	//is enabled
	bool enabled;

	//outer left
	Vec2 outerL;
	//outer right
	Vec2 outerR;
	//inner left
	Vec2 innerL;
	//inner right
	Vec2 innerR;

	//central path
	Vec2 outer;
	Vec2 inner;

	//player hit flag
	bool playerHit = false;

	//entity list
	std::vector<Entity*> entities;

	//this updates entities contained and checks colision
	void Update() {

		//list to track garbage collector in reverse index order
		std::vector<int> garbageList;

		//update in reverse index order
		for(int counter = entities.size() -1; counter >=0 ; counter--)
		{
			entities[counter]->Update();
			if (!entities[counter]->active){
				garbageList.push_back(counter);

				//check local player collision
				if ((entities[counter]->pathTravel <= 0.0f || entities[counter]->pathTravel >= 1.0f))
				{
					if ((hasPlayer) && entities[counter]->type == BULLET && entities[counter]->dir != -1) {
						//damaged
						playerHit = true;
					}

				}
			}

		}

		//garbage collect in reverse index order
		for (int item : garbageList)
		{
			entities.erase(entities.begin() + item);
		}

		//check colision
		for (Entity * ent : entities)
		{
			for (Entity * ent2 : entities)
			{
				//skip if same direction or if same
				if (ent == ent2 || ent->dir == ent2->dir) { continue; }

				//check collsion using circle method
				if (Vec2::Dist(Vec2::Lerp(inner, outer, ent->pathTravel), Vec2::Lerp(inner, outer, ent2->pathTravel)) < ent->radius + ent2->radius) {
					ent->Collided(ent2);
					ent2->Collided(ent);
				}
			}
		}

	}

	//call this to draw path with all entities contained
	void Draw() {
		//draw path
 		if (hasPlayer) {
			Vec2::DrawLine(outerL, outerR, Color::YELLOW);
			Vec2::DrawLine(outerL, innerL, Color::YELLOW);
			Vec2::DrawLine(innerR, outerR, Color::YELLOW);
			Vec2::DrawLine(innerR, innerL, Color::YELLOW);
		}
		else if (hasOtherPlayer) {
			Vec2::DrawLine(outerL, outerR, Color::RED);
			Vec2::DrawLine(outerL, innerL, Color::RED);
			Vec2::DrawLine(innerR, outerR, Color::RED);
			Vec2::DrawLine(innerR, innerL, Color::RED);
		}
		else {
			Vec2::DrawLine(outerL, outerR, Color::BLUE);
			Vec2::DrawLine(outerL, innerL, Color::BLUE);
			Vec2::DrawLine(innerR, outerR, Color::BLUE);
			Vec2::DrawLine(innerR, innerL, Color::BLUE);
		}
		//draw entities
		for (Entity* ent : entities)
		{
			ent->Draw(Vec2::Lerp(inner, outer, ent->pathTravel));
		}

	}




};