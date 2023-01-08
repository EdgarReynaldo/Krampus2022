



#ifndef CATS_HPP
#define CATS_HPP
#include "Physics.hpp"

#include "Objects.hpp"



class Cat : public Object {
public :
   Cat();
   bool found_ramen;


//   virtual void HandleEvent(EagleEvent e);
//   virtual void Update(double dt);
   virtual void Draw(EagleGraphicsContext* win);
};



#endif // CATS_HPP
