



#include "GameScene.hpp"
#include "Randomizer.hpp"
#include "World.hpp"

#include "Eagle/InputHandler.hpp"





Game::Game() :
      Scene(),
      world(0),
      world_num(-1),
      room_num(-1),
      pninja(),
      eninja(),
      cat(),
      ramen(),
      anime(),
      rng()
{
   rng.Seed(0);
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

   pganime = &anime;
   pplayer = &pninja;
   penemy = &eninja;
   pcat = &cat;
   pramen = &ramen;
   prng = &rng;

   success = success && ramen.Init(win);
   success = success && anime.LoadGlobalAnimations(win);

   world = new World();
   success = success && world->Init(win);
   return success;
}



SCENE_STATUS Game::HandleEvent(EagleEvent ev) {

   if (ev.type == EAGLE_EVENT_DISPLAY_CLOSE) {
      return SCENE_COMPLETE;
   }
   if (ev.type == EAGLE_EVENT_KEY_DOWN && ev.keyboard.keycode == EAGLE_KEY_ESCAPE) {
      return SCENE_COMPLETE;
   }
   
   world->HandleEvent(ev);
   pninja.HandleEvent(ev);
   eninja.HandleEvent(ev);
   cat.HandleEvent(ev);
   
   return SCENE_RUNNING;
}



SCENE_STATUS Game::Update(double dt) {

   /// Test for collisiions here, adjust velocities for friction

   /// Update world
   world->Update(dt);

   double pcolordist = DistanceHSL(pninja.ecol , pcurrent_room->room_bg_memory->GetPixel(pninja.phys.x , pninja.phys.y + pplayer->GetAnimationFrame()->H()/2));
   double ecolordist = DistanceHSL(eninja.ecol , pcurrent_room->room_bg_memory->GetPixel(eninja.phys.x , eninja.phys.y + penemy->GetAnimationFrame()->H()/2));

   pninja.phys.vx *= 1.0 - pcolordist;
   pninja.phys.vy *= 1.0 - pcolordist;
   pninja.Update(dt);
   eninja.phys.vx *= 1.0 - ecolordist;
   eninja.phys.vy *= 1.0 - ecolordist;
   eninja.Update(dt);

   double ccolordist = DistanceHSL(cat.ecol , pcurrent_room->room_bg_memory->GetPixel(cat.phys.x , pganime->GetCatAnimation("Walk")->GetFrame(0)->H()/2));

   cat.phys.vx *= 1.0 - ccolordist;
   cat.phys.vy *= 1.0 - ccolordist;
   cat.Update(dt);

   return SCENE_RUNNING;
}



void Game::Display(EagleGraphicsContext* win) {




   world->Display(win);
   
   pninja.Draw(win);
   eninja.Draw(win);
   cat.Draw(win);
   ramen.Draw(win);
   
   
}



void Game::Reset() {
   world->Reset();
}









