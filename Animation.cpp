



#include "Animation.hpp"

#include "Eagle/StringWork.hpp"



BitmapAnimation::BitmapAnimation() :
      AnimationBase(),
      win(0),
      frames()
{
   (void)0;
}



void BitmapAnimation::Free() {
   if (win) {
      for (unsigned int i = 0 ; i < frames.size() ; ++i) {
         win->FreeImage(frames[i]);
      }
      frames.clear();
   }
}



bool BitmapAnimation::Load(EagleGraphicsContext* window , std::string basename , std::string ext , int nframes) {
   Free();
   win = window;
   bool success = true;
   std::string path; 
   for (int i = 0 ; i  < nframes ; ++i) {
      path = StringPrintF("%s%d.%s" , basename.c_str() , i + 1 , ext.c_str());
      frames[i] = win->LoadImageFromFile(path.c_str());
      success = success && (frames[i] && frames[i]->Valid());
   }
   return success;
}



EagleImage* BitmapAnimation::GetFrame() {
   return frames[frame_num];
}



EagleImage* BitmapAnimation::GetFrame(unsigned int n) {
   return frames[n];
}



/// --------------------      Animation Map     -------------------------------



void AnimationMap::SetAnimeRef(std::string name , AnimationBase* anime) {
   amap[name] = anime;
}



AnimationBase* AnimationMap::GetAnime(std::string name) {
   return amap[name];
}
