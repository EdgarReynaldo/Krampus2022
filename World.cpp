



#include "World.hpp"



std::pair<int,Rectangle> ReadRectangle(const char* r) {
   std::pair<int , Rectangle> rp;
   rp.second = BADRECTANGLE;
   rp.first = -1;
   if (!r) {return rp;}
   int x = 0,y = 0,w = 0,h = 0;
   if (4 == sscanf(r , "(%d,%d,%d,%d)%n" , &x , &y , &w , &h , &rp.first)) {
      rp.second.SetArea(x,y,w,h);
   } else {
      rp.first = -1;
   }
   return rp;
}



World::World() :
      Scene(),
      window(),
      world_number(-1),
      room_number(-1),
      current_room()
{}



World::~World() {
   Free();
}



void World::Free() {
   current_room.FreeRoom();
}



bool World::Init(EagleGraphicsContext* win) {
   window = win;
   return SetWorldAndRoom(0,0);
}



SCENE_STATUS World::HandleEvent(EagleEvent ev) {
   (void)ev;
   return SCENE_RUNNING;
}



SCENE_STATUS World::Update(double dt) {
   (void)dt;
   return SCENE_RUNNING;
}



void World::Display(EagleGraphicsContext* win) {
   (void)win;
}



bool World::SetWorldAndRoom(int world_num , int room_num) {
   Free();
   if (world_num < 0) {
      world_num = 0;
   }
   if (world_num > 3) {
      world_num = 3;
   }
   if (world_num == 0) {room_num = 0;}
   else {
      if (room_num < 0) {
         room_num = 0;
      }
      else if (room_num > 9) {
         room_num = 9;
      }
   }
   bool status = current_room.BuildRoom(window , world_num , room_num);
   pcurrent_room = &current_room;
   world_number = world_num;
   room_number = room_num;
   return status;
}







