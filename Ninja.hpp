



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


class EagleImage;

class Ninja : public Object {
   
   friend class Game;
   
protected :
   bool player;/// Player ninja or enemy ninja
   bool faceleft;
   bool midair;

   int health;/// -1 undead 0 to 999
   int lives_left;/// -1 undead 0-9
   int catlives;/// cat color bit field of flags

   int nshuriken;/// -1 means infinite, else num

   std::deque<Shuriken> shuriken;

   AnimationBase current_animation;
   std::string astate;/// Animation state
      
public :
   
   Ninja();
         
   virtual ~Ninja();
   
   
   virtual void HandleEvent(EagleEvent e);
   virtual void Update(double dt) override;
   virtual void Draw(EagleGraphicsContext* win) override;

   void LaunchShuriken();
   void SetAnimationState(std::string state , int frame_num = 0);
   int GetAnimationFrameNum();
   EagleImage* GetAnimationFrame();
};


double NinjaSpeed(COLOR c);



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



