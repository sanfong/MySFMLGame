#include "FongFunc.h"
#include <iostream>

using namespace sf;
using namespace std;

Vector2f normalize(Vector2f vec)
{
	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	return vec / length;
}

float distance(Vector2f a, Vector2f b)
{
	Vector2f vec = a - b;
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float vectorLength(Vector2f vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

bool isCollided(RectangleShape a, RectangleShape b)
{
	Vector2f aPos = a.getPosition() - a.getOrigin();
	Vector2f aSize = a.getSize();

	Vector2f bPos = b.getPosition() - b.getOrigin();
	Vector2f bSize = b.getSize();

	if (aPos.x < bPos.x + bSize.x && aPos.x + aSize.x > bPos.x && aPos.y < bPos.y + bSize.y && aPos.y + aSize.y > bPos.y)
	{
		return true;
	}
	return false;
}