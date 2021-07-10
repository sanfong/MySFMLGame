#pragma once
#include "Animation.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player : public Entity
{
private:
	Animation animation;
	int state = 0;

public:
	bool idle = false;

public:
	Player(Vector2f shapeSize, Vector2f startPos, float speed, Animation* anime);

	void update(Vector2f mousePos, float deltaTime);
	void drawOn(RenderWindow& window);
};