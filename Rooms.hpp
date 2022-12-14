



#ifndef ROOMS_HPP
#define ROOMS_HPP


#include "Eagle/Area.hpp"



class EagleGraphicsContext;
class EagleImage;

class Room {

protected :
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

};


extern Room* pcurrent_room;






#endif // ROOMS_HPP










