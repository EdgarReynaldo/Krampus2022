



#ifndef Ramen_HPP
#define Ramen_HPP



#include "Objects.hpp"


class EagleImage;
class EagleGraphicsContext;



class Ramen : public Object {

protected :
   EagleGraphicsContext* window;
   EagleImage* ramen_pic;
   Object* owner;
   
   
public :
   
   Ramen();
   
   
   void Free();
   
   bool Init(EagleGraphicsContext* win);
   virtual void Draw(EagleGraphicsContext* win);
   
   EagleImage* RamenPic() {return ramen_pic;}
   
};


extern Ramen* pramen;



#endif // Ramen_HPP
