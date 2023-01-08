



#include "Rooms.hpp"
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

   const int ROOMNUM = (world_num == 0)?-1:(10*(world_num-1) + room_num);
   ConfigFile roomcfg;
   success = success && roomcfg.LoadFromFile("Data/Images/Rooms/Rooms.cfg");
   
   std::string world = StringPrintF("World%d" , world_num);
   std::string room = StringPrintF("Room%d" , room_num);
   std::string bg = roomcfg[world][room];
   
   room_bg = win->LoadImageFromFile(bg , VIDEO_IMAGE);
   room_bg_memory = win->LoadImageFromFile(bg , MEMORY_IMAGE);

   success = success && (room_bg && room_bg->Valid());
   success = success && (room_bg_memory && room_bg_memory->Valid());
   return success;
}










