#pragma once
#include "stdafx.h"

#include "Entity.h"

class Path {

public:
	Path(Vec2 outerLParam, Vec2 outerRParam, Vec2 innerLParam, Vec2 innerRParam) {
		outerL = outerLParam;
		outerR = outerRParam;
		innerL = innerLParam;
		innerR = innerRParam;

		outer = Vec2::Lerp(outerL, outerR, 0.5f);
		inner = Vec2::Lerp(innerL, innerR, 0.5f);
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

	//call this to draw path with all entities contained
	void Draw() {
		//draw path
		Vec2::DrawLine(outerL, outerR, 0.f, 0.f, 1.0f);
		Vec2::DrawLine(outerL, innerL, 0.f, 0.f, 1.0f);
		Vec2::DrawLine(innerR, outerR, 0.f, 0.f, 1.0f);
		Vec2::DrawLine(innerR, innerL, 0.f, 0.f, 1.0f);

		//draw entities
		for each (Entity* ent in entities)
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