#include "Agent.h"

#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

///<summary>
/// Generates a path from the cat's current position to a border using the A* algorithm
///</summary>
///<returns> A vector of points leading to the closest border </returns>
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;
  unordered_map<Point2D, float> costSoFar;
  priority_queue<WeightedPoint2D, vector<WeightedPoint2D>, greater<WeightedPoint2D>> frontier;
  unordered_set<Point2D> frontierSet;
  unordered_map<Point2D, bool> visited;

  //Initialization
  WeightedPoint2D catPos = WeightedPoint2D(w->getCat(), 1);
  frontier.push(catPos);
  costSoFar[catPos.point] = 0;
  frontierSet.insert(catPos.point);
  Point2D borderExit = Point2D::INFINITE;

  while (!frontier.empty()) {
    //Get the highest priority point from frontier
    auto currentPoint = frontier.top();
    frontier.pop();
    visited[currentPoint.point] = true;

    //If algorithm hits border, set border exit
    if (w->catWinsOnSpace(currentPoint.point)) {
      borderExit = currentPoint.point;
      break;
    }

    //Get all visitable neighbors
    auto neighbors = getVisitableNeighbors(w, currentPoint.point, visited, frontierSet);

    //If there are no valid neighbors, continue
    if (neighbors.empty()) {
      continue;
    }

    //Add visitable neighbors to frontier and calculate cost
    for (auto neighbor : neighbors) {
      //Calculate new cost (So far just add one because every tile costs 1)
      float newCost = costSoFar[currentPoint.point] + 1;

      //Check if the new cost is less expensive than the old cost
      if (!frontierSet.contains(neighbor) || costSoFar[neighbor] > newCost)
      {
        costSoFar[neighbor] = newCost;

        //Calculate priority
        float priority = newCost + w->heuristic(neighbor);
        cameFrom[neighbor] = currentPoint.point;

        //Add to frontier w/ priority
        frontier.push(WeightedPoint2D(neighbor, priority));
        frontierSet.insert(neighbor);
      }
    }
  }
  //If there is an exit, calculate path
  if (borderExit != Point2D::INFINITE) {
    vector<Point2D> path;

    auto start = w->getCat();
    auto current = borderExit;

    while (current != start) {
      path.push_back(current);
      current = cameFrom[current];
    }
    std::reverse(path.begin(), path.end());

    return path;
  }
  //No exit found
  return vector<Point2D>();
}

#pragma region Neighbor Functions
///<summary>
/// Checks which neighbors to the passed through point are visitable
///</summary>
///<returns> A vector of neighbors which are visitable </returns>
std::vector<Point2D> Agent::getVisitableNeighbors(World* world, Point2D current, const std::unordered_map<Point2D, bool>& visited, const std::unordered_set<Point2D>& frontierSet) {
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

///<summary>
/// Checks if a certain neighbor is a valid position
///</summary>
/// <remarks> A valid position needs: To not be the cat's position,
/// to be inside the grid, to not be blocked,
/// to not have been visited,
/// to not be in frontier</remarks>
///<returns> true if the neighbor meets all requirements to be valid </returns>
bool Agent::isNeighborValid(World* w, Point2D current, const std::unordered_map<Point2D, bool>& visited, const std::unordered_set<Point2D>& frontierSet) {
  //Check if cat
  if (w->getCat() == current) {
    return false;
  }

  //Check if in bounds
  if (!w->isValidPosition(current)) {
    return false;
  }

  //Check if blocked
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
#pragma endregion
