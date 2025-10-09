#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"

class Catcher : public Agent {
public:
  explicit Catcher() : Agent(){};
  Point2D Move(World*) override;

  //The distance threshold where the catcher
  //starts to block the border instead of the midway point
  int mBorderThreshold = 3;
};

#endif  // CATCHER_H
