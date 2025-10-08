#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);

  std::vector<Point2D> getVisitableNeighbors(World* world, Point2D current, std::unordered_map<Point2D, bool> visited, std::unordered_set<Point2D> frontierSet);

  bool isNeighborValid(World* w, Point2D current, std::unordered_map<Point2D, bool> visited,  std::unordered_set<Point2D> frontierSet);

  float heuristic(Point2D a, Point2D b);
};

#endif  // AGENT_H
