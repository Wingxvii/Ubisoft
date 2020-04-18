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
	}

	//currently has player
	bool hasPlayer;

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
			if (!entities[counter]->active) {
				garbageList.push_back(counter);
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
			for each (Entity * ent2 in entities)
			{
				bool collided = false;
				//skip
				if (ent == ent2) { continue; }

				//collision checks
				if (ent->pathTravel == ent2->pathTravel) {
					collided = true;
				}else if (ent->pathTravel > ent2->pathTravel && 
					ent->pathTravel - ent->radius < ent2->pathTravel + ent2->radius) {
					collided = true;
				}else if (ent->pathTravel < ent2->pathTravel && 
					ent->pathTravel + ent->radius > ent2->pathTravel - ent2->radius) {
					collided = true;
				}

				//handle collision
				if (collided) {
					ent->Collided(ent2->type);
					ent2->Collided(ent->type);
				}
			}
		}

	}

	//call this to draw path with all entities contained
	void Draw() {
		//draw path
 		if (hasPlayer) {
			Vec2::DrawLine(outerL, outerR, 1.f, 1.f, 0.0f);
			Vec2::DrawLine(outerL, innerL, 1.f, 1.f, 0.0f);
			Vec2::DrawLine(innerR, outerR, 1.f, 1.f, 0.0f);
			Vec2::DrawLine(innerR, innerL, 1.f, 1.f, 0.0f);
		}
		else {
			Vec2::DrawLine(outerL, outerR, 0.f, 0.f, 1.0f);
			Vec2::DrawLine(outerL, innerL, 0.f, 0.f, 1.0f);
			Vec2::DrawLine(innerR, outerR, 0.f, 0.f, 1.0f);
			Vec2::DrawLine(innerR, innerL, 0.f, 0.f, 1.0f);
		}
		//draw entities
		for (Entity* ent : entities)
		{
			ent->Draw(Vec2::Lerp(inner, outer, ent->pathTravel));
		}

	}

	//clean up entities
	~Path(){
		while (!entities.empty()) {
			delete entities.back();
			entities.pop_back();
		}

	}


};