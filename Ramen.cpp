



#include "Ramen.hpp"


#include "Eagle/GraphicsContext.hpp"
#include "Eagle/Image.hpp"



Ramen* pramen = 0;



Ramen::Ramen() :
      Object(Physics() , GRAY),
      window(0),
      ramen_pic(0),
      owner(0)
{}



void Ramen::Free() {
   if (window) {
      if (ramen_pic) {
         window->FreeImage(ramen_pic);
         ramen_pic = 0;
      }
   }
}



bool Ramen::Init(EagleGraphicsContext* win) {
   Free();
   window = win;
   ramen_pic = win->LoadImageFromFile("Data/Images/Food/Noodles.png");
   EAGLE_ASSERT(win && ramen_pic && ramen_pic->Valid());
   return win && ramen_pic && ramen_pic->Valid();
}
   


void Ramen::Draw(EagleGraphicsContext* win) {
   win->Draw(ramen_pic , phys.x , phys.y , HALIGN_CENTER , VALIGN_CENTER);
}





