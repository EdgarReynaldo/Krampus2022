



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



double NinjaSpeed(COLOR c) {
   const double speeds[NUMCOLORS] = {
      240.0,180.0,240.0,300.0,360.0,420.0,480.0,540.0,600.0,720.0
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
   AdvanceAnimationTime(dt);
}



void Shuriken::Draw(EagleGraphicsContext* win) {
   EAGLE_ASSERT(pganime);
   BitmapAnimation* ban = dynamic_cast<BitmapAnimation*>(pganime->GetNinjaAnimation("Shuriken"));
   int flag = (phys.vx < 0)?DRAW_HFLIP:DRAW_NORMAL;
   win->Draw(ban->GetFrame(GetFrameNum()) , phys.x , phys.y , HALIGN_CENTER , VALIGN_CENTER , ecol , flag);
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
      p.x = phys.x;
      p.y = phys.y;
      p.vx = (phys.vx>0)?(ShurikenSpeed(color) + phys.vx):((phys.vx < 0)?(-ShurikenSpeed(color) + phys.vx):0);
      p.vy = (phys.vy>0)?(ShurikenSpeed(color) + phys.vy):((phys.vy < 0)?(ShurikenSpeed(color) + phys.vy):0);
      if (fabs(p.vx) > 0 || fabs(p.vy) > 0) {
         shuriken.push_front(Shuriken(p , color));
      }
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
      if (e.keyboard.keycode == EAGLE_KEY_S) {
         LaunchShuriken();
      }
   }
   if (e.type == EAGLE_EVENT_TIMER) {
      
      if (keydown[EAGLE_KEY_LEFT]) {
         faceleft = true;
         phys.vx = -NinjaSpeed(color);
      }
      else if (keydown[EAGLE_KEY_RIGHT]) {
         faceleft = false;
         phys.vx = NinjaSpeed(color);;
      }
      else {
         phys.vx = 0.0;
      }

      if (keydown[EAGLE_KEY_UP]) {
         phys.vy = -NinjaSpeed(color);
      }
      else if (keydown[EAGLE_KEY_DOWN]) {
         phys.vy = NinjaSpeed(color);
      }
      else {
         phys.vy = 0.0;
      }
   }
}



void PlayerNinja::Update(double dt) {
   Ninja::Update(dt);
}




/// --------------------      Enemy Ninja     ----------------------------



void EnemyNinja::HandleEvent(EagleEvent e) {
   (void)e;
   
   if (e.type == EAGLE_EVENT_TIMER) {
      Physics p1 = phys;
      Physics p2 = pplayer->phys;
      double dx = p2.x - p1.x;
      double dy = p2.y - p1.y;

      double dsq = dx*dx + dy*dy;
      if (dsq >= 160000) {


         /// Head randomly towards the player in a blind linear fashion
         double arad = atan2(dy,dx);
         int octant = (int)((arad/(2.0*M_PI))*8 + 8)%8;
         bool left = octant > 2 && octant < 6;
         bool up = octant >= 1 && octant <= 3;
         bool down = octant >= 5 && octant <= 7;
         bool right = octant < 2 || octant > 6;
         
         if (left) {
            phys.vx = -NinjaSpeed(color);
         }
         else if (right) {
            phys.vx = NinjaSpeed(color);
         }
         else {
            phys.vx = 0;
         }
         if (up) {
            phys.vy = NinjaSpeed(color);
         }
         else if (down) {
            phys.vy = -NinjaSpeed(color);
         }
         else {
            phys.vy = 0;
         }
      }
      else {
         phys.vx = 0;
         phys.vy = 0;
      }
   }
   
}



void EnemyNinja::Update(double dt) {
   Ninja::Update(dt);
}











