#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  float centerOfMass = 0;

  for (auto neighbor : neighborhood) {
    //Divide sum of positions by number of neighbors
      //Calculate distance between boids
      Vector2f direction = neighbor->getPosition() - boid->getPosition();
      float distance = direction.getMagnitude();

      if (distance < neighbor->getDetectionRadius() ) {

      }
  }

  // find center of mass

  return cohesionForce;
}