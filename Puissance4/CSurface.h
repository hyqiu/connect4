#ifndef __SDLP4__CSurface__
#define __SDLP4__CSurface__

#include <stdio.h>
#include "SDL/SDL.h"

class CSurface {
public:
    CSurface();
    
    static SDL_Surface* OnLoad(char*File);
    
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_src, int X, int Y);
    
    static bool OnDraw(SDL_Surface* Surf_Dest,SDL_Surface* Surf_src, int X, int Y, int X2, int Y2, int W, int H);
    
    static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
  
};




#endif /* defined(__SDLP4__CSurface__) */
