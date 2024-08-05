#include "GravityForce.h"
#include <cmath>
#include <iomanip>

#define G 6.67430e-10f // Gravitational constant (scaled up to make the forces more noticeable)

GravityForce::GravityForce(const Vector2D& gravity, PhysicsEngine* engine) : gravity(gravity), physicsEngine(engine) {}

long double GravityForce::mulScientific(long double a, long double b)
{
	int exp_a, exp_b;
	long double sig_a = std::frexp(a, &exp_a);
	long double sig_b = std::frexp(b, &exp_b);

	long double result_sig = sig_a * sig_b;
	int result_exp = exp_a + exp_b;

	return std::ldexp(result_sig, result_exp);
}

Vector2D GravityForce::calculateForce(const RigidBody& body)
{
	if (body.mass == 0) return Vector2D(0.0f, 0.0f);
    return gravity * body.mass;
}


