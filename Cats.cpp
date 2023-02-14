



#include "Cats.hpp"
#include "GlobalAnimations.hpp"
#include "Ninja.hpp"
#include "Ramen.hpp"
#include "MathStuff.hpp"



Cat* pcat = 0;



double CatSpeed(COLOR c) {
   const double speeds[NUMCOLORS] = {
      360.0,240.0,360.0,420.0,480.0,540.0,600.0,720.0,900.0
   };
   return speeds[c];
}



Cat::Cat() :
      AnimationBase(),
      Object(Physics() , GRAY),
      faceleft(false),
      state("Walk")
{
   Init(8 , 1 , 0.75 , ANIMATION_REPEAT_FORWARDS);
}



void Cat::HandleEvent(EagleEvent e) {
   
   if (e.type == EAGLE_EVENT_TIMER) {
      /// Move kitty here
      Physics p1 = phys;
      
      /// Run away from ninjas
      Physics p2 = pplayer->phys;
      Physics p3 = penemy->phys;
      
      /// Run towards ramen
      Physics p4 = pramen->phys;
      
      double dx2 = p1.x - p2.x;
      double dx3 = p1.x - p3.x;
      double dx4 = p4.x - p1.x;
      
      double dy2 = p1.y - p2.y;
      double dy3 = p1.y - p3.y;
      double dy4 = p4.y - p1.y;
      
      double dir = atan2((dy2 + dy3 + dy4)/3.0 , (dx2 + dx3 + dx4)/3.0);
      
      int octant = RadTo8Way(dir);
      
      bool left = octant > 2 && octant < 6;
      bool up = octant >= 1 && octant <= 3;
      bool down = octant >= 5 && octant <= 7;
      bool right = octant < 2 || octant > 6;
      
      /// Update facing
      if (left) {
         faceleft = true;
         phys.vx = -CatSpeed(color);
      }
      else if (right) {
         faceleft = false;
         phys.vx = CatSpeed(color);
      }
      else {
         phys.vx = 0;
      }
      if (up) {
         phys.vy = CatSpeed(color);
      }
      else if (down) {
         phys.vy = -CatSpeed(color);
      }
      else {
         phys.vy = 0;
      }
   }
}



void Cat::Update(double dt) {
   phys = phys.FuturePhysics(dt);
   AdvanceAnimationTime(dt);
}



void Cat::Draw(EagleGraphicsContext* win) {
   SpriteSheetAnimation* ssa = pganime->GetCatAnimation(state);
   EAGLE_ASSERT(ssa);
   
   EagleImage* frame = ssa->GetFrame(GetFrameNum());
   
   win->Draw(frame , phys.x , phys.y , HALIGN_LEFT , VALIGN_BOTTOM , ecol , faceleft?DRAW_HFLIP:DRAW_NORMAL);
   
   
}








