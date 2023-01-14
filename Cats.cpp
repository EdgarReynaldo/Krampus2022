



#include "Cats.hpp"




Cat::Cat() :
      Object(Physics() , GRAY),
      found_ramen(false)
{}



void Cat::Draw(EagleGraphicsContext* win) {
   (void)win;
}
