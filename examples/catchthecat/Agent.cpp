#include "Agent.h"

#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  unordered_map<Point2D, float> costSoFar;
  priority_queue<WeightedPoint2D, vector<WeightedPoint2D>, greater<WeightedPoint2D>> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  WeightedPoint2D catPos = WeightedPoint2D(w->getCat(), 1);
  frontier.push(catPos);
  costSoFar[catPos.point] = 0;
  frontierSet.insert(catPos.point);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points


  while (!frontier.empty()) {
    // get the current from frontier
    auto currentPoint = frontier.top();
    // remove the current from frontierset
    frontier.pop();
    // mark current as visited
    visited[currentPoint.point] = true;

    //If algorithm hits border, set border exit
    if (w->catWinsOnSpace(currentPoint.point)) {
      borderExit = currentPoint.point;
      break;
    }

    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    auto neighbors = getVisitableNeighbors(w, currentPoint.point, visited, frontierSet);

    //If there are no valid neighbors, continue
    if (neighbors.empty()) {
      continue;
    }

    // iterate over the neighs:
    for (auto neighbor : neighbors) {
      //Calculate new cost (So far just add one because every tile costs 1)
      float newCost = costSoFar[currentPoint.point] + 1;

      costSoFar[neighbor] = newCost;
      float priority = newCost + w->heuristic(currentPoint.point);

      // for every neighbor set the cameFrom
      cameFrom[neighbor] = currentPoint.point;
      // enqueue the neighbors to frontier and frontierset
      frontier.push(WeightedPoint2D(neighbor, priority));
      frontierSet.insert(neighbor);
    }

    // do this up to find a visitable border and break the loop
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  if (borderExit != Point2D::INFINITE) {
    vector<Point2D> path;

    auto start = w->getCat();
    auto current = cameFrom[borderExit];

    //Push starting points
    path.push_back(borderExit);
    path.push_back(current);

    while (current != start) {
      path.push_back(cameFrom[current]);
      current = cameFrom[current];
    }
    std::reverse(path.begin(), path.end());

    return path;
  }

  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}
std::vector<Point2D> Agent::getVisitableNeighbors(World* world, Point2D current, unordered_map<Point2D, bool> visited,  unordered_set<Point2D> frontierSet) {
  std::vector<Point2D> neighbors;

  auto east = world->E(current);
  auto west = world->W(current);
  auto northEast = world->NE(current);
  auto northWest = world->NW(current);
  auto southEast = world->SE(current);
  auto southWest = world->SW(current);
  if (isNeighborValid(world, east, visited, frontierSet)) {
    neighbors.push_back(east);
  }
  if (isNeighborValid(world, west, visited, frontierSet)) {
    neighbors.push_back(west);
  }
  if (isNeighborValid(world, northEast, visited, frontierSet)) {
    neighbors.push_back(northEast);
  }
  if (isNeighborValid(world, northWest, visited, frontierSet)) {
    neighbors.push_back(northWest);
  }
  if (isNeighborValid(world, southEast, visited, frontierSet)) {
    neighbors.push_back(southEast);
  }
  if (isNeighborValid(world, southWest, visited, frontierSet)) {
    neighbors.push_back(southWest);
  }

  return neighbors;
}
bool Agent::isNeighborValid(World* w, Point2D current, unordered_map<Point2D, bool> visited, unordered_set<Point2D> frontierSet) {
  //Check if cat
  if (w->getCat() == current) {
    return false;
  }

  //Check if in bounds
  if (!w->isValidPosition(current)) {
    return false;
  }

  if (w->getContent(current)) {
    return false;
  }

  //Check if visited
  if (visited.contains(current)) {
    return false;
  }

  //Check if in queue
  if (frontierSet.contains(current)) {
    return false;
  }

  return true;
}

