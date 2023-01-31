



#ifndef GameScene_HPP
#define GameScene_HPP


#include "Scene.hpp"
#include "Ninja.hpp"
#include "Cats.hpp"
#include "Ramen.hpp"
#include "GlobalAnimations.hpp"

#include <string>

#include "Eagle/Random.hpp"


class World;

class Game : public Scene {

   World* world;
   int world_num;
   int room_num;

   PlayerNinja pninja;
   EnemyNinja eninja;
   Cat cat;
   Ramen ramen;

   GlobalAnimations anime;

   MTRNG rng;
   
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
