



#include "Scene.hpp"
#include "IntroScene.hpp"
#include "StoryScene.hpp"
#include "Program.hpp"
#include "GameScene.hpp"


#include "Eagle/GraphicsContext.hpp"
#include "Eagle/Font.hpp"
#include "Eagle/backends/Allegro5Backend.hpp"



Program::Program() :
      sys(0),
      win(0),
      config(),
      scenes(),
      active_scene(-1),
      fullscreen(false),
      redraw(true),
      quit(false)
{
   
}



bool Program::Init() {
   sys = GetAllegro5System();
   config.Setup("Eagle.cfg");
   bool success = (win = config.SetupWindow(sys));
   success = success && win->Valid();
   fullscreen = win->Fullscreen();
   scenes[0] = new IntroScene();
   scenes[1] = new StoryScene();
   scenes[2] = new Game();
   success = success && scenes[0]->Init(win);
   success = success && scenes[1]->Init(win);
   success = success && scenes[2]->Init(win);
   active_scene = 2;
   success = success && (verdana240 = win->GetFont("Data/Fonts/Verdana.ttf" , 240));
   success = success && (verdana120 = win->GetFont("Data/Fonts/Verdana.ttf" , 120));
   success = success && (verdana80 = win->GetFont("Data/Fonts/Verdana.ttf" , 80));
   success = success && (verdana40 = win->GetFont("Data/Fonts/Verdana.ttf" , 40));
   success = success && (verdana20 = win->GetFont("Data/Fonts/Verdana.ttf" , 20));
   return success;
}



int Program::Run() {
   sys->GetSystemTimer()->Start();
   int ret = 0;
   
   while (!quit) {
      if ((redraw = scenes[active_scene]->Redraw())) {
         win->Clear();
         scenes[active_scene]->Display(win);
         win->FlipDisplay();
         redraw = false;
      }
      do {
         EagleEvent ev = sys->WaitForSystemEventAndUpdateState();
         if (ev.type == EAGLE_EVENT_DISPLAY_CLOSE) {
            quit = true;
         }
         if (ev.type == EAGLE_EVENT_KEY_DOWN && ev.keyboard.keycode == EAGLE_KEY_ESCAPE) {
//            quit = true;
         }
         if (ev.type == EAGLE_EVENT_TIMER) {
            scenes[active_scene]->Update(ev.timer.eagle_timer_source->SPT());
         }
         ret = scenes[active_scene]->HandleEvent(ev);
         if (ret == SCENE_COMPLETE) {
            if (active_scene + 1 == NUM_SCENES) {quit = true;}
            active_scene = (active_scene + 1)%NUM_SCENES;
         }
      } while (!sys->UpToDate());
   }
   
   return 0;
}
