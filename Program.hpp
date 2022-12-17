



#ifndef Program_HPP
#define Program_HPP


#include "Scene.hpp"

#include "Eagle/ConfigFile.hpp"



void AllegroLogHandler(const char* text);



class Allegro5System;
class EagleGraphicsContext;
class EagleFont;

class Program {
   
   Allegro5System* sys;
   EagleGraphicsContext* win;
   
   GraphicsConfig config;

   Scene* scenes[NUM_SCENES];
   int active_scene;
   
   bool fullscreen;
   bool redraw;
   bool quit;

   EagleFont* verdana240;
   EagleFont* verdana120;
   EagleFont* verdana80;
   EagleFont* verdana40;
   EagleFont* verdana20;
public :
   
   Program();
   
   bool Init();
   int Run();
};

#endif // NewProgram_HPP
