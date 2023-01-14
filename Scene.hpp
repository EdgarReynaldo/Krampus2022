


#ifndef Scene_HPP
#define Scene_HPP


#include "Eagle/Events.hpp"
#include "Eagle/AnimationBase.hpp"

class EagleGraphicsContext;


enum SCENE_STATUS {
   SCENE_NOTREADY = 0,
   SCENE_READY    = 1,
   SCENE_RUNNING  = 2,
   SCENE_COMPLETE = 4,
   SCENE_ERROR    = 8
};


#define NUM_SCENES 3

class Scene : public AnimationBase {

protected :
   bool redraw;
   bool quit;
   bool complete;
   SCENE_STATUS status;

   void OnComplete() {complete = true;}
   
public :
   Scene();

   virtual ~Scene() {}
   
   virtual bool Init(EagleGraphicsContext* win)=0;
   
   virtual SCENE_STATUS HandleEvent(EagleEvent ev)=0;
   virtual SCENE_STATUS Update(double dt)=0;
   virtual void Display(EagleGraphicsContext* win)=0;
   
   bool Redraw();
   bool Quit();
   bool Complete();
   SCENE_STATUS Status();

   virtual void Reset();

};







#endif // Scene_HPP

