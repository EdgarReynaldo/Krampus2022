



#ifndef ROOMS_HPP
#define ROOMS_HPP


#include "Eagle/Area.hpp"



class EagleGraphicsContext;
class EagleImage;

class Room {

protected :
   
   friend class GameScene;
   
   EagleGraphicsContext* win;

public :
   
   Rectangle area;
   int world_number;
   int room_number;

   EagleImage* room_bg;
   EagleImage* room_bg_memory;
   


   Room();
   void FreeRoom();
   bool BuildRoom(EagleGraphicsContext* window , int world_num , int room_num);

   void Draw(EagleGraphicsContext* win);
   
   
   
};


extern Room* pcurrent_room;






#endif // ROOMS_HPP










