
#ifndef __SDLP4___pGame__
#define __SDLP4___pGame__

#include <stdio.h>
#include "SDL/SDL.h"
#include <cmath>
#include "CSurface.h"

class TwoPlayers{
    
private:
    
    enum Tiles{
        Empty= 0,
        
        Red,
        Redh,
        Redv,
        Redad,
        Reddd,
        
        Yellow,
        Yellowh,
        Yellowv,
        Yellowad,
        Yellowdd
    };
    
    enum PlayerT{
        None = 0,
        player1,
        player2,
        bot
    };
    
    bool Running;
    
    bool win;
    
    Tiles Grid[6][7];
    
    SDL_Surface* Surf_Display;
    
    SDL_Surface *red, *yellow, *empty;
    
    SDL_Surface *redh, *redv, *redad, *reddd;
    SDL_Surface *yellowh, *yellowv, *yellowad, *yellowdd;
    
    PlayerT Currentplayer;
    PlayerT Winner;
    PlayerT Firstplayer;
    
    Tiles P1_Tile;
    Tiles P2_Tile;
    Tiles Bot_Tile;
    Tiles CurrentTile;
    
public:
    
    TwoPlayers();
    
    int OnExecute();
    
    bool OnInit();
    
    void OnLoop();
    
    void OnRender();
    
    void OnCleanup();
    
    void OnExit();
    
    void Reset();
    
    void checkmouse(SDL_MouseButtonEvent *mouse, int &watchdog);
    
    int RowforPlay(int ColID);
    
    bool IsColFull(int ColID);
    
    bool IsGameWon(Tiles tab[6][7]);
    
    bool IsBoardFull(Tiles tab[6][7]);
    
    bool IsGameOver(Tiles tab[6][7]);
    
    int CheckGameStatus(Tiles tab[6][7]);
    
    bool HorizontalWin(Tiles tab[6][7]);
    bool VerticalWin(Tiles tab[6][7]);
    bool ADWin(Tiles tab[6][7]);
    bool DDWin(Tiles tab[6][7]);
    
    void MarkHorizontal(Tiles tab[6][7]);
    void MarkVertical(Tiles tab[6][7]);
    void MarkAD(Tiles tab[6][7]);
    void MarkDD(Tiles tab[6][7]);
    
    void SetCell(int RowID, int ColID, Tiles Type);
    
};


#endif /* defined(__SDLP4___pGame__) */
