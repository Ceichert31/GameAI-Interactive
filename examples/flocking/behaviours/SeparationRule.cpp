#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {

  //Bootstrap case
  if (neighborhood.empty())
    return Vector2f::zero();

  // Try to avoid boids too close
  Vector2f separatingForce{};

  float desiredDistance = desiredMinimalDistance;

    //Iterate through neighbors and calculate distance from all
  for (auto neighbor : neighborhood) {
      //Calculate distance between boids
      Vector2f direction = neighbor->getPosition() - boid->getPosition();

      //Divide normalized Pa - Pi by magnitude of Pa - Pi
      separatingForce += direction.normalized() / direction.getMagnitude();
    }

  //Eventually clamp here
  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

//
//    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
//    if (!neighborhood.empty()) {
//        Vector2f position = boid->transform.position;
//        int countCloseFlockmates = 0;
//        // todo: find and apply force only on the closest mates
//    }


bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
