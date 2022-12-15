



#ifndef IntroScene_HPP
#define IntroScene_HPP


#include "Scene.hpp"

class EagleGraphicsContext;
class EagleImage;
class EagleFont;


#define SAMURAI_NFRAMES 22

class IntroScene : public Scene {
   
   EagleGraphicsContext* window;
   EagleImage* krampus_splash;
   EagleImage* samurai_gif[SAMURAI_NFRAMES];
   
   EagleFont* splash_font;
   
public :
   IntroScene();

   virtual ~IntroScene();
   void Free();
   
   virtual bool Init(EagleGraphicsContext* win);
   virtual void Reset();
   
   virtual SCENE_STATUS HandleEvent(EagleEvent ev);
   virtual SCENE_STATUS Update(double dt);
   virtual void Display(EagleGraphicsContext* win);

};
   
   
   
   
#endif // IntroScene_HPP
