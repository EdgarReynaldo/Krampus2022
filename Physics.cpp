



#include "Physics.hpp"





Physics::Physics() :
      x(0.0),
      y(0.0),
      vx(0.0),
      vy(0.0),
      ax(0.0),
      ay(0.0),
      bcirc(0,0,10),
      brect(-2,-2,4,4),
      icirc(0,0,3),
      irect(-1,-1,2,2),
      itri(0,0,1,0,0,1)
{
   
}



Physics Physics::FuturePhysics(double dt) const {
   Physics p = *this;
   p.x += vx*dt + ax*dt*dt/2.0;
   p.y += vy*dt + ay*dt*dt/2.0;
   p.vx += p.ax*dt;
   p.vy += p.ay*dt;
   return p;
}



STRIKE Overlaps(const Physics& p1 , const Physics& p2) {
   const double dx = p2.x - p1.x;
   const double dy = p2.y - p1.y;
   const double dsq = dx*dx + dy*dy;
   const double r = p1.bcirc.R() + p2.bcirc.R();
   const double rsq = r*r;
   const double r2 = p1.icirc.R() + p2.icirc.R();
   const double rsq2 = r2*r2;
   if (dsq <= rsq) {
      if (dsq <= rsq2) {
      /// Inside inner circle, possible hit
         Rectangle ra = p1.irect;
         ra.MoveBy(p1.x,p1.y);
         Rectangle rb = p2.irect;
         rb.MoveBy(p2.x,p2.y);
         if (Overlaps(ra,rb)) {
            Triangle ta = p1.itri;
            ta.MoveBy(p1.x,p1.y);
            Triangle tb = p2.itri;
            tb.MoveBy(p2.x,p2.y);
            if (Overlaps(ta,tb)) {
               return PERFECT;
            }
            return BULLSEYE;
         }
         
         
         /// Inside inner circle, hit
         return CRITICAL;
      }
      else {
         /// Outside inner circle, may be in bounding rectangle
         Rectangle ra = p1.brect;
         ra.MoveBy(p1.x,p1.y);
         Rectangle rb = p2.brect;
         rb.MoveBy(p2.x,p2.y);
         if (Overlaps(ra , rb)) {
            return HIT;
         }
         else {
            return GRAZE;
         }
      }
   }
   /// Outside bounding circle
   return MISS;
}
