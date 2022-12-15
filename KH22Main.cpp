

#include "Program.hpp"



#include "Eagle/Logging.hpp"
#include "Eagle/backends/Allegro5Backend.hpp"

int main(int argc , char** argv) {
   
   (void)argc;
   (void)argv;
   
   SendOutputToFile("Log.txt" , "NVA" , false);
   

   Allegro5System* sys = GetAllegro5System();
   if (!sys->Initialize(EAGLE_FULL_SETUP)) {
      EagleWarn() << "Failed some likely (non critical) subsystem" << std::endl;
   }
   
   Program krampus;
   
   bool init = krampus.Init();
   
   if (!init) {
      EagleCritical() << "Failed to initialize krampus22 program. Halting." << std::endl;
      return 1;
   }
   
   return krampus.Run();
}














