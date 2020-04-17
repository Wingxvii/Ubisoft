#pragma once

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

	//math

	//2d lerp
	static Vec2 Lerp(Vec2 start, Vec2 end, float t) {
		return Vec2(start._x * (1-t) + end._x * t, start._y * (1 - t) + end._y * t);
	}
};