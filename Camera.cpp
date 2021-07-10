#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Camera::Camera(View* view, Vector2f startPos)
{
	this->view = view;
	this->view->setCenter(startPos);
}

void Camera::setPosition(Vector2f pos)
{
	view->setCenter(pos);
}

const int FRAMERATE = 60;
void Camera::update(Vector2f mousePos, Vector2f playerPos, float deltaTime)
{
	Vector2f dirPlayerMouse = mousePos - playerPos;
	target = playerPos + (dirPlayerMouse / 3.f);
	Vector2f cameraDir = target - view->getCenter();

	Vector2f lerp = cameraDir * (0.1f * FRAMERATE / (1.f / deltaTime));
	view->move(lerp);
}
