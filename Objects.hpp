



#ifndef Objects_HPP
#define Objects_HPP

#include "Physics.hpp"
#include "CollisionMap.hpp"

#include "Eagle/Events.hpp"



class EagleGraphicsContext;

class Object {
public :
   Physics phys;
   COLOR color;   
   EagleColor ecol;
   
   Object(Physics p , COLOR c);
   virtual ~Object() {}
   
   virtual void HandleEvent(EagleEvent e) {(void)e;}
   virtual void Update(double dt) {(void)dt;}
   virtual void Draw(EagleGraphicsContext* win)=0;

   COLOR GetColor() {return color;}
   EagleColor GetEagleColor() {return ecol;}
};



STRIKE Collides(const Object& o1 , const Object& o2 , double dt);



#endif // Objects_HPP






