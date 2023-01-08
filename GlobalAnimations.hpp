



#ifndef GlobalAnimations_HPP
#define GlobalAnimations_HPP


#include "Animation.hpp"

/**
class SpriteSheetAnimation : public AnimationBase {

   EagleGraphicsContext* window;
protected :
   EagleImage* sheet;
   std::string name;
   std::vector<EagleImage*> subsheet;
public :
   SpriteSheetAnimation();
   ~SpriteSheetAnimation();

   void Free();

   
   
   void Update(double dt)
   EagleImage* CurrentFrame();

   bool SetupSpriteSheet(EagleImage* spritesheet , std::string spritename);



};
*/




class EagleGraphicsContext;

class GlobalAnimations {
   
   EagleGraphicsContext* window;
public :
   BitmapAnimation shuriken;

   BitmapAnimation nstand;
   BitmapAnimation nknockback;
   BitmapAnimation ndie;
   
   BitmapAnimation ncrouch;
   BitmapAnimation nstab;
   BitmapAnimation nspring;
   BitmapAnimation ndodge;
   
   BitmapAnimation nslash;
   BitmapAnimation nspin;
   BitmapAnimation nrun;
/**
   EagleImage* cat_walking;
   EagleImage* cat_jumping;

   SpriteSheetAnimation catwalk;
   SpriteSheetAnimation catjump;


   ANIMATIONMAP catmap;
*/
   ANIMATIONMAP ninjamap;

   bool LoadGlobalAnimations(EagleGraphicsContext* win);

   GlobalAnimations();

public :
   
   ~GlobalAnimations();

   void Free();

   AnimationBase* GetNinjaAnimation(std::string nstate);

   friend class Game;
};

extern GlobalAnimations* pganime;




#endif // GlobalAnimations_HPP





