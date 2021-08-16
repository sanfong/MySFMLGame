#include "Enemy.h"
#include "FongFunc.h"

using namespace sf;
using namespace std;

Enemy::Enemy(Vector2f shapeSize, Vector2f startPos, Animation* anime, Entity* player, float speed, int key) :
	animation(*anime)
{
	this->player = player;
	this->speed = speed;
	this->key = (key != -1) ? key : rand() % 6;

	shape.setSize(shapeSize);
	shape.setPosition(startPos);
	shape.setOrigin(shapeSize / 2.f);
	shape.setTexture(animation.texture);

	cout << key << endl;
}

void Enemy::update(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(key)))
	{
		char c = key + 'a';
		cout << c << " Died!" << endl;
	}

	Vector2f dir = player->getPosition() - getPosition();
	velocity = normalize(dir) * speed * deltaTime;
	move(velocity);

	animation.update(key, deltaTime);
	shape.setTextureRect(animation.uvRect);
}

void Enemy::drawOn(RenderWindow& window)
{
	window.draw(shape);
}
