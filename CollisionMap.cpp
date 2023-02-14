



#include "Objects.hpp"
#include "Eagle/Exception.hpp"
#include "Eagle/Image.hpp"

#include "Eagle/GraphicsContext.hpp"


#include "allegro5/allegro_color.h"


EagleColor GetColorByEnum(COLOR c) {
   const EagleColor carray[NUMCOLORS] = {
      EagleColor(127,127,127,255),
      EagleColor(255,255,255,255),
      EagleColor(255,  0,  0,255),
      EagleColor(255,127,  0,255),
      EagleColor(255,255,  0,255),
      EagleColor(  0,255,  0,255),
      EagleColor(  0,255,255,255),
      EagleColor(  0,  0,255,255),
      EagleColor(127,  0,255,255),
      EagleColor(  0,  0,  0, 64)
   };
   return carray[c];
}



CollisionMap::CollisionMap() :
      window(0),
      cimage(0),
      caverage(0)
{}



void CollisionMap::Free() {
   if (window) {
      if (cimage) {
         /// win->FreeImage(cimage);/// reference only
         cimage = 0;
      }
      if (caverage) {
         window->FreeImage(caverage);
         caverage = 0;
      }
   }
}
   
   
bool CollisionMap::Init(EagleGraphicsContext* win , EagleImage* image) {
   Free();
   window = win;
   EAGLE_ASSERT(win);
   cimage = image;
   EAGLE_ASSERT(image && image->Valid());
   caverage = CreateAverageColor();
   EAGLE_ASSERT(caverage && caverage->Valid());
   return caverage->Valid();
}
   
   
   
EagleImage* CollisionMap::CreateAverageColor() {
   EAGLE_ASSERT(cimage);
   EagleImage* img = window->CreateImage(cimage->W() , cimage->H() , MEMORY_IMAGE , "Average color map");
   
   window->PushDrawingTarget(img);
   for (int y = 0 ; y < cimage->H() ; ++y) {
      for (int x = 0 ; x < cimage->W() ; ++x) {
         img->PutPixel(x,y,AvePixColor9(x,y));
      }
   }
   window->PopDrawingTarget();
//   window->SaveImage(img , "Average.png");
   return img;
}


EagleColor CollisionMap::AvePixColor9(int x , int y) {
   if (x > 0 && x < cimage->W() - 1) {
      if (y > 0 && y < cimage->H() - 1) {
         return FastPix9(x,y);
      }
   }
   
   int r = 0;
   int g = 0;
   int b = 0;
   int a = 0;
   int n = 0;
   for (int iy = y - 1 ; iy <= y + 1 ; ++iy) {
      if (iy >= 0 && iy <= cimage->H() - 1) {
         for (int ix = x - 1 ; ix <= x + 1 ; ++ix) {
            if (ix >= 0 && ix <= cimage->W() - 1) {
               EagleColor c = cimage->GetPixel(ix,iy);
               r += c.R();
               g += c.G();
               b += c.B();
               a += c.A();
               n++;
            }
         }
      }
   }
   EAGLE_ASSERT(n);
   if (n) {
      r /= n;
      g /= n;
      b /= n;
      a /= n;
   }
   return EagleColor(r,g,b,a);
}
EagleColor CollisionMap::FastPix9(int x , int y) {
   int r = 0;
   int g = 0;
   int b = 0;
   int a = 0;
   EAGLE_ASSERT(x > 0);
   EAGLE_ASSERT(y > 0);
   EAGLE_ASSERT(x < cimage->W() - 1);
   EAGLE_ASSERT(y < cimage->H() - 1);
   for (int iy = y - 1 ; iy <= y + 1 ; ++iy) {
      for (int ix = x - 1 ; ix <= x + 1 ; ++ix) {
         EagleColor ecol = cimage->GetPixel(ix,iy);
         r += ecol.R();
         g += ecol.G();
         b += ecol.B();
         a += ecol.A();
      }
   }
   r /= 9;
   g /= 9;
   b /= 9;
   a /= 9;
   return EagleColor(r,g,b,a);
}



double DistanceRGBA(EagleColor c1 , EagleColor c2) {
   int rd = c2.R() - c1.R();
   int gd = c2.G() - c1.G();
   int bd = c2.B() - c1.B();
   int ad = c2.A() - c1.A();
   return sqrt((double)(rd*rd + gd*gd + bd*bd + ad*ad))/(4*256*256.0);
}


double DistanceHSL(EagleColor c1 , EagleColor c2) {
   float h1 = 0.0;
   float s1 = 0.0;
   float l1 = 0.0; 
   float h2 = 0.0;
   float s2 = 0.0;
   float l2 = 0.0; 
   al_color_rgb_to_hsl(c1.fR() , c1.fG() , c1.fB() , &h1 , &s1 , &l1);
   al_color_rgb_to_hsl(c2.fR() , c2.fG() , c2.fB() , &h2 , &s2 , &l2);
   
   double dl = fabs(l2 - l1);
   dl /= 2.0;
   
   if (s2 < 0.1) {
      h2 = 0.0;
   }
   if (s1 < 0.1) {
      h1 = 0.0;
   }
   double ds = fabs(s2 - s1);
   double dh = fabs(h2 - h1);
   
   while (dh < 0.0) {dh += 360.0;}
   dh /= 360.0;
   
   return (dh + ds + dl)/3.0;
}





