#include "Entity.h"
#include "FongFunc.h"

using namespace sf;
using namespace std;

RectangleShape Entity::getShape()
{
	return shape;
}

Vector2f Entity::getPosition()
{
	return shape.getPosition();
}

void Entity::setPosition(Vector2f position)
{
	oldPosition = shape.getPosition();
	shape.setPosition(position);
}

void Entity::move(Vector2f offset)
{
	oldPosition = shape.getPosition();
	shape.move(offset);
}

Vector2f Entity::getOldPosition()
{
	return oldPosition;
}

void Entity::setOldPosition()
{
	oldPosition = shape.getPosition();
}

Vector2f Entity::getVelocity()
{
	return velocity;
}

float Entity::getSpeed()
{
	return speed;
}

void Entity::setSpeed(float speed)
{
	this->speed = speed;
}
