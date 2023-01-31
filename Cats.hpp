



#ifndef CATS_HPP
#define CATS_HPP



#include "Eagle/AnimationBase.hpp"


#include "Objects.hpp"


double CatSpeed(COLOR c);

class Cat : public AnimationBase , public Object {
protected :
   bool faceleft;
   bool midair;
   std::string state;/// "Stand" | "Walk" | "Jump"
   
   
public :
   Cat();
   
   virtual void HandleEvent(EagleEvent e);
   virtual void Update(double dt);
   virtual void Draw(EagleGraphicsContext* win);
   
};






extern Cat* pcat;





#endif // CATS_HPP



