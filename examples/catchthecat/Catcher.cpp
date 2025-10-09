#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto path = generatePath(world);
  int distance = path.size();

  if (path.size() < 2) {
    return Point2D();
  }

  std::cout << distance << "\n";
  if (distance < world->getWorldSideSize() / 4)
  {
    return path[distance - 1];
  }
  return path[distance / 4];
}
