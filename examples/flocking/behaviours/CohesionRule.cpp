#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  Vector2f centerOfMass;
  int numOfBoids = 0;
  float detectionRadius = boid->getDetectionRadius();

  for (auto neighbor : neighborhood) {
      //Calculate distance between boids
      Vector2f direction = neighbor->getPosition() - boid->getPosition();
      float distance = direction.getMagnitude();

      //Determine whether other boid is a neighbor
      if (distance < detectionRadius) {
        numOfBoids++;
        centerOfMass += neighbor->getPosition();
      }

      centerOfMass = centerOfMass / numOfBoids;
  }

  cohesionForce = (boid->getPosition() - centerOfMass) / detectionRadius;

  return cohesionForce.normalized();
}