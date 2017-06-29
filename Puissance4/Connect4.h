
#ifndef __SDLP4__Puissance4__
#define __SDLP4__Puissance4__

#include <stdio.h>

#include "SDL/SDL.h"
#include "CSurface.h"

class Connect4_AI{

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
    
    Tiles Grid[6][7];
    
    SDL_Surface* Surf_Display;
    
    SDL_Surface *red, *yellow, *empty;
    
    SDL_Surface *redh, *redv, *redad, *reddd;
    SDL_Surface *yellowh, *yellowv, *yellowad, *yellowdd;
    
    SDL_Surface *gameover;
    
    SDL_Rect backmain, quit;
    

    PlayerT Currentplayer;
    PlayerT Winner;
    PlayerT Firstplayer;
    
    Tiles P1_Tile;
    Tiles P2_Tile;
    Tiles Bot_Tile;
    Tiles CurrentTile;
    Tiles MaximizerTile;
    Tiles MinimizerTile;

    bool Running;
    
    bool win;
    
    int depth;
    
    
public:
    
    // Basic Settings
    
    Connect4_AI(int ID, int depth);
    
    int OnExecute();
    
    bool OnInit();
    
    void OnRender();
    
    void OnCleanup();
    
    void OnExit();
    
    void Reset();
    
    void checkmouse(SDL_MouseButtonEvent *mouse);
    
    int RowforPlay(int ColID);
    
    bool IsColFull(int ColID);
    
    bool IsGameWon(Tiles tab[6][7]);
    
    bool IsBoardFull(Tiles tab[6][7]);
    
    bool IsGameOver(Tiles tab[6][7]);
    
    bool HorizontalWin(Tiles tab[6][7]);
    bool VerticalWin(Tiles tab[6][7]);
    bool ADWin(Tiles tab[6][7]);
    bool DDWin(Tiles tab[6][7]);
    
    void MarkHorizontal(Tiles tab[6][7]);
    void MarkVertical(Tiles tab[6][7]);
    void MarkAD(Tiles tab[6][7]);
    void MarkDD(Tiles tab[6][7]);
    
  
    // For AI purposes
    
    int MakeBotPlay(Tiles tab[6][7], int depth, PlayerT player, Tiles type);
    
    int Alpha_Beta(Tiles tab[6][7],int depth, int alpha, int beta, PlayerT player);
    
    int Maximum(int a, int b);
    
    int Minimum(int a, int b);
    
    int Eval(Tiles tab[6][7], PlayerT player);
    
    int CheckThrees(Tiles tab[6][7], PlayerT player);
    
    int CheckTwos(Tiles tab[6][7], PlayerT player);
    
    void botplays(int depth, Tiles type);
    
    void SetCell(int RowID, int ColID, Tiles Type);
    void EraseCell(int RowID, int colID);
    
};


#endif /* defined(__SDLP4__Puissance4__) */
