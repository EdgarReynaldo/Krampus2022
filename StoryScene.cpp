



#include "StoryScene.hpp"

#include "Eagle/Font.hpp"
#include "Eagle/GraphicsContext.hpp"


StoryScene::StoryScene() :
      Scene(),
      window(0),
      font(0)
{}



StoryScene::~StoryScene() {}



bool StoryScene::Init(EagleGraphicsContext* win) {
   window = win;
   AnimationBase::Init(1 , 1 , 10.0);
   Reset();
   return win && win->Valid();
}



SCENE_STATUS StoryScene::HandleEvent(EagleEvent ev) {
   if (ev.type == EAGLE_EVENT_KEY_DOWN) {
      complete = true;
      return SCENE_COMPLETE;
   }
   return SCENE_RUNNING;
}



SCENE_STATUS StoryScene::Update(double dt) {
   AnimationBase::AdvanceAnimationTime(dt);
   if (complete) {
      return SCENE_COMPLETE;
   }
   return SCENE_RUNNING;
}

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "Eagle/backends/Allegro5/Allegro5Font.hpp"


void StoryScene::Display(EagleGraphicsContext* win) {
   double pct = GetAnimationPercent();
   EagleFont* font = win->GetFont("Data/Fonts/EnglishCn.ttf" , -240);
   if (pct < 0.3) {
      
      /// Draw red shadow krampus22 as header
      win->DrawTextString(font , "Krampus22" , win->Width()/2 + 5 , win->Height()/4 + 5 , EagleColor(255,0,0) , HALIGN_CENTER , VALIGN_CENTER);
      win->DrawTextString(font , "Krampus22" , win->Width()/2  , win->Height()/4 - 5 , EagleColor(0,0,0) , HALIGN_CENTER , VALIGN_CENTER);
      /// Draw red shadow krampus22 as header
      win->DrawTextString(font , "Presents" , win->Width()/2 + 5 , 3*win->Height()/4 + 5 , EagleColor(255,0,0) , HALIGN_CENTER , VALIGN_CENTER);
      win->DrawTextString(font , "Presents" , win->Width()/2  , 3*win->Height()/4 - 5 , EagleColor(0,0,0) , HALIGN_CENTER , VALIGN_CENTER);
   }
   else {
      /// Draw red shadow krampus22 as header
      win->DrawTextString(font , "Neko" , win->Width()/2 + 5 , win->Height()/4 + 5 , EagleColor(255,0,255) , HALIGN_CENTER , VALIGN_CENTER);
      win->DrawTextString(font , "Neko" , win->Width()/2  , win->Height()/4 - 5 , EagleColor(0,0,0) , HALIGN_CENTER , VALIGN_CENTER);
      /// Draw red shadow krampus22 as header
      win->DrawTextString(font , "Ninja" , win->Width()/2 + 5 , 3*win->Height()/4 + 5 , EagleColor(255,0,255) , HALIGN_CENTER , VALIGN_CENTER);
      win->DrawTextString(font , "Ninja" , win->Width()/2  , 3*win->Height()/4 - 5 , EagleColor(0,0,0) , HALIGN_CENTER , VALIGN_CENTER);
      
      
      uint16_t buf[5] = {
         0x30cd,0x30b3,0x5fcd,0x8005,0x0
      };
      ALLEGRO_USTR* ustr = al_ustr_new_from_utf16(buf);
      
      EagleFont* japfont = win->GetFont("Data/Fonts/Oshidashi-M-Gothic.otf" , -240);
      ALLEGRO_FONT* fnt = dynamic_cast<Allegro5Font*>(japfont)->AllegroFont();
      /// Draw white shadow
      win->DrawTextString(japfont , "\xe3\x83\x8d\xe3\x82\xb3\xe5\xbf\x8d\xe8\x80\x85" , win->Width()/2 + 5 , win->Height()/2 - 45 , EagleColor(255,255,255) , HALIGN_CENTER , VALIGN_CENTER);
      win->DrawTextString(japfont , "\xe3\x83\x8d\xe3\x82\xb3\xe5\xbf\x8d\xe8\x80\x85" , win->Width()/2  , win->Height()/2 - 55 , EagleColor(0,0,0) , HALIGN_CENTER , VALIGN_CENTER);
///      al_draw_ustr(fnt , al_map_rgb(255,255,255) , win->Width()/2 + 5 , win->Height()/2 + 5 , 0 , ustr);
///      al_draw_ustr(fnt , al_map_rgb(0,0,0) , win->Width()/2  , win->Height()/2 - 5 , 0 , ustr);
//      al_draw_ustr(fnt , al_map_rgb(255,255,255) , , 0 , 0 , ustr);
//      al_draw_ustr(fnt , al_map_rgb(0,0,0) , -5 , -10 , 0 , ustr);
      al_ustr_free(ustr);
   }
}
