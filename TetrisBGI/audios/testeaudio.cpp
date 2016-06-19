// play a wave file sound using the winmm library 
// Include -lwinmm on linker parameters

#include <iostream> 
#include <windows.h>   // for PlaySound()


//#define SND_FILENAME 0x20000
//#define SND_LOOP 8 
//#define SND_ASYNC 1 

using namespace std; 

int main() 
{ 
  // play sound as loop (remove SND_LOOP for one time play) 
  // file me.wav has be in the working directory
  PlaySound("1.wav",NULL,9);
   
  cin.get(); // wait 
  return 0; 
}
