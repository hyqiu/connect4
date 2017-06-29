
#include "2Gamers.h"
#include "CSurface.h"

const int WIDTH = 700;
const int HEIGHT = 600;

TwoPlayers::TwoPlayers(){
    
    Running = 1;
    red = NULL;
    yellow = NULL;
    empty = NULL;
    
    for (int i = 0; i<6; i++) {
        for (int j=0; j<7; j++) {
            Grid[i][j] = Empty;
        }
    }
    
    Winner = None;
    
    Firstplayer = player1;
    Currentplayer = player1;
    
    ////// On définit les jetons de chacun
    
    P1_Tile = Red;
    P2_Tile = Yellow;
    
    CurrentTile = P1_Tile;
}

bool TwoPlayers::OnInit(){
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    
    if ((Surf_Display = SDL_SetVideoMode(700, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    
    if ((empty = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/emptyboard.bmp")) == NULL) {
        return false;
    }
    
    if ((red = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/boardred.bmp")) == NULL) {
        return false;
    }
    
    if ((yellow = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/boardyellow.bmp")) == NULL) {
        return false;
    }
    
    if ((redh = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/redh.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowh = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/yellowh.bmp")) == NULL) {
        return false;
    }
    
    if ((redv = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/redv.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowv = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/yellowv.bmp")) == NULL) {
        return false;
    }
    
    if ((redad = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/redad.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowad = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/yellowad.bmp")) == NULL) {
        return false;
    }
    
    if ((reddd = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/reddd.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowdd = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/yellowdd.bmp")) == NULL) {
        return false;
    }

    
    CSurface::Transparent(red, 255, 0, 255);
    CSurface::Transparent(redh, 255, 0, 255);
    CSurface::Transparent(redv, 255, 0, 255);
    CSurface::Transparent(redad, 255, 0, 255);
    CSurface::Transparent(reddd, 255, 0, 255);
    CSurface::Transparent(yellow, 255, 0, 255);
    CSurface::Transparent(yellowh, 255, 0, 255);
    CSurface::Transparent(yellowv, 255, 0, 255);
    CSurface::Transparent(yellowad, 255, 0, 255);
    CSurface::Transparent(yellowdd, 255, 0, 255);
    
    Reset();
    
    return true;
}

/// Jeu du début

void TwoPlayers::Reset(){
    int w = WIDTH/7, h= HEIGHT/6, i, j, k, l;
    
    SDL_Rect r = {0};
    
    for (k= 0, i=0; i<HEIGHT; i+=h,k++) {
        r.y = i;
        for (l=0,j=0; j<WIDTH; j+=w,l++) {
            r.x = j;
            SDL_BlitSurface(empty,NULL,Surf_Display,&r);
        }
    }
}

int TwoPlayers::OnExecute(){
    
    if(OnInit() == false){
        return -1;
    }
    
    SDL_Flip(Surf_Display);
    SDL_Event Event;
    
    while(Running == 1){
        SDL_WaitEvent(&Event);
        switch (Event.type) {
                
            case SDL_QUIT:
                Running = 0;
                break;
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Running = 0;
                        break;
                }
            case SDL_MOUSEBUTTONDOWN:
                
                if (Event.button.button == SDL_BUTTON_LEFT) {
                    
                    if (IsGameOver(Grid) == true){
                        Running = 0;
                        break;
                    }
                    
                    int watchdog = 0; /// On checke le watchdog pour que si l'utilisateur clique sur une colonne pleine, on ne passe pas directement à l'autre.
                    
                    if (Currentplayer == player1) {
                        checkmouse(&Event.button, watchdog);
                        if (watchdog == 0) {
                            break;
                        }
                        
                        if (IsGameWon(Grid) == true) {
                            if (HorizontalWin(Grid) == true) {
                                MarkHorizontal(Grid);
                            }
                            
                            if (VerticalWin(Grid) == true) {
                                MarkVertical(Grid);
                            }
                            
                            if (ADWin(Grid) == true) {
                                MarkAD(Grid);
                            }
                            
                            if (DDWin(Grid) == true) {
                                MarkDD(Grid);
                            }
                            
                            OnCleanup();
                            return 0;
                        }
                        
                        else{
                        
                            Currentplayer = player2;
                            CurrentTile = P2_Tile;
                            break;
                        }
                    }
                    
                    else{
                        checkmouse(&Event.button, watchdog);
                        if (watchdog == 0) {
                            break;
                        }
                        if (IsGameWon(Grid) == true) {
                            if (HorizontalWin(Grid) == true) {
                                MarkHorizontal(Grid);
                            }
                            
                            if (VerticalWin(Grid) == true) {
                                MarkVertical(Grid);
                            }
                            
                            if (ADWin(Grid) == true) {
                                MarkAD(Grid);
                            }
                            
                            if (DDWin(Grid) == true) {
                                MarkDD(Grid);
                            }
                            
                            OnCleanup();
                            return 0;
                        }
                        
                        else{
                        
                            Currentplayer = player1;
                            CurrentTile = P1_Tile;
                            break;
                        }
                    }

                }
            }
        OnRender();
    }
    
    OnCleanup();
    return 0;
}

int TwoPlayers::RowforPlay(int ColID){
    
    int row;
    
    for (int i=5; i>=0; i--) {
        if (Grid[i][ColID] == Empty) {
            row = i;
            break;
        }
    }
    return row;
}

bool TwoPlayers::IsColFull(int ColID){
    
    if (Grid[0][ColID] != Empty) {
        return true;
    }
    
    else{
        return false;
    }
}

void TwoPlayers::checkmouse(SDL_MouseButtonEvent *mouse, int &watchdog){
    
    float mousex = mouse->x;
//    float mousey = mouse ->y;
    
    int colID = floor(mousex/100);
    
    if (IsColFull(colID) == true) {
        watchdog = 0;
        return;
    }
    
    else{
        watchdog = 1;
    }
    
    int rowID = RowforPlay(colID);
    
    SetCell(rowID,colID, CurrentTile);
}

void TwoPlayers::OnRender(){
    
    CSurface::OnDraw(Surf_Display,empty,0,0);
    
    int w = WIDTH/7, h= HEIGHT/6, i, j, k, l;
    
    SDL_Rect r = {0};
    
    //    SDL_BlitSurface(empty,NULL,Surf_Display,&r);
    
    for (k= 0, i=0; i<HEIGHT; i+=h,k++) {
        r.y=i;
        for (l=0,j=0; j<WIDTH; j+=w,l++) {
            r.x=j;
            
            if (Grid[k][l]==Red) {
                SDL_BlitSurface(red,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l]==Yellow){
                SDL_BlitSurface(yellow,NULL,Surf_Display,&r);
            }
            
            
            else if (Grid[k][l] == Redh){
                SDL_BlitSurface(redh,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowh){
                SDL_BlitSurface(yellowh,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Redv){
                SDL_BlitSurface(redv,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowv){
                SDL_BlitSurface(yellowv,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Redad){
                SDL_BlitSurface(redad,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowad){
                SDL_BlitSurface(yellowad,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Reddd){
                SDL_BlitSurface(reddd,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowdd){
                SDL_BlitSurface(yellowdd,NULL,Surf_Display,&r);
            }
        }
    }
    
    SDL_Flip(Surf_Display);
    
}

void TwoPlayers::OnExit(){
    SDL_Quit();
}

void TwoPlayers::SetCell(int RowID, int ColID, TwoPlayers::Tiles Type){
    if(RowID<0 || RowID>5 || ColID <0 || ColID > 7) return;
    
    Grid[RowID][ColID]=Type;
}

void TwoPlayers::MarkHorizontal(TwoPlayers::Tiles tab[6][7]){
    int start;
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Redh;
                    tab[i][start+1] = Redh;
                    tab[i][start+2] = Redh;
                    tab[i][start+3] = Redh;
                }
                
                else{
                    tab[i][start] = Yellowh;
                    tab[i][start+1] = Yellowh;
                    tab[i][start+2] = Yellowh;
                    tab[i][start+3] = Yellowh;
                }
                break;
            }
        }
    }
}

void TwoPlayers::MarkVertical(TwoPlayers::Tiles tab[6][7]){
    int start;
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                
                if (tab[start][j] == Red) {
                    
                    tab[start][j] = Redv;
                    tab[start+1][j] = Redv;
                    tab[start+2][j] = Redv;
                    tab[start+3][j] = Redv;
                }
                
                else{
                    tab[start][j] = Yellowv;
                    tab[start+1][j] = Yellowv;
                    tab[start+2][j] = Yellowv;
                    tab[start+3][j] = Yellowv;
                }
                break;
            }
        }
    }
}

void TwoPlayers::MarkAD(TwoPlayers::Tiles tab[6][7]){
    int start;
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Redad;
                    tab[i-1][start+1] = Redad;
                    tab[i-2][start+2] = Redad;
                    tab[i-3][start+3] = Redad;
                }
                
                else{
                    tab[i][start] = Yellowad;
                    tab[i-1][start+1] = Yellowad;
                    tab[i-2][start+2] = Yellowad;
                    tab[i-3][start+3] = Yellowad;
                }
                break;
            }
        }
    }
    
}

void TwoPlayers::MarkDD(TwoPlayers::Tiles tab[6][7]){
    int start;
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Reddd;
                    tab[i+1][start+1] = Reddd;
                    tab[i+2][start+2] = Reddd;
                    tab[i+3][start+3] = Reddd;
                }
                
                else{
                    tab[i][start] = Yellowdd;
                    tab[i+1][start+1] = Yellowdd;
                    tab[i+2][start+2] = Yellowdd;
                    tab[i+3][start+3] = Yellowdd;
                }
                break;
            }
        }
    }
}

bool TwoPlayers::IsGameWon(TwoPlayers::Tiles tab[6][7]){
    int start;
    bool won = false;
    
    ///// HORIZONTAL
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                won = true;
                
                if (tab[i][start] == Red) {
                    Winner = player1;
                    
                }
                
                else{
                    Winner = bot;
                    
                }
                
                break;
            }
        }
    }
    
    ////// VERTICAL
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                won = true;
                
                if (tab[start][j] == Red) {
                    Winner = player1;
                }
                
                else{
                    Winner = bot;
                }
                break;
            }
        }
    }
    
    ///// Ascending diagonal
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                won = true;
                if (tab[i][start] == Red) {
                    Winner = player1;
                }
                
                else{
                    Winner = bot;
                }
                break;
            }
        }
    }
    
    ///// Descending diagonal
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                won = true;
                if (tab[i][start] == Red) {
                    Winner= player1;
                }
                
                else{
                    Winner = bot;
                }
                break;
            }
        }
    }
    
    return won;
}

void TwoPlayers::OnCleanup(){
    SDL_FreeSurface(Surf_Display);
    SDL_FreeSurface(red);
    SDL_FreeSurface(yellow);
    SDL_FreeSurface(Surf_Display);
//    SDL_Quit();
}

bool TwoPlayers::HorizontalWin(TwoPlayers::Tiles tab[6][7]){
    int start;
    bool hwon = false;
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                hwon = true;
                break;
            }
        }
    }
    
    return hwon;
}

bool TwoPlayers::VerticalWin(TwoPlayers::Tiles tab[6][7]){
    int start;
    bool vwon = false;
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                vwon = true;
                break;
            }
        }
    }
    
    return vwon;
    
}

bool TwoPlayers::ADWin(TwoPlayers::Tiles tab[6][7]){
    
    int start;
    bool adwon = false;
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                adwon = true;
                break;
            }
        }
    }
    return adwon;
}

bool TwoPlayers::DDWin(TwoPlayers::Tiles tab[6][7]){
    int start;
    bool ddwon = false;
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                ddwon = true;
            }
        }
    }
    return ddwon;
}

bool TwoPlayers::IsGameOver(TwoPlayers::Tiles tab[6][7]){
    if (IsGameWon(tab) == true || IsBoardFull(tab) == true) {
        return true;
    }
    
    else{
        return false;
    }
}

bool TwoPlayers::IsBoardFull(TwoPlayers::Tiles tab[6][7]){
    bool res = true;
    
    for (int j = 0; j<7; j++) {
        if (tab[0][j] == Empty) {
            res = false;
            break;
        }
    }
    
    return res;
};

