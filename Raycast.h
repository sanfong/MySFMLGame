#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

/*
Ray consisted of:
bool hit --> true if hit any
Vector2f point --> the contact point
float length --> distance from start to contact point
RectangleShape* hitRectangle --> pointer of the box
*/
typedef struct Ray
{
	bool hit = false; // true if hit any
	Vector2f point; // the contact point
	float length = 0.f; // distance from start to contact point
	RectangleShape* hitRectangle = NULL; // pointer of the box
} Ray;

/*
Return Ray - closest to start
Parameter:
Vector2f start = start point of the ray
Vector2f dir = direction of the ray
vector<RectangleShape*> includedBox = a vector of [pointer of RectangleShape]
*/
Ray raycast(Vector2f start, Vector2f dir, vector<RectangleShape*> includedBox);

/*
For checking only a box
Return Ray
Ray's hitRectangle will be NULL
Parameter:
Vector2f start = start point of the ray
Vector2f dir = direction of the ray
RectangleShape box = the box for checking against ray
*/
Ray raycast(Vector2f start, Vector2f dir, RectangleShape box);