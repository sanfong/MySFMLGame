#pragma once
#include "Entity.h"
#include "Animation.h"
#include "FongFunc.h"

using namespace sf;
using namespace std;

class Enemy : public Entity
{
private:
	Animation animation;
	Entity* player;
	int key;

public:
	Enemy(Vector2f shapeSize, Vector2f startPos, Animation* anime, Entity* player, float speed, int key = -1);
	void update(float deltaTime);
	void drawOn(RenderWindow& window);
};