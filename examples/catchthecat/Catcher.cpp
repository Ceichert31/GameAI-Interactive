#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto path = generatePath(world);
  auto distance = path.size();

  if (path.empty()) {
    return Point2D();
  }

  std::cout << distance << "\n";
  return path[distance / 2];
}
