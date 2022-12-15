



#include "Scene.hpp"



Scene::Scene() : 
      redraw(true),
      quit(false),
      complete(false),
      status(SCENE_NOTREADY)
{}



bool Scene::Redraw() {
   return redraw;
}



bool Scene::Quit() {
   return quit;
}



bool Scene::Complete() {
   return complete;
}



SCENE_STATUS Scene::Status() {
   return status;
}
