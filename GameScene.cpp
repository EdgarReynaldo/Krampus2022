



#include "GameScene.hpp"

#include "World.hpp"



Game::Game() :
      Scene(),
      world(0),
      world_num(-1),
      room_num(-1),
      pninja(),
      eninja(),
      cat(),
      anime()
{
   
}



Game::~Game()
{
   Free();
}



void Game::Free() {
   if (world) {
      delete world;
      world = 0;
   }
   anime.Free();
}



bool Game::Init(EagleGraphicsContext* win) {
   Free();
   bool success = true;
   world = new World();
   success = success && world->Init(win);
   pganime = &anime;
   pplayer = &pninja;
   penemy = &eninja;
   success = success && anime.LoadGlobalAnimations(win);
   success = success && world->SetWorldAndRoom(0 , 0);
   return success;
}



SCENE_STATUS Game::HandleEvent(EagleEvent ev) {

   if (ev.type == EAGLE_EVENT_DISPLAY_CLOSE) {
      return SCENE_COMPLETE;
   }

   world->HandleEvent(ev);
   pninja.HandleEvent(ev);
   eninja.HandleEvent(ev);
   cat.HandleEvent(ev);
   
   return SCENE_RUNNING;
}



SCENE_STATUS Game::Update(double dt) {
   world->Update(dt);
   pninja.Update(dt);
   eninja.Update(dt);
   cat.Update(dt);
   return SCENE_RUNNING;
}



void Game::Display(EagleGraphicsContext* win) {
   world->Display(win);
   
   win->Draw(pninja.GetAnimationFrame() , pninja.phys.x , pninja.phys.y , HALIGN_CENTER , VALIGN_CENTER , pninja.GetEagleColor() , pninja.faceleft?DRAW_HFLIP:DRAW_NORMAL);
   win->Draw(eninja.GetAnimationFrame() , eninja.phys.x , eninja.phys.y , HALIGN_CENTER , VALIGN_CENTER , eninja.GetEagleColor() , eninja.faceleft?DRAW_HFLIP:DRAW_NORMAL);
   
}



void Game::Reset() {
   world->Reset();
}









