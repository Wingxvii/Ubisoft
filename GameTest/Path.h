#pragma once
#include "Vec2.h"
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
	Entity* entities[];

	//call this to draw path with all entities contained
	void Draw() {
		//draw path

		//draw entities


	}
};