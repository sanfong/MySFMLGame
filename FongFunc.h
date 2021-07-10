#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

Vector2f normalize(Vector2f vec);
float distance(Vector2f a, Vector2f b);
float vectorLength(Vector2f vec);
bool isCollided(RectangleShape shape1, RectangleShape shape2);