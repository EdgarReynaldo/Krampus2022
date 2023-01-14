



#include "GlobalAnimations.hpp"




GlobalAnimations* pganime = 0;


/**
SpriteSheetAnimation() :
      AnimationBase(),
      window(0),
      sheet(0),
      name(""),
      subsheet()
{}



SpriteSheetAnimation::~SpriteSheetAnimation() {
   Free();
}



void SpriteSheetAnimation::Free() {
   if (window) {
      for (unsigned int i = 0 ; i < subsheet.size() ; ++i) {
         window->FreeImage(subsheet[i]);
      }
      subsheet.clear();
      window = 0;
   }
}



void SpriteSheetAnimation::Update(double dt) {
   AdvanceAnimationTime(dt);
}



EagleImage* SpriteSheetAnimation::CurrentFrame() {
   return subsheet[frame_num];
}
*/


/// ----------------      Global Animations      ------------------------



bool GlobalAnimations::LoadGlobalAnimations(EagleGraphicsContext* win) {
   Free();
   EAGLE_ASSERT(win);
   window = win;
   bool success = true;
   
   success = success && shuriken.Load  (window , "Data/Images/Shuriken/Blade"       , "png" , 3);
   success = success && nstand.Load    (window , "Data/Images/Ninja/NinjaStand"     , "png" , 1);
   success = success && nknockback.Load(window , "Data/Images/Ninja/NinjaKnockback" , "png" , 1);
   success = success && ndie.Load      (window , "Data/Images/Ninja/NinjaDie"       , "png" , 10);
   success = success && ncrouch.Load   (window , "Data/Images/Ninja/NinjaCrouch"    , "png" , 1);
   success = success && nstab.Load     (window , "Data/Images/Ninja/NinjaStab"      , "png" , 2);
   success = success && nspring.Load   (window , "Data/Images/Ninja/NinjaSpring"    , "png" , 3);
   success = success && ndodge.Load    (window , "Data/Images/Ninja/NinjaDodge"     , "png" , 2);
   success = success && nslash.Load    (window , "Data/Images/Ninja/NinjaSlash"     , "png" , 7);
   success = success && nspin.Load     (window , "Data/Images/Ninja/NinjaSpin"      , "png" , 10);
   success = success && nrun.Load      (window , "Data/Images/Ninja/NinjaRun"       , "png" , 6);

   shuriken.Init  (3  , 1 , 0.25 , ANIMATION_REPEAT_FORWARDS);
   nstand.Init    (1  , 1 , 10.0 , ANIMATION_REPEAT_FORWARDS);
   nknockback.Init(1  , 1 , 1.0  , ANIMATION_ONCE_FORWARDS);
   ndie.Init      (10 , 1 , 1.5  , ANIMATION_ONCE_FORWARDS);
   ncrouch.Init   (1  , 1 , 10.0 , ANIMATION_REPEAT_FORWARDS);
   nstab.Init     (2  , 1 , 0.4  , ANIMATION_ONCE_FORWARDS);
   nspring.Init   (3  , 1 , 0.4  , ANIMATION_ONCE_FORWARDS);
   ndodge.Init    (2  , 1 , 1.0  , ANIMATION_ONCE_FORWARDS);
   nslash.Init    (7  , 1 , 1.0  , ANIMATION_ONCE_FORWARDS);
   nspin.Init     (10 , 1 , 1.5  , ANIMATION_ONCE_FORWARDS);
   nrun.Init      (6  , 1 , 1.5  , ANIMATION_REPEAT_FORWARDS);
   
   ninjamap["Shuriken"] = &shuriken;
   ninjamap["Stand"] = &nstand;
   ninjamap["Knockback"] = &nknockback;
   ninjamap["Die"] = &ndie;
   ninjamap["Crouch"] = &ncrouch;
   ninjamap["Stab"] = &nstab;
   ninjamap["Spring"] = &nspring;
   ninjamap["Dodge"] = &ndodge;
   ninjamap["Slash"] = &nslash;
   ninjamap["Spin"] = &nspin;
   ninjamap["Run"] = &nrun;

   return success;
}



GlobalAnimations::GlobalAnimations() :
      window(0),
      shuriken(),
      nstand(),
      nknockback(),
      ndie(),
      ncrouch(),
      nstab(),
      nspring(),
      ndodge(),
      nslash(),
      nspin(),
      nrun(),
      ninjamap()
{}



GlobalAnimations::~GlobalAnimations() {
   Free();
}



void GlobalAnimations::Free() {
   if (window) {
      shuriken.Free();
      nstand.Free();
      nknockback.Free();
      ndie.Free();
      ncrouch.Free();
      nstab.Free();
      nspring.Free();
      ndodge.Free();
      nslash.Free();
      nspin.Free();
      nrun.Free();
      ninjamap.clear();
      
   }
}



AnimationBase* GlobalAnimations::GetNinjaAnimation(std::string nstate) {
   return ninjamap[nstate];
}


