



#ifndef GameScene_HPP
#define GameScene_HPP


#include "Scene.hpp"
#include "Ninja.hpp"
#include "Cats.hpp"
#include "GlobalAnimations.hpp"

#include <string>



class World;

class Game : public Scene {

   World* world;
   int world_num;
   int room_num;

   PlayerNinja pninja;
   EnemyNinja eninja;
   Cat cat;

   std::string pstate;/// stab/crouch/etc
   std::string estate;/// same
   std::string cstate;/// Walking/jumping

   GlobalAnimations anime;

public :
   
   Game();

   virtual ~Game();
   
   void Free();
   
   virtual bool Init(EagleGraphicsContext* win);
   
   virtual SCENE_STATUS HandleEvent(EagleEvent ev);
   virtual SCENE_STATUS Update(double dt);
   virtual void Display(EagleGraphicsContext* win);

   virtual void Reset();
};


#endif // GameScene_HPP
