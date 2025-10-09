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

  std::vector<Point2D> getVisitableNeighbors(World* world, Point2D current, const std::unordered_map<Point2D, bool>& visited, const std::unordered_set<Point2D>& frontierSet);

  bool isNeighborValid(World* w, Point2D current, const std::unordered_map<Point2D, bool>& visited, const std::unordered_set<Point2D>& frontierSet);

  struct WeightedPoint2D {
    Point2D point{};
    float weight{};

    WeightedPoint2D() {
      point = Point2D();
      weight = 0;
    }

    WeightedPoint2D(Point2D p, float w) {
      point = p;
      weight = w;
    }

    bool operator>(WeightedPoint2D const a) const {
      return weight > a.weight;
    }
    bool operator<(WeightedPoint2D const a) const {
      return weight < a.weight;
    }
    bool operator==(WeightedPoint2D const a) const {
      return point == a.point && weight == a.weight;
    }
  };
};

#endif  // AGENT_H
