#include "PhysicsEngine.h"
#include "Collision.h"
#include <algorithm> // for std::swap


void PhysicsEngine::addBody(const RigidBody& body) {
    bodies.push_back(body);
}

void PhysicsEngine::addForce(Force* force) {
    forces.push_back(force);
}

void PhysicsEngine::update(float dt) {
    applyForces();
    integrateMotion(dt);
    handleCollisions();
    updateGridSection();
}

void PhysicsEngine::applyForces() {
    for (RigidBody& body : bodies) {
        Vector2D totalForce(0.0f, 0.0f);
        for (Force* force : forces) 
        {
            totalForce = totalForce + force->calculateForce(body);
        }
        body.applyForce(totalForce);
    }
}

void PhysicsEngine::integrateMotion(float dt) {
    for (RigidBody& body : bodies) {
        body.integrate(dt);
    }
}

void PhysicsEngine::handleCollisions() {
     //Existing body-to-body collision handling
    for (RigidBody& body : bodies) {
        if (Collision::checkWallCollision(body)) {
            Collision::resolveWallCollision(body);
        }
    }

    for (RigidBody& body : bodies)
    {
        vector<vector<RigidBody*>> neighbours = getNeighbours(body);
		for (vector<RigidBody*> neighbour : neighbours)
		{
			for (RigidBody* otherBody : neighbour)
			{
				if (Collision::checkCollision(body, *otherBody))
				{
					Collision::resolveCollision(body, *otherBody);
				}
			}
		}
    }

}

void PhysicsEngine::updateGridSection()
{
    for (RigidBody& body : bodies)
	{
        int oldIndex = body.gridSection.x + body.gridSection.y;
		body.gridSection.x = (int)(body.position.x / gridWidth);
		body.gridSection.y = (int)(body.position.y / gridHeight);
        int newIndex = body.gridSection.x + body.gridSection.y;

        if (oldIndex != newIndex)
		{
            // Remove the body from the old grid section
			std::swap(bodyRefs[oldIndex][body.currentVecIndex], bodyRefs[oldIndex].back());
            bodyRefs[oldIndex].pop_back();

            // Add the body to the new grid section
            bodyRefs[newIndex].push_back(&body);
            body.currentVecIndex = bodyRefs[newIndex].size() - 1;
		}
	}
}

vector<vector<RigidBody*>> PhysicsEngine::getNeighbours(const RigidBody& body)
{
    vector<vector<RigidBody*>> neighbours;
    
    int gridSecX = body.gridSection.x;
    int gridSecY = body.gridSection.y;

    for (int i = -1 ; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
            int index = gridSecX + i + gridSecY + j;
			if (index >= 0 && index < bodyRefs.size())
			{
				neighbours.push_back(bodyRefs[index]);
			}
		}
	}
    
    return neighbours;
}

