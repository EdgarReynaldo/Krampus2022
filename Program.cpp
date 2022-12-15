



#include "Scene.hpp"
#include "IntroScene.hpp"
#include "Program.hpp"



#include "Eagle/GraphicsContext.hpp"
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
   win = config.SetupWindow(sys);
   fullscreen = win->Fullscreen();
   scenes[0] = new IntroScene();
   active_scene = 0;
   scenes[active_scene]->Init(win);
   return win;
}



int Program::Run() {
   sys->GetSystemTimer()->Start();
   int ret = 0;
   
   while (!quit) {
      if (redraw = scenes[active_scene]->Redraw()) {
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
            quit = true;
         }
         if (ev.type == EAGLE_EVENT_TIMER) {
            scenes[active_scene]->Update(ev.timer.eagle_timer_source->SPT());
         }
         ret = scenes[active_scene]->HandleEvent(ev);
         if (ret == SCENE_COMPLETE) {
            quit = true;
         }
      } while (!sys->UpToDate());
   }
   
   return 0;
}
