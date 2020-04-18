#pragma once

#include "app\app.h"

enum Color {
	WHITE,
	BLACK,
	BLUE,
	GREEN,
	RED,
	YELLOW,
	MAGENTA,
	CYAN,


};

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

	//overloads
	Vec2 operator+(const Vec2 other) {
		return Vec2(_x + other._x, _y + other._y);
	}
	Vec2 operator-(const Vec2 other) {
		return Vec2(_x - other._x, _y - other._y);
	}
	Vec2 operator*(const float other) {
		return Vec2(_x * other, _y * other);
	}
	Vec2 operator*(const int other) {
		return Vec2(_x * other, _y * other);
	}

	//static helper functions

	//2d lerp
	static Vec2 Lerp(Vec2 start, Vec2 end, float t) {
		return Vec2(start._x * (1-t) + end._x * t, start._y * (1 - t) + end._y * t);
	}

	//drawline wrapper
	static void DrawLine(Vec2 x, Vec2 e, float r = 1.0f, float g = 1.0f, float b = 1.0f) {
		App::DrawLine(x._x, x._y, e._x, e._y, r, g, b);
	}

	static void DrawLine(Vec2 x, Vec2 e, Color color) {
		switch (color)
		{
		case WHITE:
			App::DrawLine(x._x, x._y, e._x, e._y, 1, 1, 1);
			break;
		case BLACK:
			App::DrawLine(x._x, x._y, e._x, e._y, 0, 0, 0);
			break;
		case BLUE:
			App::DrawLine(x._x, x._y, e._x, e._y, 0, 0, 1);
			break;
		case GREEN:
			App::DrawLine(x._x, x._y, e._x, e._y, 0, 1, 0);
			break;
		case RED:
			App::DrawLine(x._x, x._y, e._x, e._y, 1, 0, 0);
			break;
		case YELLOW:
			App::DrawLine(x._x, x._y, e._x, e._y, 1, 1, 0);
			break;
		case MAGENTA:
			App::DrawLine(x._x, x._y, e._x, e._y, 1, 0, 1);
			break;
		case CYAN:
			App::DrawLine(x._x, x._y, e._x, e._y, 0, 1, 1);
			break;

		default:
			break;
		}

	}


};