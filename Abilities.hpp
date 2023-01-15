



#ifndef Abilities_HPP
#define Abilities_HPP


#include "Objects.hpp"



class Attack {
   std::string attack;
   int basedamage;
   std::deque<KEYBOARD_EVENT_DATA> trigger
   COLOR color;
   double speed;
   
};

std::map<std::string , Attack> attack_map;






#endif // Abilities_HPP
