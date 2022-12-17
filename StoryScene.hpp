



#ifndef StoryScene_HPP
#define StoryScene_HPP


#include "Scene.hpp"


class EagleGraphicsContext;
class EagleFont;

class StoryScene : public Scene {
   
protected :
   
   EagleGraphicsContext* window;
   EagleFont* font;
   
public :
   StoryScene();
   
   
   virtual ~StoryScene();
   
   
   bool Init(EagleGraphicsContext* win);

   SCENE_STATUS HandleEvent(EagleEvent ev);
   SCENE_STATUS Update(double dt);
   void Display(EagleGraphicsContext* win);
   

};


#endif // StoryScene_HPP









