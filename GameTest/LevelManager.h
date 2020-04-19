#pragma once
#include "stdafx.h"

#include <vector>
#include "Path.h"


class LevelManager {

#pragma region singleton 
	static LevelManager* s_instance;

public:
	static LevelManager* instance()
	{
		if (!s_instance) {
			s_instance = new LevelManager;
		}
		return s_instance;
	}
#pragma endregion singleton

	//map
	std::vector<Path> map;

	//player
	Path* playerPath;
	int playerIndex;

	//other player
	Path* otherPlayerPath;
	int otherPlayerIndex;

	//init the level
	void InitMap(int level) {
		map.clear();

		switch (level)
		{
		case 1:

	#pragma region map1
			map.push_back(Path(
				Vec2(510, 595),
				Vec2(413, 573),
				Vec2(510, 281),
				Vec2(496, 278)
				));
			map.push_back(Path(
				Vec2(413, 573),
				Vec2(326, 515),
				Vec2(496, 278),
				Vec2(483, 270)
				));
			
			map.push_back(Path(
				Vec2(326, 515),
				Vec2(270, 430),
				Vec2(483, 270),
				Vec2(474, 256)
			));
			map.push_back(Path(
				Vec2(270, 430),
				Vec2(248, 333),
				Vec2(474, 256),
				Vec2(472, 240)
			));
			map.push_back(Path(
				Vec2(248, 333),
				Vec2(270, 240),
				Vec2(472, 240),
				Vec2(474, 227)
			));
			map.push_back(Path(
				Vec2(270, 240),
				Vec2(327, 153),
				Vec2(474, 227),
				Vec2(483, 213)
			));
			map.push_back(Path(
				Vec2(327, 153),
				Vec2(412, 99),
				Vec2(483, 213),
				Vec2(497, 206)
			));
			map.push_back(Path(
				Vec2(412, 99),
				Vec2(510, 78),
				Vec2(497, 206),
				Vec2(510, 202)
			));
			map.push_back(Path(
				Vec2(510, 78),
				Vec2(610, 100),
				Vec2(510, 202),
				Vec2(526, 205)
			));
			map.push_back(Path(
				Vec2(610, 100),
				Vec2(695, 153),
				Vec2(526, 205),
				Vec2(540, 213)
			));
			map.push_back(Path(
				Vec2(695, 153),
				Vec2(750, 237),
				Vec2(540, 213),
				Vec2(548, 227)
			));
			map.push_back(Path(
				Vec2(750, 237),
				Vec2(775, 335),
				Vec2(548, 227),
				Vec2(550, 242)
			));
			map.push_back(Path(
				Vec2(775, 335),
				Vec2(752, 430),
				Vec2(550, 242),
				Vec2(547, 257)
			));
			map.push_back(Path(
				Vec2(752, 430),
				Vec2(697, 515),
				Vec2(547, 257),
				Vec2(538, 269)
			));
			map.push_back(Path(
				Vec2(697, 515),
				Vec2(611, 572),
				Vec2(538, 269),
				Vec2(526, 277)
			));
			map.push_back(Path(
				Vec2(611, 572),
				Vec2(510, 595),
				Vec2(526, 277),
				Vec2(510, 281)
			));
			map[0].hasPlayer = true;
			playerPath = &map[0];
			playerIndex = 0;

			map[0].hasOtherPlayer = true;
			otherPlayerPath = &map[0];
			otherPlayerIndex = 0;
#pragma endregion map1

			break;
		default:
			break;
		}
	
	}

	//move player to the left
	void MoveLeft() {
		if (playerIndex == 15) {
			playerIndex = -1;
		}

		playerPath->hasPlayer = false;
		playerPath = &map[++playerIndex];
		playerPath->hasPlayer = true;
	}

	//move player to the rightr
	void MoveRight() {
		if (playerIndex == 0) {
			playerIndex = 16;
		}

		playerPath->hasPlayer = false;
		playerPath = &map[--playerIndex];
		playerPath->hasPlayer = true;
	}

	//move player to the rightr
	void Shoot() {
		playerPath->entities.push_back(new Bullet(-1));
	}


	//move player to the left
	void OtherMoveLeft() {
		if (otherPlayerIndex == 0) {
			otherPlayerIndex = 16;
		}

		otherPlayerPath->hasOtherPlayer = false;
		otherPlayerPath = &map[--otherPlayerIndex];
		otherPlayerPath->hasOtherPlayer = true;

	}

	//move player to the rightr
	void OtherMoveRight() {
		if (otherPlayerIndex == 15) {
			otherPlayerIndex = -1;
		}

		otherPlayerPath->hasOtherPlayer = false;
		otherPlayerPath = &map[++otherPlayerIndex];
		otherPlayerPath->hasOtherPlayer = true;

	}

	//move player to the rightr
	void OtherShoot() {
		otherPlayerPath->entities.push_back(new Bullet(1));
	}



	//draws player sprite in position
	void DrawMap() {
		for (int counter = 0; counter < map.size(); counter++)
		{
			if (!map[counter].hasPlayer || !map[counter].hasOtherPlayer) {
				map[counter].Draw();
			}
		}
		//draw player path on top
		otherPlayerPath->Draw();
		playerPath->Draw();

	}

	//updates the path
	void Update() {
		for (int counter = 0; counter < map.size(); counter++)
		{
			map[counter].Update();
		}
	}
};

//singleton init
LevelManager* LevelManager::s_instance = 0;
