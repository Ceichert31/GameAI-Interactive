#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto path = generatePath(world);
  int distance = path.size();

  if (path.size() < 1) {
    return Point2D();
  }

  std::cout << distance << "\n";
  if (distance > mBorderThreshold)
  {
    //If great distance, get average to block
    return path[distance / 2];
  }
  //Otherwise get border to block
  return path[distance - 1];
}
