



#include "Rooms.hpp"
#include "Ninja.hpp"
#include "Cats.hpp"
#include "Ramen.hpp"
#include "GlobalAnimations.hpp"
#include "Eagle/Image.hpp"
#include "Eagle/GraphicsContext.hpp"
#include "Eagle/ConfigFile.hpp"
#include "Eagle/StringWork.hpp"



Room* pcurrent_room = 0;



Room::Room() :
      win(0),
      area(),
      world_number(-1),
      room_number(-1),
      room_bg(0),
      room_bg_memory(0)
{}

   
   
void Room::FreeRoom() {
   if (win) {
      if (room_bg)  {
         win->FreeImage(room_bg);
         room_bg = 0;
      }
      if (room_bg_memory) {
         win->FreeImage(room_bg_memory);
         room_bg_memory = 0;
      }
   }
   world_number = -1;
   room_number = -1;
   area = BADRECTANGLE;
   win = 0;
}


   
bool Room::BuildRoom(EagleGraphicsContext* window , int world_num , int room_num) {
   FreeRoom();
   bool success = true;
   if (world_num < 0 || world_num > 3) {
      world_num = 0;
      room_num = 0;
   }
   if (room_num < 0 || room_num > 9) {
      room_num = 0;
   }
   win = window;

///   const int ROOMNUM = (world_num == 0)?-1:(10*(world_num-1) + room_num);
   ConfigFile roomcfg;
   success = success && roomcfg.LoadFromFile("Data/Images/Rooms/Rooms.cfg");
   
   std::string world = StringPrintF("WORLD%d" , world_num);
   std::string room = StringPrintF("Room%d" , room_num);
   std::string bg = roomcfg[world][room];
   
   room_bg = win->LoadImageFromFile(bg , VIDEO_IMAGE);
   room_bg_memory = win->LoadImageFromFile(bg , MEMORY_IMAGE);

////   area.SetArea(0 , win->Height() - room_bg->H() , room_bg->W() , room_bg->H());
   area.SetArea(0 , 0 , room_bg->W() , room_bg->H());
   
   success = success && (room_bg && room_bg->Valid());
   success = success && (room_bg_memory && room_bg_memory->Valid());
   
   pplayer->phys.y = room_bg->H() - dynamic_cast<BitmapAnimation*>(pganime->GetNinjaAnimation("Stand"))->GetFrame(0)->H()/2;
   penemy->phys.y = pplayer->phys.y;
   penemy->phys.x = room_bg->W();
   pcat->phys.x = room_bg->W()/2;
   pcat->phys.y = 0;
   pramen->phys.x = room_bg->W()/2;
   pramen->phys.y = room_bg->H() - pramen->RamenPic()->H()/2;
   
   
   CollisionMap cmap;
   success = success && cmap.Init(win , room_bg_memory);
   
   return success;
}



void Room::Draw(EagleGraphicsContext* win) {
   win->Draw(room_bg , area.X() , area.Y());
}










