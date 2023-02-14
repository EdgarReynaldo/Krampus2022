



#include "GlobalAnimations.hpp"




GlobalAnimations* pganime = 0;



SpriteSheetAnimation::SpriteSheetAnimation() :
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



EagleImage* SpriteSheetAnimation::GetFrame(int fnum) {
   return subsheet[fnum];
}



bool SpriteSheetAnimation::SetupSpriteSheet(EagleGraphicsContext* win , EagleImage* spritesheet , std::string spritename) {
   Free();
   EAGLE_ASSERT(win);
   EAGLE_ASSERT(spritesheet && spritesheet->Valid());
   if (!win || !spritesheet || (spritesheet && !spritesheet->Valid())) {return false;}
   window = win;
   sheet = spritesheet;
   if (spritename.compare("CatWalk") == 0) {
      /// Uneven image 130,120,120,130
      int heights[4] = {130,120,120,130};
      int ys[4] = {0 , 130 , 250 , 370};
      subsheet.resize(8 , 0);
      for (unsigned int f = 0 ; f < 8 ; ++f) {
         int row = f/2;
         int col = f%2;
         int y = ys[row];//row*(sheet->H()/4);
         int x = col*(sheet->W()/2);
         subsheet[f] = window->CreateSubImage(sheet , x , y , sheet->W()/2 , heights[row]);
      }
      return true;
   }
   else if (spritename.compare("CatJump") == 0) {
      subsheet.resize(10 , 0);
      for (unsigned int f = 0 ; f < 10 ; ++f) {
         int row = f/3;
         int col = f%3;
         int y = row*(sheet->H()/4);
         int x = col*(sheet->W()/3);
         subsheet[f] = window->CreateSubImage(sheet , x , y , sheet->W()/3 , sheet->H()/4);
      }
      return true;
   }
   return false;
}



/// ----------------      Global Animations      ------------------------



bool GlobalAnimations::LoadGlobalAnimations(EagleGraphicsContext* win) {
   Free();
   EAGLE_ASSERT(win);
   window = win;
   bool success = true;
   
   cat_walking = window->LoadImageFromFile("Data/Images/Cats/CatRun.png");
   cat_jumping = window->LoadImageFromFile("Data/Images/Cats/CatJump.png");
   
   success = success && cat_walking && cat_walking->Valid();
   success = success && cat_jumping && cat_jumping->Valid();
   
   success = success && catwalk.SetupSpriteSheet(win , cat_walking , "CatWalk");
   success = success && catjump.SetupSpriteSheet(win , cat_jumping , "CatJump");
   
   catwalk.Init(8 , 1 , 2.0 , ANIMATION_REPEAT_FORWARDS);
   catjump.Init(10 , 1 , 1.2 , ANIMATION_ONCE_FORWARDS);
   
   catmap["Walk"] = &catwalk;
   catmap["Jump"] = &catjump;
   
   success = success && shuriken.Load  (window , "Data/Images/Shuriken/BladeB"       , "png" , 3);
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

   shuriken.Init  (3  , 1 , 0.20 , ANIMATION_REPEAT_FORWARDS);
   nstand.Init    (1  , 1 , 2.0 , ANIMATION_REPEAT_FORWARDS);
   nknockback.Init(1  , 1 , 0.5  , ANIMATION_ONCE_FORWARDS);
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



BitmapAnimation* GlobalAnimations::GetNinjaAnimation(std::string nstate) {
   return dynamic_cast<BitmapAnimation*>(ninjamap[nstate]);
}



SpriteSheetAnimation* GlobalAnimations::GetCatAnimation(std::string cstate) {
   return dynamic_cast<SpriteSheetAnimation*>(catmap[cstate]);
}





