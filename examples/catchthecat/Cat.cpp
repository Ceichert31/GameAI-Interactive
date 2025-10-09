#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  auto path = generatePath(world);

  if (path.size() < 2) {
    return {};
  }

  return path[1];
}
