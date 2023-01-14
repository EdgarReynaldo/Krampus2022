



#include "Objects.hpp"



EagleColor GetColorByEnum(COLOR c) {
   const EagleColor carray[NUMCOLORS] = {
      EagleColor(127,127,127,255),
      EagleColor(255,255,255,255),
      EagleColor(255,  0,  0,255),
      EagleColor(255,127,  0,255),
      EagleColor(255,255,  0,255),
      EagleColor(  0,255,  0,255),
      EagleColor(  0,255,255,255),
      EagleColor(  0,  0,255,255),
      EagleColor(127,  0,255,255),
      EagleColor(  0,  0,  0, 64)
   };
   return carray[c];
}




STRIKE Collides(const Object& o1 , const Object& o2 , double dt) {
   STRIKE s = Overlaps(o1.phys.FuturePhysics(dt) , o2.phys.FuturePhysics(dt));
   return s;
}



Object::Object(Physics p , COLOR c) :
      phys(p),
      color(c),
      ecol()
{
   ecol = GetColorByEnum(c);
}
