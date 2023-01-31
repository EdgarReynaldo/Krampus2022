



#include "MathStuff.hpp"

#include <cmath>


int RadTo8Way(double radians) {
   while (radians < M_PI/8.0) {
      radians += 2.0*M_PI;
   }
   return int(((radians + M_PI/8.0)/(2.0*M_PI))*8.0)%8;
}
