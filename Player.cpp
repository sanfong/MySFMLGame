#include "Player.h"
#include "Animation.h"
#include "FongFunc.h"
#include <iostream>

using namespace sf;
using namespace std;

Player::Player(Vector2f shapeSize, Vector2f startPos, float speed, Animation* anime) :
	animation(*anime)
{
	shape.setSize(shapeSize);
	shape.setPosition(startPos);
	shape.setOrigin(shapeSize / 2.f);
	shape.setTexture(animation.texture);
	this->speed = speed;
}

void Player::update(Vector2f mousePos, float deltaTime)
{
	if (focus)
	{
		Vector2f size = shape.getSize();
		Vector2f dir = mousePos - shape.getPosition();
		velocity = normalize(dir) * speed * deltaTime;
		if (vectorLength(dir) > size.x)
		{
			move(velocity);
			idle = false;
		}
		else
		{
			idle = true;
		}

		#pragma region Game Boarder
		Vector2f playerPos = shape.getPosition();
		bool hitBoarder = false;
		if (playerPos.x - (size.x / 2.f) < -100.f)
		{
			playerPos.x = -100.f + (size.x / 2.f);
			hitBoarder = true;
		}
		if (playerPos.x + (size.x / 2.f) > 2700.f)
		{
			playerPos.x = 2700.f - (size.x / 2.f);
			hitBoarder = true;
		}
		if (playerPos.y - (size.y / 2.f) < -100.f)
		{
			playerPos.y = -100.f + (size.y / 2.f);
			hitBoarder = true;
		}
		if (playerPos.y + (size.y / 2.f) > 2700.f)
		{
			playerPos.y = 2700.f - (size.y / 2.f);
			hitBoarder = true;
		}
		if (hitBoarder)
		{
			setPosition(playerPos);
		}
		#pragma endregion

		if (abs(dir.y) > abs(dir.x)) // Up 3, 7 - Down 0, 4
		{
			if (dir.y >= 0)
			{
				state = (idle) ? 4 : 0;
			}
			else
			{
				state = (idle) ? 7 : 3;
			}
		}
		else // Right 1, 5 - Left - 2, 6
		{
			if (dir.x >= 0)
			{
				state = (idle) ? 5 : 1;
			}
			else
			{
				state = (idle) ? 6 : 2;
			}
		}

		animation.update(state, deltaTime);
		shape.setTextureRect(animation.uvRect);
	}
}

void Player::drawOn(RenderWindow& window)
{
	window.draw(shape);
}
