#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Camera
{
private:
	View* view;

public:
	Vector2f target;

	Camera(View* view, Vector2f startPos);
	void setPosition(Vector2f pos);
	Vector2f getPosition() { return view->getCenter(); };
	void update(Vector2f mousePos, Vector2f playerPos, float deltaTime);
};