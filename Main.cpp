#include <iostream>
#include <time.h>
#include "FongFunc.h"
#include "Entity.h"
#include "Player.h"
#include "Animation.h"
#include "Camera.h"
#include "Raycast.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

void fixedRatio(RenderWindow& window, Event& ev)
{
	window.setSize(Vector2u((unsigned int)ev.size.width, (unsigned int)ev.size.width * 600 / 800));
}

void clickOnce(Vector2f pos, bool click)
{
	static bool FLAG = true;
	if (click)
	{
		if (FLAG)
		{
			cout << pos.x << " " << pos.y << endl;
			FLAG = false;
		}
	}
	else
	{
		FLAG = true;
	}
}

int parallel()
{
	bool focus = true;

	RenderWindow window(VideoMode(800, 600), "Parallel", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	RectangleShape shape(Vector2f(10.f, 10.f));
	Vector2f shapePos = Vector2f(0.f, 0.f);
	float speed = 1.f;

	while (window.isOpen())
	{
		Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::Resized:
				fixedRatio(window, ev);
				break;

			case Event::GainedFocus:
				focus = true;
				break;
			case Event::LostFocus:
				focus = false;
				break;

			default:
				break;
			}
		}

		shape.setPosition(shapePos);
		shape.setFillColor(Color::Black);

		if (Keyboard::isKeyPressed(Keyboard::LControl))
			speed = 3.f;
		else
			speed = 2.f;

		if (focus)
		{
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				shapePos.y -= speed;
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				shapePos.x -= speed;
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				shapePos.y += speed;
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				shapePos.x += speed;
			}
		}

		window.clear(Color::Cyan);
		window.draw(shape);
		window.display();
	}

	return 0;
}

const int FRAMERATE = 60;
int main()
{
	RenderWindow window(VideoMode(800, 600), "Game", Style::Close);
	window.setFramerateLimit(FRAMERATE);
	View view;
	view.setSize((Vector2f)window.getSize());
	/*Thread thread(&troll);
	thread.launch();*/

	Clock clock;
	bool focus = true;
	float deltaTime = 0.0f;
	float speed = 3.f * FRAMERATE;
	srand(time(0));

	Camera camera(&view, (Vector2f)window.getSize() / 2.f);

	Texture mapTexture;
	if (!mapTexture.loadFromFile("Map.png"))
		cout << "Map Texture not loaded" << endl;
	RectangleShape map(Vector2f(100.f * 30.f, 100.f * 30.f));
	map.setPosition(-200.f, -200.f);
	map.setTexture(&mapTexture);

	RectangleShape wallMid(Vector2f(931.f, 938.f));
	wallMid.setPosition(834.f, 831.f); // opposite point - 1765 1769
	wallMid.setFillColor(Color(255, 255, 255, 128));

	Texture playerTexture;
	if (!playerTexture.loadFromFile("Player.png"))
		cout << "Player Texture not loaded" << endl;
	Animation anime(&playerTexture, Vector2u(4, 8), 0.2f);
	Player player(Vector2f(100.f, 100.f), Vector2f(200.f, 200.f), speed, &anime);

	Texture enemyTexture;
	if (!enemyTexture.loadFromFile("Enemy.png"))
		cout << "Enemy.png not loaded" << endl;
	Animation enemyAnime(&enemyTexture, Vector2u(2, 6), 0.3f);
	Enemy enemy(Vector2f(100.f, 100.f), Vector2f(400.f, 200.f), &enemyAnime, &player, speed / 2.f);
	Enemy enemy2(Vector2f(100.f, 100.f), Vector2f(300.f, 300.f), &enemyAnime, &player, speed / 2.f);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::Resized:
				fixedRatio(window, ev);
				break;

			case Event::GainedFocus:
				focus = true;
				break;
			case Event::LostFocus:
				focus = false;
				break;

			default:
				break;
			}
		}

		Vector2i localMouse = Mouse::getPosition(window);
		Vector2f mousePosView = window.mapPixelToCoords(localMouse);

		player.focus = focus;
		player.update(mousePosView, deltaTime);

		enemy.update(deltaTime);
		enemy2.update(deltaTime);

		//collision
		if (isCollided(player.getShape(), wallMid))
		{
			/*int bisect = 100;
			bool hit = true;
			Vector2f v = player.getVelocity();
			RectangleShape dummie(player.getShape());
			while (bisect > 0)
			{
				v /= 2.f;
				if (hit)
				{
					dummie.move(-v);
					hit = isCollided(dummie, wallMid);
				}
				else
				{
					dummie.move(v);
					hit = isCollided(dummie, wallMid);
				}
				bisect -= 1;
			}

			player.setPosition(dummie.getPosition());*/
			player.move(-player.getVelocity());
		}

		camera.update(mousePosView, player.getPosition(), deltaTime);

		//clickOnce(mousePosView, Mouse::isButtonPressed(Mouse::Button::Left));

		window.clear(Color(128, 128, 128));
		window.draw(map);
		window.setView(view);
		enemy.drawOn(window);
		enemy2.drawOn(window);
		player.drawOn(window);
		window.display();
	}
	return 0;
}