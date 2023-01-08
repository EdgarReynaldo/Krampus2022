



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
      pstate("Stand"),
      estate("Stand"),
      cstate("Stand"),
      anime()
{}



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
   pganime = &anime;
   pplayer = &pninja;
   penemy = &eninja;
   success = success && anime.LoadGlobalAnimations(win);
   success = success && world->SetWorldAndRoom(0 , 0);
   return success;
}



SCENE_STATUS Game::HandleEvent(EagleEvent ev) {
   return world->HandleEvent(ev);
}



SCENE_STATUS Game::Update(double dt) {
   return world->Update(dt);
}



void Game::Display(EagleGraphicsContext* win) {
   world->Display(win);
}



void Game::Reset() {
   world->Reset();
}









