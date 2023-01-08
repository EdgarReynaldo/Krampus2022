



#ifndef World_HPP
#define World_HPP

#include "Scene.hpp"
#include "Rooms.hpp"


#include "Eagle/Area.hpp"

std::pair<int,Rectangle> ReadRectangle(const char* r);



class World : public Scene {
protected :
   EagleGraphicsContext* window;
   
   int world_number;
   int room_number;
   
   Room current_room;
   
public :
   World();
   ~World();

   void Free();

   virtual bool Init(EagleGraphicsContext* win);
   
   virtual SCENE_STATUS HandleEvent(EagleEvent ev);
   virtual SCENE_STATUS Update(double dt);
   virtual void Display(EagleGraphicsContext* win);
   
   bool SetWorldAndRoom(int world_num , int room_num);
   
};




#endif // World_HPP










