#pragma once
#include "FongFunc.h"

using namespace sf;
using namespace std;

class Entity
{
protected:
	RectangleShape shape;
	Vector2f oldPosition;
	Vector2f velocity;
	float speed = 1.f;

public:
	bool focus = true;

	virtual RectangleShape getShape();

	virtual Vector2f getPosition();
	virtual void setPosition(Vector2f position);
	virtual void move(Vector2f offset);

	virtual Vector2f getOldPosition();
	virtual void setOldPosition();

	virtual Vector2f getVelocity();

	virtual float getSpeed();
	virtual void setSpeed(float speed);
};