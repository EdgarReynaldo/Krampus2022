



#ifndef Color_HPP
#define Color_HPP


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

#include "Eagle/Color.hpp"

EagleColor GetColorByEnum(COLOR c);

class EagleGraphicsContext;
class EagleImage;



class CollisionMap {
   
protected :
   EagleGraphicsContext* window;
   EagleImage* cimage;
   EagleImage* caverage;
   
public :
   CollisionMap();
   ~CollisionMap() {Free();}
   
   void Free();
   bool Init(EagleGraphicsContext* win , EagleImage* image);

   EagleImage* CreateAverageColor();

   EagleColor AvePixColor9(int x , int y);
   EagleColor FastPix9(int x , int y);
};

double DistanceRGBA(EagleColor c1 , EagleColor c2);

double DistanceHSL(EagleColor c1 , EagleColor c2);/// 0.0,1.0


#endif // Color_HPP





