#pragma once
#include <vector>
#include "RigidBody.h"
#include "Force.h"

using std::vector;

class PhysicsEngine {
public:
    vector<RigidBody> bodies;
    vector<Force*> forces;

    void addBody(const RigidBody& body);
    void addForce(Force* force);

    void update(float dt);

private:
    vector<vector<RigidBody*>> bodyRefs;

    int gridWidth = 10;
    int gridHeight = 10;

    void applyForces();
    void integrateMotion(float dt);
    void handleCollisions();
    void updateGridSection();

    vector<vector<RigidBody*>> getNeighbours(const RigidBody& body);
};
