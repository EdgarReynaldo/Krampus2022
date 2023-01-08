



#ifndef Physics_HPP
#define Physics_HPP

#include "Eagle/Area.hpp"







enum STRIKE {
   MISS     = 0,/// Outside bounding circle
   GRAZE    = 1,/// Inside bounding circle , outside bounding rectangle
   HIT      = 2,/// Inside bounding rectangle, outside inner circle
   CRITICAL = 4,/// Inside inner circle, outside inner rectangle
   BULLSEYE = 8,/// Inside inner rectangle, outside inner triangle
   PERFECT  = 16/// Inside inner triangle
};



class Physics {
public :
   double x,y;
   double vx,vy;
   double ax,ay;
   Circle    bcirc;/// Bounding circle
   Rectangle brect;/// Bounding rectangle
   Circle    icirc;/// Inner circle
   Rectangle irect;/// Inner rectangle
   Triangle  itri; /// Inner triangle
   
   Physics();
   
   
   Physics FuturePhysics(double dt) const;
   
   
};


STRIKE Overlaps(const Physics& p1 , const Physics& p2);






#endif // Physics_HPP





