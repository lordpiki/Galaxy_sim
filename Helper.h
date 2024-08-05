#pragma once
#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "RigidBody.h"
#include "Force.h"

class Helper
{
public:
	static float distance(const Vector2D& a, const Vector2D& b);
	static float getRand(float min = -1, float max = 1);
	static Vector2D getRandVector(float min = -1, float max = 1);

};

