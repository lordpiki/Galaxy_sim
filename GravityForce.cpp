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
    if (body.mass == 0.0f) return Vector2D(0.0f, 0.0f); // Prevent division by zero (infinite acceleration
    for (const RigidBody& otherBody : physicsEngine->bodies)
	{
		if (body.position != otherBody.position)
		{
			Vector2D direction = (otherBody.position - body.position).normalized();
			// Calculate force
			long double m1m2 = mulScientific(body.mass, otherBody.mass);
			long double Gm1m2 = mulScientific(G, m1m2);
			long double r_squared = body.position.distanceSquared(otherBody.position);
			long double forceMagnitude = Gm1m2 / r_squared;
			float angle = atan2(direction.y, direction.x);
			Vector2D force = direction;
			force.x = forceMagnitude * cos(angle);
			force.y = forceMagnitude * sin(angle);
			return force;
		}
	}
    return Vector2D();
}


