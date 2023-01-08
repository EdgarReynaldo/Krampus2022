



#include "Cats.hpp"




Cat::Cat() :
      Object(Physics() , NONE),
      found_ramen(false)
{}



void Cat::Draw(EagleGraphicsContext* win) {
   (void)win;
}
