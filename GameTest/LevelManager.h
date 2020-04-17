#pragma once
#include "stdafx.h"

#include <vector>
#include "Path.h"

class LevelManager {
	static LevelManager* s_instance;

public:
	static LevelManager* instance()
	{
		if (!s_instance) {
			s_instance = new LevelManager;
		}
		return s_instance;
	}

	std::vector<Path> map;

	void InitMap(int level) {
		map.clear();

		switch (level)
		{
		case 1:






			break;
		default:
			break;
		}
	
	}


	//draws player sprite in position
	void DrawMap() {
		for each (Path path in map)
		{
			path.Draw();
		}
	}




};

LevelManager* LevelManager::s_instance = 0;
