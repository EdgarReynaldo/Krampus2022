



#ifndef Objects_HPP
#define Objects_HPP


/**! @enum CATCOLOR
     @brief Flags for indicating which abilities a cat has
*/

enum COLOR {
   GRAY     = 0,
   WHITE    = 1,
   RED      = 2,
   ORANGE   = 4,
   YELLOW   = 8,
   GREEN    = 16,
   CYAN     = 32,
   BLUE     = 64,
   PURPLE   = 128,
   BLACK    = 256,
   NUMCOLORS = 10
};

#include "Eagle/Events.hpp"

#include "Eagle/Color.hpp"

EagleColor GetColorByEnum(COLOR c);

#include "Physics.hpp"



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






