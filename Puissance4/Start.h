
#ifndef __SDLP4__Start__
#define __SDLP4__Start__

#include <stdio.h>
#include "SDL/SDL.h"
#include "Connect4.h"
#include "2Gamers.h"


class StartMenu{
    
private:
    
    SDL_Surface *Background, *HumanvBot, *HumanvHuman, *Level, *Quit, *Menu_Display, *Difficulty, *OneTwo;
    SDL_Rect posBackground, posArcade, pos2, posLevel, posQuit;
    
    SDL_Rect poslvl1, poslvl2, poslvl3, poslvl4, poslvl5, poslvl6, posback;
    
    SDL_Rect PosP1, PosP2, PosbacktoD;
    
    int MenuRuns;
    
public:
    
    StartMenu();
    int showmenu();
    bool MenuInit();
    void Reset();
    void OnCleanup();
    
};

#endif /* defined(__SDLP4__Start__) */
