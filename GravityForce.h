#pragma once
#include "Force.h"
#include <vector>
#include "PhysicsEngine.h"
using std::vector;


class GravityForce : public Force {
public:
    Vector2D gravity;
    PhysicsEngine* physicsEngine;

    GravityForce(const Vector2D& gravity, PhysicsEngine* engine);
    long double mulScientific(long double a, long double b);

    Vector2D calculateForce(const RigidBody& body) override;
};
