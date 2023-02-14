



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
      rng(),
      pcolordist(1.0),
      ecolordist(1.0),
      ccolordist(1.0)
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
   cat.color = WHITE;
   cat.ecol = GetColorByEnum(WHITE);
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
   if (ev.type == EAGLE_EVENT_ANIMATION_COMPLETE) {
      if (ev.animation.source == &(pninja.current_animation)) {
         pninja.SetAnimationState("Stand" , 0);
         pninja.current_animation.ResetAnimation();
      }
      else if (ev.animation.source == &(eninja.current_animation)) {
         eninja.SetAnimationState("Stand" , 0);
         eninja.current_animation.ResetAnimation();
      }
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
/// HEY DUMMY THESE PIXELS AREN"T ON THE BITMAP
   double pcolordist = 1.0 - DistanceRGBA(pninja.ecol , pcurrent_room->room_bg_memory->GetPixel(pninja.phys.x , pninja.phys.y + pplayer->GetAnimationFrame()->H()/2));
   double ecolordist = 1.0 - DistanceRGBA(eninja.ecol , pcurrent_room->room_bg_memory->GetPixel(eninja.phys.x , eninja.phys.y + penemy->GetAnimationFrame()->H()/2));

   if (pcolordist < 0.5) {
      pninja.phys.tr = 0.0;
      pninja.phys.ay = 10.0;
   }
   else {
      pninja.phys.tr = 1.0;
      pninja.phys.ay = 0.0;
   }
   pninja.phys.vx *= pninja.phys.tr;
   pninja.phys.vy *= pninja.phys.tr;

   if (ecolordist < 0.5) {
      eninja.phys.tr = 0.0;
      eninja.phys.ay = 10.0;
   }
   else {
      eninja.phys.tr = 1.0;
      eninja.phys.ay = 0.0;
   }
   eninja.phys.vx *= eninja.phys.tr;
   eninja.phys.vy *= eninja.phys.tr;
   
   for (std::deque<Shuriken>::iterator it = eninja.shuriken.begin() ; it != eninja.shuriken.end() ; ++it) {
      STRIKE st = Collides(pninja , *it , dt);
      if (st > GRAZE) {
         pninja.SetAnimationState("Knockback" , 0);
      }
   }

   for (std::deque<Shuriken>::iterator it = pninja.shuriken.begin() ; it != pninja.shuriken.end() ; ++it) {
      STRIKE st = Collides(eninja , *it , dt);
      if (st > GRAZE) {
         eninja.SetAnimationState("Knockback" , 0);
      }
   }
   eninja.Update(dt);
   pninja.Update(dt);
   AdjustPhysicsForWorld(pninja.phys , pcurrent_room->area);
   AdjustPhysicsForWorld(eninja.phys , pcurrent_room->area);

   double ccolordist = 1.0 - DistanceRGBA(cat.ecol , pcurrent_room->room_bg_memory->GetPixel(cat.phys.x , cat.phys.y + pganime->GetCatAnimation("Walk")->GetFrame(0)->H()/2));

   if (ccolordist < 0.3) {
      cat.phys.tr = 0.0;
      cat.phys.ay = 10.0;
   }
   else {
      cat.phys.tr = 1.0;
      cat.phys.ay = 0.0;
   }
   cat.phys.vx *= cat.phys.tr;
   cat.phys.vy *= cat.phys.tr;
   cat.Update(dt);
   AdjustPhysicsForWorld(cat.phys , pcurrent_room->area);

   return SCENE_RUNNING;
}



void Game::Display(EagleGraphicsContext* win) {


   Transform t = win->GetTransformer()->CreateTransform();
   t.Translate(-pninja.phys.x , -pninja.phys.y);
   t.Translate(win->Width()/2.0 , win->Height()/2.0);
   win->PushViewTransform(t);
   
   world->Display(win);
   win->DrawRectangle(Rectangle(-5,-5,pcurrent_room->room_bg->W() + 10 , pcurrent_room->room_bg->H() + 10) , 10.0 , EagleColor(255,255,255));
   
   ramen.Draw(win);
   cat.Draw(win);
   pninja.Draw(win);
   eninja.Draw(win);
   pninja.DrawShuriken(win);
   eninja.DrawShuriken(win);
   
   win->PopViewTransform();
}



void Game::Reset() {
   world->Reset();
}









