



#ifndef Animation_HPP
#define Animation_HPP

#include "Eagle/AnimationBase.hpp"
#include "Eagle/GraphicsContext.hpp"
#include "Eagle/Image.hpp"



typedef std::map<std::string , AnimationBase*> ANIMATIONMAP;
typedef ANIMATIONMAP::iterator AMIT;



class BitmapAnimation : public AnimationBase {
protected :
   EagleGraphicsContext* win;
   std::vector<EagleImage*> frames;
public :
   
   BitmapAnimation();
   virtual void Free();
   bool Load(EagleGraphicsContext* window , std::string basename , std::string ext , int nframes);
   
   EagleImage* GetFrame();
   EagleImage* GetFrame(unsigned int n);
};


class AnimationMap {
protected :
  ANIMATIONMAP amap;
public :
   
   void SetAnimeRef(std::string name , AnimationBase* anime);
   AnimationBase* GetAnime(std::string name);
};


#endif // Animation_HPP
