



#include "Ninja.hpp"
#include "GlobalAnimations.hpp"


#include "Eagle/Events.hpp"
#include "Eagle/InputHandler.hpp"
#include "Eagle/Image.hpp"



PlayerNinja* pplayer = 0;
EnemyNinja* penemy = 0;


double ShurikenSpeed(COLOR c) {
   const double speeds[NUMCOLORS] = {
      50.0,75.0,100.0,125.0,150.0,175.0,200.0,225.0,250.0,300.0
   };
   return speeds[c];
}



/// ----------------     Shuriken      -------------------


Shuriken::Shuriken(Physics p , COLOR c) :
      AnimationBase(),
      Object(p,c)
{
   Init(3 , 1 , 0.25 , ANIMATION_REPEAT_FORWARDS);
}



void Shuriken::HandleEvent(EagleEvent e) {
   (void)e;
}



void Shuriken::Update(double dt) {
   this->phys = this->phys.FuturePhysics(dt);
}



void Shuriken::Draw(EagleGraphicsContext* win) {
   EAGLE_ASSERT(pganime);
   BitmapAnimation* ban = dynamic_cast<BitmapAnimation*>(pganime->GetNinjaAnimation("Shuriken"));
   int flag = (phys.vx < 0)?DRAW_HFLIP:DRAW_NORMAL;
   win->Draw(ban->GetFrame(GetFrameNum()) , phys.x , phys.y , HALIGN_CENTER , VALIGN_CENTER , pplayer->GetEagleColor() , flag);
}



/// --------------------      Ninja     ----------------------------



Ninja::Ninja() :
      Object(Physics() , GRAY),
      player(false),
      faceleft(false),
      midair(false),
      health(-1),
      lives_left(-1),
      catlives(GRAY),
      nshuriken(-1),
      shuriken(),
      current_animation(),
      astate("Stand")
{}



Ninja::~Ninja()
{}



void Ninja::HandleEvent(EagleEvent e) {
   (void)e;
}



void Ninja::Update(double dt) {
   for (std::deque<Shuriken>::iterator it = shuriken.begin() ; it != shuriken.end() ; ++it) {
      (*it).Update(dt);
   }
   phys = phys.FuturePhysics(dt);
   current_animation.AdvanceAnimationTime(dt);
}



void Ninja::Draw(EagleGraphicsContext* win) {
   BitmapAnimation* anime = dynamic_cast<BitmapAnimation*>(pganime->GetNinjaAnimation(astate));
   int flag = faceleft?DRAW_HFLIP:DRAW_NORMAL;
   EagleColor c = GetEagleColor();
   win->Draw(anime->GetFrame(current_animation.GetFrameNum()) , phys.x , phys.y , HALIGN_CENTER , VALIGN_CENTER , c , flag);
   for (std::deque<Shuriken>::iterator it = shuriken.begin() ; it != shuriken.end() ; ++it) {
      it->Draw(win);
   }
}



void Ninja::LaunchShuriken() {
   if (nshuriken != 0) {
      if (nshuriken > 0) {--nshuriken;}
      Physics p;
      p.x = this->phys.x;
      p.y = this->phys.y;
      p.vx = faceleft?-ShurikenSpeed(this->color):ShurikenSpeed(this->color);
      shuriken.push_front(Shuriken(p , this->color));
   }
}



void Ninja::SetAnimationState(std::string state , int frame_num) {
   astate = state;
   current_animation = *(pganime->GetNinjaAnimation(astate));
   current_animation.SetAnimationTime(0.0);
   while (frame_num > 0) {
      current_animation.AdvanceFrame();
      --frame_num;
   }
}



int Ninja::GetAnimationFrameNum() {
   return current_animation.GetFrameNum();
}



EagleImage* Ninja::GetAnimationFrame() {
   BitmapAnimation* nanime = dynamic_cast<BitmapAnimation*>(pganime->GetNinjaAnimation(astate));
   return nanime->GetFrame(GetAnimationFrameNum());
}



/// --------------------      Player Ninja     ----------------------------



void PlayerNinja::HandleEvent(EagleEvent e) {
   if (e.type == EAGLE_EVENT_KEY_DOWN) {
      if (e.keyboard.keycode == EAGLE_KEY_SPACE) {
         LaunchShuriken();
      }
   }
}



void PlayerNinja::Update(double dt) {
   Ninja::Update(dt);
}




/// --------------------      Enemy Ninja     ----------------------------



void EnemyNinja::HandleEvent(EagleEvent e) {
   (void)e;
}



void EnemyNinja::Update(double dt) {
   Ninja::Update(dt);
}











