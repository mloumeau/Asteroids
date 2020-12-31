//
//  velocity.h
//  myMoonLander
//
//  Created by Scott Burton on 10/22/15.
//  Copyright © 2015 Scott Burton. All rights reserved.
//

#ifndef velocity_h
#define velocity_h

#include "point.h"

class Velocity
{
private:
   float dx;
   float dy;
   float angle = 0;
   float speed = 0;
   
public:
   Velocity()
   {
      dx = 0.0;
      dy = 0.0;
      angle = 0;
   }
   
   Velocity(float dx, float dy)
   {
      this->dx = dx;
      this->dy = dy;
      angle = 0;
      speed = 0;
   }
   
   float getDx() const { return dx; }
   float getDy() const { return dy; }
   float getAngle() const { return angle; }
   
   void setDx(float dx) { this->dx = dx; }
   void setDy(float dy) { this->dy = dy; }
   void setAngle(float angle) { this->angle = angle; }
   
   void add(const Velocity & other);

   void advancePoint(Point & point);
};

#endif /* velocity_h */
