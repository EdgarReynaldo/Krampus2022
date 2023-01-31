



#include "Objects.hpp"



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
