#pragma once

#include "app\app.h"

class Vec2 {
public:
	Vec2(){
		_x = 0;
		_y = 0;
	}

	Vec2(int x ,int y) {
		_x = x;
		_y = y;
	}
	int _x;
	int _y;


	//static helper functions

	//2d lerp
	static Vec2 Lerp(Vec2 start, Vec2 end, float t) {
		return Vec2(start._x * (1-t) + end._x * t, start._y * (1 - t) + end._y * t);
	}

	//drawline wrapper
	static void DrawLine(Vec2 x, Vec2 e, float r = 1.0f, float g = 1.0f, float b = 1.0f) {
		App::DrawLine(x._x, x._y, e._x, e._y, r, g, b);
	}


};