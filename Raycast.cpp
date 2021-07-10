#include "Raycast.h"

using namespace sf;
using namespace std;

float cross(Vector2f a, Vector2f b)
{
	return a.x * b.y - a.y * b.x;
}

Vector2f* rayIntersectLine(Vector2f start, Vector2f dir, Vector2f line[2])
{
	// start = p, q = pointA
	Vector2f s = line[1] - line[0]; // direction AB
	float rxs = cross(dir, s);
	if (rxs != 0)
	{
		float u = cross((line[0] - start), dir) / rxs;
		float t = cross((line[0] - start), s) / rxs;
		if (0 <= u && u <= 1 && t >= 0)
		{
			Vector2f result = line[0] + (u * s);
			return &result;
		}
	}
	return NULL;
}

float distanceBetween2Point(Vector2f a, Vector2f b)
{
	Vector2f vec = a - b;
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Vector2f minimumDistance(vector<Vector2f> vecs, Vector2f point)
{
	if (vecs.empty())
		return Vector2f();
	Vector2f closest = vecs.at(0);
	for (size_t i = 0; i < vecs.size(); i++)
	{
		float closelen = distanceBetween2Point(closest, point);
		float challenger = distanceBetween2Point(vecs.at(i), point);
		if (challenger < closelen)
		{
			closest = vecs.at(i);
		}
	}
	return closest;
}

Ray raycast(Vector2f start, Vector2f dir, RectangleShape box)
{
	Ray thisRay;
	Vector2f pos = box.getPosition() - box.getOrigin();
	Vector2f size = box.getSize();
	// Broken down into 4 lines
	Vector2f lines[4][2] = {
		{pos, Vector2f(pos.x + size.x, pos.y)},
		{pos, Vector2f(pos.x, pos.y + size.y)},
		{Vector2f(pos.x + size.x, pos.y), pos + size},
		{Vector2f(pos.x, pos.y + size.y), pos + size}
	};
	vector<Vector2f> hitlines; // list of contact point
	for (size_t i = 0; i < 4; i++)
	{
		Vector2f* ptr = rayIntersectLine(start, dir, lines[i]);
		if (ptr != NULL)
		{
			hitlines.push_back(*ptr);
		}
	}
	if (!hitlines.empty())
	{
		thisRay.hit = true;
		thisRay.point = minimumDistance(hitlines, start);
		thisRay.length = distanceBetween2Point(start, thisRay.point);
	}
	return thisRay;
}

Ray raycast(Vector2f start, Vector2f dir, vector<RectangleShape*> includedBox)
{
	Ray ray;
	for (size_t i = 0; i < includedBox.size(); i++)
	{
		Ray a_ray = raycast(start, dir, *includedBox.at(i));
		if (a_ray.hit)
		{
			a_ray.hitRectangle = includedBox.at(i);
			if (a_ray.length < ray.length || ray.hitRectangle == NULL)
			{
				ray = a_ray;
			}
		}
	}
	return ray;
}