



#ifndef Ninja_HPP
#define Ninja_HPP



#include "Eagle/AnimationBase.hpp"
#include "Objects.hpp"



class Shuriken : public AnimationBase , public Object {
public :
   Shuriken(Physics p , COLOR c);

   virtual void HandleEvent(EagleEvent e);
   virtual void Update(double dt);
   virtual void Draw(EagleGraphicsContext* win);
};

double ShurikenSpeed(COLOR c);


class Ninja : public Object {
protected :
   bool player;/// Player ninja or enemy ninja

   int nshuriken;/// -1 means infinite, else num

   int lives;/// -1 undead 0-9
   int lives_left;
   
   int health;/// -1 undead 0 to 999

   bool faceleft;

   AnimationBase shuriken_animation;
   
      
   std::deque<Shuriken> shuriken;
public :
   
   Ninja();
   virtual ~Ninja();
   
   
   virtual void HandleEvent(EagleEvent e);
   virtual void Update(double dt) override;
   virtual void Draw(EagleGraphicsContext* win) override;

   void LaunchShuriken();
};


class PlayerNinja : public Ninja {
public :
   virtual void HandleEvent(EagleEvent e) override;
   virtual void Update(double dt) override;
};



class EnemyNinja : public Ninja {
public :
   virtual void HandleEvent(EagleEvent e) override;
   virtual void Update(double dt) override;
};



extern PlayerNinja* pplayer;
extern EnemyNinja* penemy;






#endif // Ninja_HPP





