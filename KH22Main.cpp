

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
//**   
   Program krampus;
   
   bool init = krampus.Init();
   
   if (!init) {
      EagleCritical() << "Failed to initialize krampus22 program. Halting." << std::endl;
      return 1;
   }
   
   return krampus.Run();
//*/

/**
   EagleGraphicsContext* win = sys->CreateGraphicsContext("Temp" , 400 , 300 , EAGLE_WINDOWED);
   win->Clear();
   win->DrawTextString(win->DefaultFont() , "Resizing" , win->Width()/2 , win->Height()/2 , EagleColor(255,255,255) , HALIGN_CENTER , VALIGN_CENTER);

   win->SetCopyBlender();
   
   std::shared_ptr<Folder> fl = sys->GetFileSystem()->ReadFolder(std::string("Data/Images/Ninja/Original"));
   Folder::FILEMAP fm = fl->Files();
   for (Folder::FILEMAP::iterator it = fm.begin() ; it != fm.end() ; ++it) {
      std::shared_ptr<File> f = it->second;
      std::string p = f->Path();
      if (f->Info().Exists()) {
         EagleImage* img = win->LoadImageFromFile(p.c_str());
         EAGLE_ASSERT(img && img->Valid());
         EagleImage* temp = win->CreateImage(img->W()/2 , img->H()/2);
         win->SetDrawingTarget(temp);
         win->Clear();
         win->DrawStretched(img , Rectangle(0 , 0 , temp->W() , temp->H()));
         bool save = win->SaveImage(temp , std::string("Data/Images/Ninja/New/") + f->Name());
         EAGLE_ASSERT(save);
         win->FreeImage(temp);
         win->FreeImage(img);
      }
   }

//*/

   return 0;
}














