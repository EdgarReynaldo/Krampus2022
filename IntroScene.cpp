



#include "IntroScene.hpp"
#include "Eagle/GraphicsContext.hpp"
#include "Eagle/Image.hpp"
#include "Eagle/Font.hpp"


IntroScene::IntroScene() :
      Scene(),
      window(0),
      krampus_splash(0),
      samurai_gif(),
      splash_font(0)
{
   
}



IntroScene::~IntroScene() 
{}



void IntroScene::Free() {
   if (window) {
      if (krampus_splash) {
         window->FreeImage(krampus_splash);
         krampus_splash = 0;
      }
      for (unsigned int i = 0 ; i < SAMURAI_NFRAMES ; ++i) {
         if (samurai_gif[i]) {
            window->FreeImage(samurai_gif[i]);
         }
         samurai_gif[i] = 0;
      }
      if (splash_font) {
         window->FreeFont(splash_font);
      }
   }
   complete = false;
   status = SCENE_NOTREADY;
}



bool IntroScene::Init(EagleGraphicsContext* win) {
   Free();
   window = win;
   EAGLE_ASSERT(win);
   krampus_splash = window->LoadImageFromFile("vista/mountain-vista-with-cliff-face-and-blue-michael-interisano.jpg");
   splash_font = window->GetFont("Data/Fonts/Verdana.ttf" , -240);
   bool success = window && window->Valid() && krampus_splash && krampus_splash->Valid() && splash_font && splash_font->Valid();
   for (unsigned int i = 0 ; i < SAMURAI_NFRAMES ; ++i) {
      char buf[1024] = {0};
      sprintf(buf , "samurai/samurai_frame_%04i.jpg" , i + 1 );
      samurai_gif[i] = window->LoadImageFromFile(buf);
      success = success && samurai_gif[i];
   }
   AnimationBase::Init(1 , 1 , 15.0 , ANIMATION_ONCE_FORWARDS);
   Reset();
   status = SCENE_READY;
   return success;
}



void IntroScene::Reset() {
   AnimationBase::ResetAnimation();
   complete = false;
}



SCENE_STATUS IntroScene::HandleEvent(EagleEvent ev) {
   if (ev.type == EAGLE_EVENT_DISPLAY_CLOSE) {
      return status = SCENE_COMPLETE;
   }
   return status = SCENE_RUNNING;
}



SCENE_STATUS IntroScene::Update(double dt) {
   AnimationBase::AdvanceAnimationTime(dt);
   redraw = true;
   if (complete) {return SCENE_COMPLETE;}
   return status = SCENE_RUNNING;
}



void IntroScene::Display(EagleGraphicsContext* win) {
   double pct = GetAnimationPercent();
   if (pct < 0.5) {
      pct = pct*2.0;
      double apct = (pct <= 0.5 )? (pct*2.0 ): ((1.0-pct)*2.0);
//      apct = apct/2.0;
      double npct = (pct - 0.9)*10.0;
      int frame = npct*22;
      if (frame >= 22) {frame = 21;}
      double spct = (pct < 0.8)?pct:(5.0*(1.0-pct));
      
      win->DrawImageFit(krampus_splash , Rectangle(0,0,win->Width() , win->Height()) , EagleColor(1.0f,1.0f,1.0f,spct));

      
      win->DrawTextString(splash_font , "Krampus22" , win->Width()/2 , (win->Height())*GetAnimationPercent() , EagleColor(1.0f,1.0f,1.0f,apct) , HALIGN_CENTER , VALIGN_CENTER);

      
      win->DrawTextString(splash_font , "Krampus22" , win->Width()/2 , win->Height() - (win->Height())*GetAnimationPercent() , EagleColor(0.0f,0.0f,0.0f,apct) , HALIGN_CENTER , VALIGN_CENTER);

      if (frame >= 0) {
         win->DrawImageCenter(samurai_gif[frame] , Rectangle(0,0,win->Width() , win->Height()));
      }
   }
   else if (pct < 0.667) {
      pct = (pct-0.333)*3.33;/// .333 to .667 0-1.0
      
      win->DrawImageCenter(samurai_gif[(int)SAMURAI_NFRAMES - 1] , Rectangle(0,0,win->Width(),win->Height()));
      
      win->DrawTextString(splash_font , "Krampus22" , win->Width()/2 + 5 , win->Height()/4 + 5 , EagleColor(0,0,0) , HALIGN_CENTER , VALIGN_CENTER);
      win->DrawTextString(splash_font , "Krampus22" , win->Width()/2  , win->Height()/4 - 5 , EagleColor(255,0,0) , HALIGN_CENTER , VALIGN_CENTER);
      
   }
   else if (pct <= 1.0) {
      pct = (pct - 0.667)*3.33;/// .667 to 0.999 0-1.0
      int frame = pct*SAMURAI_NFRAMES;
      if (frame >= SAMURAI_NFRAMES) {
         frame = (int)SAMURAI_NFRAMES - 1;
      }
      frame = ((int)SAMURAI_NFRAMES - 1) - frame;
      win->DrawImageCenter(samurai_gif[frame] , Rectangle(0,0,win->Width(),win->Height()) , EagleColor(1.0f , 1.0f - pct , 1.0f - pct , 1.0f - pct));
      win->DrawTextString(splash_font , "Krampus22" , win->Width()/2 + 5 , win->Height()/4 + 5 , EagleColor(255,0,0) , HALIGN_CENTER , VALIGN_CENTER);
      win->DrawTextString(splash_font , "Krampus22" , win->Width()/2  , win->Height()/4 - 5 , EagleColor(0,0,0) , HALIGN_CENTER , VALIGN_CENTER);
   }
   else {
      complete = true;
   }
}


















