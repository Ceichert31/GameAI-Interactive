#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;
  Vector2f centerOfMass{};
  int numOfBoids{};
  float detectionRadius = boid->getDetectionRadius();

  for (auto neighbor : neighborhood) {
      numOfBoids++;
      centerOfMass += neighbor->getPosition();
  }
  //Calculate center of mass
  centerOfMass = centerOfMass / numOfBoids;

  //Set cohesion force
  cohesionForce = (boid->getPosition() - centerOfMass) / detectionRadius;

  return cohesionForce.normalized();
}