#pragma once
#include "stdafx.h"
#include <vector>
#include "Path.h"
#include "Network.h"
#include "app\app.h"
#include "Animation.h"


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
	int lives = 3;

	//other player
	Path* otherPlayerPath;
	int otherPlayerIndex;
	int otherLives = 3;

	//network reference
	Network net;

	//game status
	bool gameActive = false;
	bool pause = false;

	//flag to keep track of explosion pause
	bool animationExplosionFlag = false;

	//init the level
	void InitMap(int level) {
		map.clear();

		gameActive = true;

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

			map[15].hasOtherPlayer = true;
			otherPlayerPath = &map[15];
			otherPlayerIndex = 15;
#pragma endregion map1

			break;
		default:
			break;
		}
	
	}

	//move player to the left
	void MoveLeft() {
		//ignore if paused
		if (pause) { return; }

		net.SendData(1);

		if (playerIndex == 15) {
			playerIndex = -1;
		}

		playerPath->hasPlayer = false;
		playerPath = &map[++playerIndex];
		playerPath->hasPlayer = true;
	}

	//move player to the right
	void MoveRight() {
		//ignore if paused
		if (pause) { return; }

		net.SendData(2);

		if (playerIndex == 0) {
			playerIndex = 16;
		}

		playerPath->hasPlayer = false;
		playerPath = &map[--playerIndex];
		playerPath->hasPlayer = true;
	}

	//player shoot
	void Shoot() {
		//ignore if paused
		if (pause) { return; }

		net.SendData(0);
		playerPath->entities.push_back(new Bullet(-1));
	}

	//when player is hit
	void OnDamage() {
		//update network
		net.SendData(3);

		//play animation
		Animation::PlayExplotion(playerPath->outer);

		//remove all entities
		for (int counter = 0; counter < map.size(); counter++) {
			map[counter].entities.clear();
		}
		lives--;

		//check if lost
		if (lives == 0) {
			gameActive = false;
			DrawLose();
		}
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

	//move player to the right
	void OtherMoveRight() {
		if (otherPlayerIndex == 15) {
			otherPlayerIndex = -1;
		}

		otherPlayerPath->hasOtherPlayer = false;
		otherPlayerPath = &map[++otherPlayerIndex];
		otherPlayerPath->hasOtherPlayer = true;

	}

	//other player shoot
	void OtherShoot() {
		otherPlayerPath->entities.push_back(new Bullet(1));
	}

	//when other player is hit
	void OnDamageOther() {

		//play animation
		Animation::PlayExplotion(otherPlayerPath->inner);

		//remove all entities
		for (int counter = 0; counter < map.size(); counter++) {
			for (Entity* ent : map[counter].entities) {
				ent->active = false;
			}
		}
		otherLives--;

		//check if won
		if (otherLives == 0) {
			gameActive = false;
			DrawWin();
		}
	}

	//draws player sprite in position
	void DrawMap() {

		//display win/lose
		if (!gameActive) { 	
			if (lives == 0) {
				DrawLose();
			}
			else {
				DrawWin();
			}
		}
		if (pause && !Animation::explosionActive) {
			DrawPause();
		}
		
		//draw
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

	//draw win over screen
	void DrawWin() {
		char winText[4] = "WIN";
		App::Print(500, 550, winText, 1.0f, 1.0f, 0.8f, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	//draw lose over screen
	void DrawLose() {
		char loseText[5] = "LOSE";
		App::Print(500, 550, loseText, 1.0f, 1.0f, 0.8f, GLUT_BITMAP_TIMES_ROMAN_24);

	}

	//draw pause
	void DrawPause() {
		if (!Animation::explosionActive && animationExplosionFlag) {
			animationExplosionFlag = false;
			pause = false;
			return;
		}

		char pauseText[7] = "PAUSED";
		App::Print(500, 550, pauseText, 1.0f, 1.0f, 0.8f, GLUT_BITMAP_TIMES_ROMAN_24);

	}


	//switch pause
	void Pause() {
		if (pause) {
			pause = false;
		}
		else {
			pause = true;
		}

	}

	//draws current lives for each player
	void DrawLives() {
		//current player lives
		for (int counter = 0; counter < lives; counter++) {
			int offset = -45;

			Vec2::DrawLine(	Vec2(193 + (offset * counter), 602),
							Vec2(178 + (offset * counter), 608), Color::YELLOW
			);
			Vec2::DrawLine(	Vec2(178 + (offset * counter), 608),
							Vec2(195 + (offset * counter), 615), Color::YELLOW
			);
			Vec2::DrawLine(	Vec2(195 + (offset * counter), 615),
							Vec2(215 + (offset * counter), 608), Color::YELLOW
			);
			Vec2::DrawLine(	Vec2(215 + (offset * counter), 608),
							Vec2(199 + (offset * counter), 602), Color::YELLOW
			);
			Vec2::DrawLine(	Vec2(199 + (offset * counter), 602),
							Vec2(205 + (offset * counter), 606), Color::YELLOW
			);
			Vec2::DrawLine(	Vec2(205 + (offset * counter), 606),
							Vec2(196 + (offset * counter), 608), Color::YELLOW
			);
			Vec2::DrawLine(	Vec2(196 + (offset * counter), 608),
							Vec2(187 + (offset * counter), 606), Color::YELLOW
			);
			Vec2::DrawLine(	Vec2(187 + (offset * counter), 606),
							Vec2(193 + (offset * counter), 602), Color::YELLOW
			);
		}

		//other player lives
		for (int counter = 0; counter < otherLives; counter++) {
			int offset = 45;

			Vec2::DrawLine(	Vec2(793 + (offset * counter), 602),
							Vec2(778 + (offset * counter), 608), Color::RED
			);															
			Vec2::DrawLine(	Vec2(778 + (offset * counter), 608),		
							Vec2(795 + (offset * counter), 615), Color::RED
			);															
			Vec2::DrawLine(	Vec2(795 + (offset * counter), 615),		
							Vec2(815 + (offset * counter), 608), Color::RED
			);															
			Vec2::DrawLine(	Vec2(815 + (offset * counter), 608),		
							Vec2(799 + (offset * counter), 602), Color::RED
			);															
			Vec2::DrawLine(	Vec2(799 + (offset * counter), 602),		
							Vec2(805 + (offset * counter), 606), Color::RED
			);															
			Vec2::DrawLine(	Vec2(805 + (offset * counter), 606),		
							Vec2(796 + (offset * counter), 608), Color::RED
			);															
			Vec2::DrawLine(	Vec2(796 + (offset * counter), 608),		
							Vec2(787 + (offset * counter), 606), Color::RED
			);															
			Vec2::DrawLine(	Vec2(787 + (offset * counter), 606),		
							Vec2(793 + (offset * counter), 602), Color::RED
			);
		}

	}

	//updates the path
	void Update() {
		//check to see if pause needs to be on
		if (Animation::explosionActive) { 
			pause = true; 
			animationExplosionFlag = true;
		}

		//check if game is active
		if (!gameActive || pause) { return; }

		//packet processing
		while (!net.packetsIn.empty()) {
			Packet* pack = &net.packetsIn.back();

			switch (pack->packet_type)
			{
			case 0:
				OtherShoot();
				break;
			case 1:
				OtherMoveLeft();
				break;
			case 2:
				OtherMoveRight();
				break;
			case 3:
				OnDamageOther();
				break;
			case 4:
				Pause();
				break;
			default:
				break;
			}

			net.packetsIn.pop_back();
		}

		//update path
		for (int counter = 0; counter < map.size(); counter++)
		{
			map[counter].Update();

			//check for flags
			if (map[counter].playerHit) {
				OnDamage();
				map[counter].playerHit = false;

			}
		}


	}
};

//singleton init
LevelManager* LevelManager::s_instance = 0;
